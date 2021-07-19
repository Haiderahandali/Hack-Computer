#include "parse.h"
#include "hashtable.h"

static bool gHasMoreLines;
static int gInstructionNo;
static char gBuffer[MAX_INSTRUCTION_SIZE];

static void Parse_C_Instruction(instruction_t* currentInstruction, char* instructionString, CInstructionType t);
static void Parse_A_Instruction(instruction_t* currentInstruction, char* instructionString);
static instruction_t* gInstructions;
char initStr[17] = "0000000000000000";

static symbol_table_t* gHashtable;
static int gNextAvailableAddr = 16; // we filled the symbol from 0 to 15

static void Parse_L_Instruction(instruction_t* currentInstruction, char* instructionString);

static int isDigit(char c)
{
    return (c <= '9' && c >= '0');
}

#define PLUS 1
#define NEGATIVE -1
typedef long long long_t;

static long_t StrToInt(char* src)
{

    ulong_t size     = strlen(src);
    ulong_t value    = 0;
    signed char sign = PLUS;
    ulong_t index    = 0;

    if (src[0] == '-')
    {
        index = 1;
        sign  = NEGATIVE;
    }
    else if (src[0] == '+')
    {
        index = 1;
    }

    for (; index < size; ++index)
    {
        char currentCharValue = src[index]; //assuming ASCII only

        if (!isDigit(currentCharValue))
        {
            printf("error: %c is not a digit\n", src[index]);
            exit(1);
        }

        value = (value * 10) + (ulong_t)(currentCharValue - '0');
    }

    return (long_t)value * sign;
}

static void DecimalToBinary(long_t decimal, char* buffer)
{

    if ((decimal >> 15) > 0)
    {
        return;
    }

    for (int j = 0; j < INSTRUCTION_SIZE_BINARY; ++j)
    {

        //don't know if there is a better way
        buffer[j] += (decimal & (1 << (INSTRUCTION_SIZE_BINARY - (j + 1)))) != 0;
    }

    buffer[INSTRUCTION_SIZE_BINARY] = '\0';
}

file_pointer_t InitParse(char const* pathToFile)
{

    gInstructionNo = 0;
    gHasMoreLines  = true;
    gInstructions  = malloc(sizeof(instruction_t) * MAX_LINES);
    for (int i = 0; i < MAX_LINES; ++i)
    {
        gInstructions[i].instructionString       = malloc(sizeof(char) * MAX_INSTRUCTION_SIZE);
        gInstructions[i].instructionBinaryFormat = malloc(sizeof(char) * (INSTRUCTION_SIZE_BINARY + 1));
    }

    gHashtable = CreateSymbolTable(MAX_LINES);

    HashtableInsertSymbol("SP", 0, gHashtable);
    HashtableInsertSymbol("LCL", 1, gHashtable);
    HashtableInsertSymbol("ARG", 2, gHashtable);
    HashtableInsertSymbol("THIS", 3, gHashtable);
    HashtableInsertSymbol("THAT", 4, gHashtable);

    HashtableInsertSymbol("R0", 0, gHashtable);
    HashtableInsertSymbol("R1", 1, gHashtable);
    HashtableInsertSymbol("R2", 2, gHashtable);
    HashtableInsertSymbol("R3", 3, gHashtable);
    HashtableInsertSymbol("R4", 4, gHashtable);
    HashtableInsertSymbol("R5", 5, gHashtable);
    HashtableInsertSymbol("R6", 6, gHashtable);
    HashtableInsertSymbol("R7", 7, gHashtable);
    HashtableInsertSymbol("R8", 8, gHashtable);
    HashtableInsertSymbol("R9", 9, gHashtable);
    HashtableInsertSymbol("R10", 10, gHashtable);
    HashtableInsertSymbol("R11", 11, gHashtable);
    HashtableInsertSymbol("R12", 12, gHashtable);
    HashtableInsertSymbol("R13", 13, gHashtable);
    HashtableInsertSymbol("R14", 14, gHashtable);
    HashtableInsertSymbol("R15", 15, gHashtable);
    HashtableInsertSymbol("SCREEN", 16384, gHashtable);
    HashtableInsertSymbol("KBD", 24576, gHashtable);

    return fopen(pathToFile, "r");
}

