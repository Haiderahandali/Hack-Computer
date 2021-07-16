#include "parse.h"

static bool gHasMoreLines;
static int gInstructionNo;
static char gBuffer[MAX_INSTRUCTION_SIZE];

static instruction_t* gInstructions;

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

            printf("%s\n", temp);
            break;
        }

        case L_Insturction:
        {
            unsigned long symbolSize = currentInstruction->lineSize - 2;
            strncpy(temp, currentInstruction->instructionString + 1, symbolSize);
            temp[symbolSize] = '\0';
            printf("%s\n", temp);
            break;
        }
        case C_Insturction:
        {
            // printf("instruction not a symbol instruction\n");
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

void Dest(instruction_t* currentInstruction)
{
    switch (currentInstruction->type)
    {
        case A_Insturction:
        case L_Insturction:
        {

            // printf("A or L instruction don't have dest \n");
            // temp[0] = '\0';
            break;
        }

        case C_Insturction:
        {
            char* insStr = currentInstruction->instructionString;
            char* eqSign = strchr(insStr, '=');
            if (eqSign != NULL)
            {
                unsigned long stringSize = eqSign - insStr;
                char temp[MAX_INSTRUCTION_SIZE];
                strncpy(temp, insStr, stringSize);
                temp[stringSize] = '\0';
                printf("Dest: %s\n", temp);
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
void Comp(instruction_t* currentInstruction)
{

    switch (currentInstruction->type)
    {
        case A_Insturction:
        case L_Insturction:
        {

            // printf("A or L instruction don't have comp \n");
            // temp[0] = '\0';
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
                    unsigned long stringSize = colSign - eqSign;
                    char temp[MAX_INSTRUCTION_SIZE];
                    strncpy(temp, eqSign, stringSize);
                    temp[stringSize] = '\0';

                    printf("%s\n", temp);
                }
                else
                {

                    int insSize = strlen(insStr);

                    unsigned long stringSize = &insStr[insSize - 1] - eqSign;
                    char temp[MAX_INSTRUCTION_SIZE];
                    strncpy(temp, eqSign + 1, stringSize);
                    temp[stringSize] = '\0';
                    printf("%s\n", temp);
                }
            }
            else
            {
                char* colSign = strchr(insStr, ';');
                if (colSign != NULL)
                {
                    int stringSize = colSign - insStr;
                    char temp[MAX_INSTRUCTION_SIZE];
                    strncpy(temp, insStr, stringSize);
                    temp[stringSize] = '\0';
                    printf("%s\n", temp);
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

void Jump(instruction_t* currentInstruction)
{
    switch (currentInstruction->type)
    {
        case A_Insturction:
        case L_Insturction:
        {

            // printf("A or L instruction don't have jump \n");
            // temp[0] = '\0';
            break;
        }

        case C_Insturction:
        {
            char* insStr  = currentInstruction->instructionString;
            char* colSign = strchr(insStr, ';');
            if (colSign != NULL)
            {
                int endStrPos = strlen(insStr) - 1;
                char temp[MAX_INSTRUCTION_SIZE];
                int stringSize = &insStr[endStrPos] - colSign;
                strncpy(temp, colSign + 1, stringSize);
                temp[stringSize] = '\0';

                if (stringSize != 3)
                {
                    printf("error expected 3 character jump expression");
                }
                else
                {
                    printf("%s\n", temp);
                }
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