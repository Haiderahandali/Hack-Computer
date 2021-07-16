#ifndef PRASE_H
#define PRASE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INSTRUCTION_SIZE 32
#define MAX_LINES 1000

typedef FILE* file_pointer_t;
typedef unsigned long ulong_t;

typedef enum Instruction_Type
{
    A_Insturction, // address instruction: @lineNumber
    C_Insturction, // execute/compute insturction: M = D - 1
    L_Insturction, // label instruction: (LABELNAME)
} Instruction_Type;

typedef struct _instruction
{
    Instruction_Type type;
    char instructionString[MAX_INSTRUCTION_SIZE];
    int lineNumber;
    ulong_t lineSize;

} instruction_t;

extern bool gHasMoreLines;

file_pointer_t InitParse(char const* path_to_file);
bool CurrentOpenedFileHasMoreLines(void);
char const* getLineFromStream(file_pointer_t openedFile);
instruction_t* GetNextInstruction();

void close(file_pointer_t openedFile);
void PushInstruction(char const* instruction);
void PrintInstruction(instruction_t* instruction);
void PrintInstructions(void);
#endif