//This already strip out extra tokens such as whitespaces, comments
char const* GetLineFromStream(file_pointer_t openedFile)
{
    int i = 0;

    bool endOfLine = false;
    while (!endOfLine)
    {

        int c = fgetc(openedFile);
        switch (c)
        {
            case ' ':
            {
                break;
            }

            case CR:
            case '\n':
            {
                endOfLine = true;
                break;
            }

            case EOF:
            {
                gHasMoreLines = false;
                endOfLine     = true;
                break;
            }

            case '/':
            {

                int secondSlash = fgetc(openedFile);
                if (secondSlash != '/')
                {
                    printf("invalid comment expected next slash\n");
                    endOfLine = true;
                    break;
                }
                while (true)
                {
                    int ch = fgetc(openedFile);
                    if (ch == EOF || ch == '\n')
                    {
                        endOfLine = true;
                        break;
                    }
                }
                break;
            }

            default:
            {
                gBuffer[i] = (char)c;
                ++i;
                break;
            }
        }
    }
    gBuffer[i] = '\0';
    return gBuffer;
}

void PushInstruction(char const* instructionLine)
{
    ulong_t stringSize = strlen(instructionLine);
    static int lineNo  = -1;
    if (stringSize > 0) //if not am empty instruction do nothing
    {
        if (stringSize >= MAX_INSTRUCTION_SIZE)
        {
            printf("instruction:%s  size is above maximum %d, skipping to next instruction ....\n", instructionLine, MAX_INSTRUCTION_SIZE);
            return;
        }
        gInstructions[gInstructionNo].lineSize = stringSize;
        strcpy(gInstructions[gInstructionNo].instructionString, instructionLine);

        strcpy(gInstructions[gInstructionNo].instructionBinaryFormat, initStr);

        char firstCh = instructionLine[0];
        switch (firstCh)
        {
            case '@':
            {
                gInstructions[gInstructionNo].type       = A_Insturction;
                gInstructions[gInstructionNo].lineNumber = ++lineNo;

                break;
            }
            case '(':
            {
                if (instructionLine[stringSize - 1] != ')')
                {
                    printf("Error expected a matching parenthesis for '(' \n");
                }
                else
                {
                    //this needed here, because we can declare symbols
                    //before we use them, so before parsing the strings,
                    //they should be added to the symbol table
                    gInstructions[gInstructionNo].type       = L_Insturction;
                    gInstructions[gInstructionNo].lineNumber = lineNo;
                    char temp[MAX_INSTRUCTION_SIZE + 1];
                    Symbol(&gInstructions[gInstructionNo], temp);
                    Parse_L_Instruction(&gInstructions[gInstructionNo], temp);
                    // empty instruction
                    gInstructions[gInstructionNo].instructionBinaryFormat[0] = '\0';
                    break;
                }
                break;
            }
            default:
            {
                gInstructions[gInstructionNo].type       = C_Insturction;
                gInstructions[gInstructionNo].lineNumber = ++lineNo;
                break;
            }
        }

        //we successfully pushed an instruction so we increase the line count
        ++gInstructionNo;
    }
}

bool CurrentOpenedFileHasMoreLines()
{
    return gHasMoreLines == true;
}
void close(file_pointer_t openedFile)
{
    fclose(openedFile);
    for (int i = 0; i < MAX_LINES; ++i)
    {
        free(gInstructions[i].instructionString);
        free(gInstructions[i].instructionBinaryFormat);
    }
    free(gInstructions);
    DestroySymbolTable(gHashtable);
}
int GetInstructionCount()
{
    return gInstructionNo;
}
void PrintInstruction(instruction_t* currentInstruction)
{
    char* InstructType;
    switch (currentInstruction->type)
    {
        case A_Insturction:
        {
            InstructType = "A_Instruction";
            break;
        }
        case C_Insturction:
        {
            InstructType = "C_Instruction";
            break;
        }
        case L_Insturction:
        {
            InstructType = "L_Instruction";
            break;
        }
        default:
        {
            printf("Error not a known type\n");
            break;
        }
    }

    char temp1[MAX_INSTRUCTION_SIZE];
    char temp2[MAX_INSTRUCTION_SIZE];
    char temp3[MAX_INSTRUCTION_SIZE];
    char temp4[MAX_INSTRUCTION_SIZE];

    Symbol(currentInstruction, temp1);
    Dest(currentInstruction, temp2);
    Jump(currentInstruction, temp3);
    Comp(currentInstruction, temp4);

    printf("INSTRUCTION: %s"
           "\nInstruction Binary Format: %s"
           "\nInstructionType: %s"
           "\nSymbol: %s"
           "\nDest: %s"
           "\nJump: %s"
           "\nComp: %s"
           "\nLine Size: %lu"
           "\nLineNo. :%d"
           "\n------------------------\n",
        currentInstruction->instructionString,
        currentInstruction->instructionBinaryFormat,
        InstructType,
        temp1,
        temp2,
        temp3,
        temp4,
        currentInstruction->lineSize,
        currentInstruction->lineNumber);
}

