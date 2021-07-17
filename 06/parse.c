#include "parse.h"

static bool gHasMoreLines;
static int gInstructionNo;
static char gBuffer[MAX_INSTRUCTION_SIZE];

static void Parse_C_Instruction(instruction_t* currentInstruction, char* instructionString, CInstructionType t);
static void Parse_A_Instruction(instruction_t* currentInstruction, char* instructionString);
static instruction_t* gInstructions;

static int StrToInt(char* src)
{
    int size  = (int)strlen(src);
    int value = 0;

    for (int i = 0; i < size; ++i)
    {
        int currentCharValue = src[i] - '0';
        value                = (value * 10) + currentCharValue;
    }

    printf("value = %d\n", value);

    return value;
}

static void DecimalToBinary(char* src, char* buffer)
{
    int decimal = StrToInt(src);
    if (decimal >> 15 > 0)
    {
        return;
    }

    for (int j = 0; j < INSTRUCTION_SIZE_BINARY; ++j)
    {
        // printf("%d \n",   (decimal & (1 << (INSTRUCTION_SIZE_BINARY - (j +1))))!= 0         );
        buffer[j] += (decimal & (1 << (INSTRUCTION_SIZE_BINARY - (j + 1)))) != 0;
    }

    buffer[INSTRUCTION_SIZE_BINARY] = '\0';
}

file_pointer_t InitParse(char const* pathToFile)
{

    gInstructionNo = 0;
    gHasMoreLines  = true;
    gInstructions  = (instruction_t*)malloc(sizeof(instruction_t) * MAX_LINES);
    return fopen(pathToFile, "r");
}

//This already strip out extra tokens such as whitespaces, comments
char const* getLineFromStream(file_pointer_t openedFile)
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
    static int lineNo  = 0;
    if (stringSize > 0) //if not am empty instruction do nothing
    {
        if (stringSize >= 16)
        {
            printf("instruction String size is above maximum (16 characters), skipping to next instruction ....\n");
            return;
        }
        gInstructions[gInstructionNo].lineSize   = stringSize;
        gInstructions[gInstructionNo].lineNumber = ++lineNo;
        strcpy(gInstructions[gInstructionNo].instructionString, instructionLine);

        char firstCh = instructionLine[0];
        switch (firstCh)
        {
            case '@':
            {
                gInstructions[gInstructionNo].type = A_Insturction;
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
                    gInstructions[gInstructionNo].type = L_Insturction;
                }
                break;
            }
            default:
            {
                gInstructions[gInstructionNo].type = C_Insturction;
                break;
            }
        }

        char initStr[17] = "0000000000000000";

        strcpy(gInstructions[gInstructionNo].instructionBinaryFormat, initStr);
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
    free(gInstructions);
}
int GetInstructionCount()
{
    return gInstructionNo;
}
void PrintInstruction(instruction_t* instruction)
{
    char* InstructType;
    switch (instruction->type)
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

    printf("INSTRUCTION: %s\nInstructionType: %s\nLine Size: %lu\nLineNo. :%d\n------------------------\n",
        instruction->instructionString,
        InstructType,
        instruction->lineSize,
        instruction->lineNumber);
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

void PrintInstructions()

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

                // int hashValue = HashInstruction(currentInstruction, temp, Dest_type);
                printf("Dest: %s\n", temp);
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
                    strncpy(temp, eqSign, stringSize);
                    temp[stringSize] = '\0';

                    printf("Comp: %s\n", temp);
                }
                else
                {

                    ulong_t insSize = strlen(insStr);
                    long stringSize = &insStr[insSize - 1] - eqSign;
                    char temp[MAX_INSTRUCTION_SIZE];
                    strncpy(temp, eqSign + 1, stringSize);
                    temp[stringSize] = '\0';
                    printf("Comp: %s\n", temp);
                }
            }
            else
            {
                char* colSign = strchr(insStr, ';');
                if (colSign != NULL)
                {
                    long stringSize = colSign - insStr;
                    char temp[MAX_INSTRUCTION_SIZE];
                    strncpy(temp, insStr, stringSize);
                    temp[stringSize] = '\0';
                    printf("Comp: %s\n", temp);
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
                else
                {
                    printf("Jump: %s\n", temp);
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

static int sumChars(char* temp)
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

    int hashValue = sumChars(instructionString);

    currentInstruction->instructionBinaryFormat[1] = '1';
    currentInstruction->instructionBinaryFormat[2] = '1';

    switch (t)
    {
        case Dest_type:
        {
            switch (hashValue)
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
                case DM:
                {
                    currentInstruction->dest = DM;

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
            switch (hashValue)
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
            switch (hashValue)
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
        DecimalToBinary(instructionString, currentInstruction->instructionBinaryFormat);
        currentInstruction->instructionBinaryFormat[0] = '0';
    }
    else
    {
        printf("symbols are not supported yet");
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
                char temp[INSTRUCTION_SIZE_BINARY + 1];
                Symbol(&gInstructions[i], temp);
                Parse_A_Instruction(&gInstructions[i], temp);
                printf("%s\n", gInstructions[i].instructionBinaryFormat);
                break;
            }
            case C_Insturction:
            {
                char temp[INSTRUCTION_SIZE_BINARY + 1];
                Dest(&gInstructions[i], temp);
                Parse_C_Instruction(&gInstructions[i], temp, Dest_type);
                Jump(&gInstructions[i], temp);
                Parse_C_Instruction(&gInstructions[i], temp, Jump_type);
                Comp(&gInstructions[i], temp);
                Parse_C_Instruction(&gInstructions[i], temp, Comp_type);

                printf("%s\n", gInstructions[i].instructionBinaryFormat);
                break;
            }

            default:
            {
                printf("not supported for now\n");
                break;
            }
        }
    }
}
