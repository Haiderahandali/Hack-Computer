#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parse_vm_code.h"
#include "parser_core.h"
#include "write_instructions.h"

#define MAX_LOC 30000 //maximum number of vm instructions
#define LINE_BUFFER_SIZE 256 // 256 characters in a single line

typedef FILE* file_ptr_t;

static vm_code_t* gVmInstructions;
static uint32_t gCurrentInstructionNo;

static void PushLine(char* lineBuffer, uint32_t* lastCharIndex)
{
    if (*lastCharIndex == 0)
    {
        return;
    }
    lineBuffer[*lastCharIndex] = '\0';

    gVmInstructions->vm_instructions[gCurrentInstructionNo].vmInstructionString = strdup(lineBuffer);
    gVmInstructions->vm_instructions[gCurrentInstructionNo].lineNo              = gCurrentInstructionNo + 1;

    ++gCurrentInstructionNo;

    *lastCharIndex = 0;
}
static void ProcessCode(file_ptr_t pathToSourceCode)
{
    char lineBuffer[LINE_BUFFER_SIZE];

    int c;

    uint32_t currentCharIndex = 0;

    while ((c = fgetc(pathToSourceCode)) != EOF)
    {
        switch (c)
        {
            case '\n':
            case '\r':
            {
                PushLine(lineBuffer, &currentCharIndex);
                break;
            }

            case '/':
            {
                int nextSlash;
                if ((nextSlash = fgetc(pathToSourceCode)) != '/')
                {
                    printf("expected next slash in a comment....existing program\n");
                    exit(1);
                }
                else
                {
                    while (nextSlash != EOF && nextSlash != '\n')
                    {
                        nextSlash = fgetc(pathToSourceCode);
                    }
                    PushLine(lineBuffer, &currentCharIndex);
                }
                break;
            }

            default:
            {
                lineBuffer[currentCharIndex] = (char)c;
                ++currentCharIndex;

                break;
            }
        }
    }
    if (currentCharIndex > 0)
    {
        lineBuffer[currentCharIndex]                                                  = '\0';
        gVmInstructions->vm_instructions[gCurrentInstructionNo++].vmInstructionString = strdup(lineBuffer);
    }
    gVmInstructions->vmLOC = gCurrentInstructionNo;
}