instruction_t* GetNextInstruction()
{
    static int i = 0;
    if (i < gInstructionNo)
    {

        return &gInstructions[i++];
    }
    else
    {
        printf("Last instruction was reached... returning last instruction\n");
        return &gInstructions[gInstructionNo - 1];
    }
}

void PrintAllInstructionInfo()

{
    for (int i = 0; i < gInstructionNo; ++i)
    {
        PrintInstruction(GetNextInstruction());
    }
}

void Symbol(instruction_t* currentInstruction, char* temp)
{
    switch (currentInstruction->type)
    {
        case A_Insturction:
        {

            strcpy(temp, currentInstruction->instructionString + 1);

            // printf("Addr: %s\n", temp);
            break;
        }

        case L_Insturction:
        {
            unsigned long symbolSize = currentInstruction->lineSize - 2;
            strncpy(temp, currentInstruction->instructionString + 1, symbolSize);
            temp[symbolSize] = '\0';
            // printf("Label: %s\n", temp);
            break;
        }
        case C_Insturction:
        {
            temp[0] = '\0';
            break;
        }
        default:
        {
            printf("error not a valid label instruction\n");
            break;
        }
    }
}

void Dest(instruction_t* currentInstruction, char* temp)
{
    switch (currentInstruction->type)
    {
        case A_Insturction:
        case L_Insturction:
        {

            break;
        }

        case C_Insturction:
        {
            char* insStr = currentInstruction->instructionString;
            char* eqSign = strchr(insStr, '=');
            if (eqSign != NULL)
            {
                long stringSize = eqSign - insStr;
                strncpy(temp, insStr, stringSize);
                temp[stringSize] = '\0';

                // printf("Dest: %s\n", temp);
            }
            else
            {
                temp[0] = '\0';
            }
            break;
        }
        default:
        {
            printf("error not a valid dest instruction\n");
            break;
        }
    }
}
void Comp(instruction_t* currentInstruction, char* temp)
{

    switch (currentInstruction->type)
    {
        case A_Insturction:
        case L_Insturction:
        {

            break;
        }

        case C_Insturction:
        {
            char* insStr = currentInstruction->instructionString;
            char* eqSign = strchr(insStr, '=');
            if (eqSign != NULL)
            {
                char* colSign = strchr(eqSign, ';');
                if (colSign != NULL)
                {
                    long stringSize = colSign - eqSign;
                    strncpy(temp, eqSign + 1, stringSize - 1);
                    temp[stringSize] = '\0';
                }
                else
                {

                    ulong_t insSize = strlen(insStr);
                    long stringSize = &insStr[insSize - 1] - eqSign;

                    strncpy(temp, eqSign + 1, stringSize);
                    temp[stringSize] = '\0';
                }
            }
            else
            {
                char* colSign = strchr(insStr, ';');
                if (colSign != NULL)
                {
                    long stringSize = colSign - insStr;
                    strncpy(temp, insStr, stringSize);
                    temp[stringSize] = '\0';
                }
                else
                {
                    printf("error, expected a jump expression\n");
                }
            }
            break;
        }
        default:
        {
            printf("error not a valid comp instruction\n");
            break;
        }
    }
}

