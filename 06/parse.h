#ifndef PRASE_H
#define PRASE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INSTRUCTION_SIZE 16
#define MAX_LINES 1000

typedef enum Instruction_Type
{
    A_Insturction, // address instruction: @lineNumber
    C_Insturction, // execute/compute insturction: M = D - 1
    L_Insturction, // label instruction: (LABELNAME)
    E_Instruction // empty instruction, no instruction available
} Instruction_Type;

typedef struct _instruction
{
    Instruction_Type type;
    char instructionLine[MAX_INSTRUCTION_SIZE];

} instruction_t;

typedef FILE* file_pointer_t;
extern bool gHasMoreLines;

file_pointer_t InitParse(char const* path_to_file);
char advance(file_pointer_t openedFile);
bool CurrentOpenedFileHasMoreLines(void);
void PushInstruction(file_pointer_t file, char* instruction);
char const* getLineFromStream(file_pointer_t openedFile);
#endif