void InitParser(char const* pathToFile)
{
    char* extension = strchr(pathToFile, '.');
    if (extension != NULL)
    {
        if (strcmp(extension, ".vm") == 0)
        {
            file_ptr_t vmSourceCodeFile = fopen(pathToFile, "r");
            if (vmSourceCodeFile == NULL)
            {
                printf("error, couldn't open vmSourceCodeFile ... returning\n");
                return;
            }

            gVmInstructions = malloc(sizeof(vm_code_t));

            gVmInstructions->vm_instructions = malloc(sizeof(vm_instruction_t) * MAX_LOC);
            gVmInstructions->vmLOC           = 0;
            gCurrentInstructionNo            = 0;

            ProcessCode(vmSourceCodeFile);
            fclose(vmSourceCodeFile);
        }
    }
}
void PrintInstructions(/*char const* logFile*/)
{
    file_ptr_t logFile = fopen("InstructionLog.txt", "w+");
    if (logFile == NULL)
    {
        printf("couldn't open logFile ...retunring\n");
        return;
    }
    if (!gCurrentInstructionNo)
    {
        return;
    }

    for (uint32_t i = 0; i < gCurrentInstructionNo; ++i)
    {
        fprintf(logFile, "Line Str: %s\n", gVmInstructions->vm_instructions[i].vmInstructionString);
    }

    fprintf(logFile, "VM_LOC = %d\n", gVmInstructions->vmLOC);
    fclose(logFile);
}
void WriteMachineInstructions(output_struct_t* o, lines_t* instructionLines, char* fileName)
{

    //------------ Opening/Preparing Output file --------------//

    //reading instructions of each line, one line at a time

    FILE* openFile = o->output;

    static bool init = false;
    if (!init)
    {

        SysInit(openFile);
        init = true;
    }
    for (int currentLine = 0, lineCount = instructionLines->lineCount; currentLine < lineCount; ++currentLine)
    {

        //todo hash those values in the instruction arguments instead of strings
        if (instructionLines->lines[currentLine].wordCount == 1)
        {
            if (strcmp(instructionLines->lines[currentLine].words[0], "add") == 0)
            {
                Add(openFile);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "sub") == 0)
            {
                Sub(openFile);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "neg") == 0)
            {
                Neg(openFile);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "eq") == 0)
            {
                Equal(openFile);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "gt") == 0)
            {
                GreaterThan(openFile);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "lt") == 0)
            {
                LessThan(openFile);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "and") == 0)
            {
                And(openFile);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "or") == 0)
            {
                Or(openFile);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "not") == 0)
            {
                Not(openFile);
            }

            else if (strcmp(instructionLines->lines[currentLine].words[0], "return") == 0)
            {
                ReturnFunc(openFile);
            }
            else
            {
                printf("Operation not supported for now\n");
                break;
            }
        }
        else if (instructionLines->lines[currentLine].wordCount == 2)
        {
            if (strcmp(instructionLines->lines[currentLine].words[0], "label") == 0)
            {
                WriteLabel(openFile, instructionLines->lines[currentLine].words[1]);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "if-goto") == 0)
            {
                WriteIfGoto(openFile, instructionLines->lines[currentLine].words[1]);
            }

            else if (strcmp(instructionLines->lines[currentLine].words[0], "goto") == 0)
            {
                WriteGoto(openFile, instructionLines->lines[currentLine].words[1]);
            }

            else
            {
                printf("Only if-goto and label are supported\n");
            }
        }
        else if (instructionLines->lines[currentLine].wordCount == 3)
        {
            int value = (int)strtol(instructionLines->lines[currentLine].words[2], (char**)NULL, 10);
            if (strcmp(instructionLines->lines[currentLine].words[0], "push") == 0)
            {
                if (strcmp(instructionLines->lines[currentLine].words[1], "constant") == 0)
                {
                    PushConstant(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "argument") == 0)
                {
                    PushArgument(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "local") == 0)
                {
                    PushLocal(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "this") == 0)
                {
                    PushThis(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "that") == 0)
                {
                    PushThat(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "pointer") == 0)
                {
                    PushPointer(value, openFile);
                }

                else if (strcmp(instructionLines->lines[currentLine].words[1], "temp") == 0)
                {
                    PushTemp(value, openFile);
                }

                else if (strcmp(instructionLines->lines[currentLine].words[1], "static") == 0)
                {
                    PushStatic(value, openFile, fileName);
                }

                else
                {
                    printf("only constant,argument,local,this, that & pointer pushing is supported for now \n");
                }
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "pop") == 0)
            {
                if (strcmp(instructionLines->lines[currentLine].words[1], "argument") == 0)
                {
                    PopArgument(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "local") == 0)
                {
                    PopLocal(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "this") == 0)
                {
                    PopThis(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "that") == 0)
                {
                    PopThat(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "pointer") == 0)
                {
                    PopPointer(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "temp") == 0)
                {
                    PopTemp(value, openFile);
                }
                else if (strcmp(instructionLines->lines[currentLine].words[1], "static") == 0)
                {
                    PopStatic(value, openFile, fileName);
                }
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "function") == 0)
            {
                GenerateFunctionLable(openFile, instructionLines->lines[currentLine].words[1], value);
            }
            else if (strcmp(instructionLines->lines[currentLine].words[0], "call") == 0)
            {
                CallFunction(openFile, instructionLines->lines[currentLine].words[1], value);
            }
            else
            {
                printf("only push and pop is supported for now\n");
            }
        }
        else
        {
            printf("Only one operation or 3 words comamnd are supported for now \n");
            break;
        }
    }
}

void CloseParser()
{
    if (gVmInstructions == NULL)
    {
        printf("empty file ... returning\n");
        return;
    }
    for (uint32_t i = 0, size = gVmInstructions->vmLOC; i < size; ++i)
    {
        free(gVmInstructions->vm_instructions[i].vmInstructionString);
    }
    free(gVmInstructions->vm_instructions);
    free(gVmInstructions);
}

vm_code_t* GetVmInstructions()
{
    return gVmInstructions;
}

void CloseOutputStruct(output_struct_t** out_ptr)
{
    if (*out_ptr != NULL)
    {
        output_struct_t* output = *out_ptr;

        fclose(output->output);
        free(output->fileName);
        free(*out_ptr);
        *out_ptr = NULL;
    }
    else
    {
        printf("the file has already been freed\n");
        return;
    }
}
output_struct_t* CreateOutputStruct(char const* pathToFile)
{
    uint32_t size = (uint32_t)strlen(pathToFile);
    char outputFileName[LINE_BUFFER_SIZE];

    strcpy(outputFileName, pathToFile);
    if (strchr(pathToFile, '.'))

    {
        outputFileName[size + 1] = '\0';
        outputFileName[size]     = 'm';
        outputFileName[size - 1] = 's';
        outputFileName[size - 2] = 'a';
    }
    else
    {
        outputFileName[size + 0] = '.';
        outputFileName[size + 1] = 'a';
        outputFileName[size + 2] = 's';
        outputFileName[size + 3] = 'm';
        outputFileName[size + 4] = '\0';
    }

    FILE* openFile = fopen(outputFileName, "w");

    output_struct_t* f = malloc(sizeof(output_struct_t));
    f->output          = openFile;
    f->fileName        = strdup(outputFileName);
    return f;
}