void Jump(instruction_t* currentInstruction, char* temp)
{
    switch (currentInstruction->type)
    {
        case A_Insturction:
        case L_Insturction:
        {

            break;
        }

        case C_Insturction:
        {
            char* insStr  = currentInstruction->instructionString;
            char* colSign = strchr(insStr, ';');
            if (colSign != NULL)
            {
                ulong_t endStrPos = strlen(insStr) - 1;

                long stringSize = &insStr[endStrPos] - colSign;

                strncpy(temp, colSign + 1, stringSize);
                temp[stringSize] = '\0';

                if (stringSize != 3)
                {
                    printf("error expected 3 character jump expression");
                }
            }
            else
            {
                temp[0] = '\0';
            }
            break;
        }
        default:
        {
            printf("error not a valid jump instruction\n");
            break;
        }
    }
}

static int SumChars(char* temp)
{
    int index = 0;
    int sum   = 0;
    while (temp[index] != '\0')
    {
        sum += temp[index];
        ++index;
    }

    return index == 0 ? sum : sum + 2 * temp[0];
}
static void Parse_C_Instruction(instruction_t* currentInstruction, char* instructionString, CInstructionType t)
{

    // Instruction format is 111accccccdddjjj

    int sumValue = SumChars(instructionString);

    currentInstruction->instructionBinaryFormat[0] = '1';
    currentInstruction->instructionBinaryFormat[1] = '1';
    currentInstruction->instructionBinaryFormat[2] = '1';

    switch (t)
    {
        case Dest_type:
        {
            switch (sumValue)
            {
                case noDest:
                {
                    currentInstruction->dest = noDest;

                    currentInstruction->instructionBinaryFormat[10] = '0';
                    currentInstruction->instructionBinaryFormat[11] = '0';
                    currentInstruction->instructionBinaryFormat[12] = '0';
                    break;
                }
                case M:
                {
                    currentInstruction->dest = M;

                    currentInstruction->instructionBinaryFormat[10] = '0';
                    currentInstruction->instructionBinaryFormat[11] = '0';
                    currentInstruction->instructionBinaryFormat[12] = '1';
                    break;
                }

                case D:
                {
                    currentInstruction->dest = D;

                    currentInstruction->instructionBinaryFormat[10] = '0';
                    currentInstruction->instructionBinaryFormat[11] = '1';
                    currentInstruction->instructionBinaryFormat[12] = '0';
                    break;
                }
                // case MD: // this is actually illegal instruction but it has been used in the test cases and it should be DM
                case MD:
                {
                    currentInstruction->dest = MD;

                    currentInstruction->instructionBinaryFormat[10] = '0';
                    currentInstruction->instructionBinaryFormat[11] = '1';
                    currentInstruction->instructionBinaryFormat[12] = '1';
                    break;
                }
                case A:
                {
                    currentInstruction->dest = A;

                    currentInstruction->instructionBinaryFormat[10] = '1';
                    currentInstruction->instructionBinaryFormat[11] = '0';
                    currentInstruction->instructionBinaryFormat[12] = '0';
                    break;
                }
                case AM:
                {
                    currentInstruction->dest = AM;

                    currentInstruction->instructionBinaryFormat[10] = '1';
                    currentInstruction->instructionBinaryFormat[11] = '0';
                    currentInstruction->instructionBinaryFormat[12] = '1';
                    break;
                }
                case AD:
                {

                    currentInstruction->dest = AD;

                    currentInstruction->instructionBinaryFormat[10] = '1';
                    currentInstruction->instructionBinaryFormat[11] = '1';
                    currentInstruction->instructionBinaryFormat[12] = '0';
                    break;
                }
                case ADM:
                {
                    currentInstruction->dest = ADM;

                    currentInstruction->instructionBinaryFormat[10] = '1';
                    currentInstruction->instructionBinaryFormat[11] = '1';
                    currentInstruction->instructionBinaryFormat[12] = '1';
                    break;
                }
                default:
                {
                    printf("Error not a valid hash Dest value\n");
                    break;
                }
            }
            break;
        }
        case Jump_type:
        {
            switch (sumValue)
            {
                case noJump:
                {
                    currentInstruction->jump = noJump;

                    currentInstruction->instructionBinaryFormat[13] = '0';
                    currentInstruction->instructionBinaryFormat[14] = '0';
                    currentInstruction->instructionBinaryFormat[15] = '0';

                    break;
                }
                case JGT:
                {
                    currentInstruction->jump = JGT;

                    currentInstruction->instructionBinaryFormat[13] = '0';
                    currentInstruction->instructionBinaryFormat[14] = '0';
                    currentInstruction->instructionBinaryFormat[15] = '1';
                    break;
                }
                case JEQ:
                {
                    currentInstruction->jump = JEQ;

                    currentInstruction->instructionBinaryFormat[13] = '0';
                    currentInstruction->instructionBinaryFormat[14] = '1';
                    currentInstruction->instructionBinaryFormat[15] = '0';
                    break;
                }
                case JGE:
                {
                    currentInstruction->jump = JGE;

                    currentInstruction->instructionBinaryFormat[13] = '0';
                    currentInstruction->instructionBinaryFormat[14] = '1';
                    currentInstruction->instructionBinaryFormat[15] = '1';
                    break;
                }
                case JLT:
                {
                    currentInstruction->jump = JLT;

                    currentInstruction->instructionBinaryFormat[13] = '1';
                    currentInstruction->instructionBinaryFormat[14] = '0';
                    currentInstruction->instructionBinaryFormat[15] = '0';
                    break;
                }
                case JNE:
                {
                    currentInstruction->jump = JNE;

                    currentInstruction->instructionBinaryFormat[13] = '1';
                    currentInstruction->instructionBinaryFormat[14] = '0';
                    currentInstruction->instructionBinaryFormat[15] = '1';
                    break;
                }
                case JLE:
                {
                    currentInstruction->jump = JLE;

                    currentInstruction->instructionBinaryFormat[13] = '1';
                    currentInstruction->instructionBinaryFormat[14] = '1';
                    currentInstruction->instructionBinaryFormat[15] = '0';
                    break;
                }
                case JMP:
                {
                    currentInstruction->jump = JMP;

                    currentInstruction->instructionBinaryFormat[13] = '1';
                    currentInstruction->instructionBinaryFormat[14] = '1';
                    currentInstruction->instructionBinaryFormat[15] = '1';
                    break;
                }
            }
            break;
        }
        case Comp_type:
        {
            switch (sumValue)
            {
                case Zero:
                {
                    currentInstruction->comp = Zero;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '1';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '0';

                    break;
                }
                case One:
                {
                    currentInstruction->comp = One;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '1';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
                case NegOne:
                {
                    currentInstruction->comp = NegOne;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '1';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '0';

                    break;
                }
                case D_c:
                {
                    currentInstruction->comp = D_c;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '1';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '0';

                    break;
                }
                case A_c:
                {
                    currentInstruction->comp = A_c;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '0';
                    break;
                }
                case M_c:
                {
                    currentInstruction->comp = M_c;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '0';

                    break;
                }
                case NotD:
                {
                    currentInstruction->comp = NotD;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '1';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '1';

                    break;
                }
                case NotA:
                {
                    currentInstruction->comp = NotA;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '1';

                    break;
                }
                case NotM:
                {
                    currentInstruction->comp = NotM;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
                case Minus_D:
                {
                    currentInstruction->comp = Minus_D;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '1';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
                case Minus_A:
                {
                    currentInstruction->comp = Minus_A;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';

                    break;
                }
                case Minus_M:
                {
                    currentInstruction->comp = Minus_M;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
                case D_Plus_one:
                {
                    currentInstruction->comp = D_Plus_one;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '1';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';

                    break;
                }
                case M_Plus_one:
                {
                    currentInstruction->comp = M_Plus_one;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
                case A_Plus_one:
                {

                    currentInstruction->comp = A_Plus_one;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
                case D_Minus_one:
                {
                    currentInstruction->comp = D_Minus_one;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '1';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '0';
                    break;
                }
                case M_Minus_one:
                {
                    currentInstruction->comp = M_Minus_one;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '0';
                    break;
                }
                case A_Minus_one:
                {

                    currentInstruction->comp = A_Minus_one;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '1';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '0';
                    break;
                }
                case D_Plus_A:
                {
                    currentInstruction->comp = D_Plus_A;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '0';
                    break;
                }
                case D_Plus_M:
                {
                    currentInstruction->comp = D_Plus_M;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '0';
                    break;
                }
                case D_Minus_A:
                {
                    currentInstruction->comp = D_Minus_A;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';

                    break;
                }
                case D_Minus_M:
                {
                    currentInstruction->comp = D_Minus_M;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
                case A_Minus_D:
                {
                    currentInstruction->comp = A_Minus_D;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';

                    break;
                }
                case M_Minus_D:
                {
                    currentInstruction->comp = M_Minus_D;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '1';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
                case D_And_A:
                {
                    currentInstruction->comp = D_And_A;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '0';

                    break;
                }
                case D_And_M:
                {

                    currentInstruction->comp = D_And_M;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '0';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '0';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '0';
                    break;
                }
                case D_Or_A:
                {
                    currentInstruction->comp = D_Or_A;

                    currentInstruction->instructionBinaryFormat[3] = '0';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
                case D_Or_M:
                {
                    currentInstruction->comp = D_Or_M;

                    currentInstruction->instructionBinaryFormat[3] = '1';
                    currentInstruction->instructionBinaryFormat[4] = '0';
                    currentInstruction->instructionBinaryFormat[5] = '1';
                    currentInstruction->instructionBinaryFormat[6] = '0';
                    currentInstruction->instructionBinaryFormat[7] = '1';
                    currentInstruction->instructionBinaryFormat[8] = '0';
                    currentInstruction->instructionBinaryFormat[9] = '1';
                    break;
                }
            }
            break;
        }

        default:
        {
            printf("Error not a valid hash type\n");
            break;
        }
    }
}
static void Parse_A_Instruction(instruction_t* currentInstruction, char* instructionString)
{
    char firstCh = instructionString[0];
    if ((firstCh >= '0' && firstCh <= '9'))
    {
        long_t decimal = StrToInt(instructionString);
        DecimalToBinary(decimal, currentInstruction->instructionBinaryFormat);
        currentInstruction->instructionBinaryFormat[0] = '0';
    }
    else
    {
        symbol_t* symbol = GetSymbolInHashTable(gHashtable, instructionString);
        if (symbol == NULL)
        {
            //if this is the first time we see the symbol,
            //we give it the next available address
            HashtableInsertSymbol(instructionString, gNextAvailableAddr, gHashtable);

            DecimalToBinary(gNextAvailableAddr, currentInstruction->instructionBinaryFormat);
            currentInstruction->instructionBinaryFormat[0] = '0';
            ++gNextAvailableAddr;
        }

        else
        {
            DecimalToBinary(symbol->value, currentInstruction->instructionBinaryFormat);
            currentInstruction->instructionBinaryFormat[0] = '0';
        }
    }
}
static void Parse_L_Instruction(instruction_t* currentInstruction, char* instructionString)
{
    symbol_t* symbol = GetSymbolInHashTable(gHashtable, instructionString);
    if (symbol == NULL)
    {
        int nextLine = currentInstruction->lineNumber + 1;
        HashtableInsertSymbol(instructionString, nextLine, gHashtable);
    }
    else
    {

        printf("error this lable: %s was already declared at line %d\n", instructionString, symbol->value - 1);
    }
}

void ParseInstructions(void)
{
    for (int i = 0; i < gInstructionNo; ++i)
    {
        switch (gInstructions[i].type)
        {
            case A_Insturction:
            {
                char temp[MAX_INSTRUCTION_SIZE + 1];
                Symbol(&gInstructions[i], temp);
                Parse_A_Instruction(&gInstructions[i], temp);
                break;
            }
            case C_Insturction:
            {
                char temp[MAX_INSTRUCTION_SIZE + 1];
                Dest(&gInstructions[i], temp);
                Parse_C_Instruction(&gInstructions[i], temp, Dest_type);
                Jump(&gInstructions[i], temp);
                Parse_C_Instruction(&gInstructions[i], temp, Jump_type);
                Comp(&gInstructions[i], temp);
                Parse_C_Instruction(&gInstructions[i], temp, Comp_type);

                break;
            }
            case L_Insturction:
            {
                //the rest were handled already handled in PushInstructions
                break;
            }

            default:
            {
                printf("Error: Unknown instruction type \n");
                break;
            }
        }
    }
}

void WriteBinaryInstructions(char* fileName)
{
    FILE* openedFile = fopen(fileName, "w");

    char* newLine = "\n";
    for (int i = 0; i < gInstructionNo; ++i)
    {
        if (gInstructions[i].type != L_Insturction)
        {
            fwrite(gInstructions[i].instructionBinaryFormat, sizeof(char), INSTRUCTION_SIZE_BINARY,
                openedFile);
            fwrite(newLine, sizeof(char), 1, openedFile);
        }
    }
    fclose(openedFile);
}
