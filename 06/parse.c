#include "parse.h"

static int gInstructionNo;
static char gBuffer[MAX_INSTRUCTION_SIZE];
static instruction_t* gInstructions;

bool gHasMoreLines;

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
            printf("Insturction String size is above maximum (16 characters), skipping to next instruction ....\n");
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
int InstructionsCount()
{
    return gInstructionNo + 1;
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