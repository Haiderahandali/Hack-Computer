#ifndef PRASE_H
#define PRASE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INSTRUCTION_SIZE 32
#define INSTRUCTION_SIZE_BINARY 16
#define MAX_LINES 1000

typedef FILE* file_pointer_t;
typedef unsigned long ulong_t;

typedef enum Instruction_Type
{
    A_Insturction, // address instruction: @lineNumber
    C_Insturction, // execute/compute insturction: M = D - 1
    L_Insturction, // label instruction: (LABELNAME)
} Instruction_Type;

typedef enum Dest_Instruction
{
    noDest = (3 * 0),
    M      = (3 * 'M'),
    D      = (3 * 'D'),
    DM     = (3 * 'D') + 'M',
    A      = (3 * 'A'),
    AM     = (3 * 'A') + 'M',
    AD     = (3 * 'A') + 'D',
    ADM    = (3 * 'A') + 'D' + 'M',

} Dest_Instruction;

typedef enum Jump_Instruction
{
    noJump = 0,
    JGT    = (3 * 'J') + 'G' + 'T',
    JEQ    = (3 * 'J') + 'E' + 'Q',
    JGE    = (3 * 'J') + 'G' + 'E',
    JLT    = (3 * 'J') + 'L' + 'T',
    JNE    = (3 * 'J') + 'N' + 'E',
    JLE    = (3 * 'J') + 'L' + 'E',
    JMP    = (3 * 'J') + 'M' + 'P'
} Jump_Instruction;

typedef enum Comp_Instruction
{
    Zero        = (3 * '0'),
    One         = (3 * '1'),
    NegOne      = (3 * '-') + '1',
    D_c         = (3 * 'D'),
    A_c         = (3 * 'A'),
    M_c         = (3 * 'M'),
    NotD        = (3 * '!') + 'D',
    NotA        = (3 * '!') + 'A',
    NotM        = (3 * '!') + 'M',
    Minus_D     = (3 * 'D') + '-',
    Minus_A     = (3 * 'A') + '-',
    Minus_M     = (3 * 'M') + '-',
    D_Plus_one  = (3 * 'D') + '+' + '1',
    M_Plus_one  = (3 * 'M') + '+' + '1',
    A_Plus_one  = (3 * 'A') + '+' + '1',
    D_Minus_one = (3 * 'D') + '-' + '1',
    M_Minus_one = (3 * 'M') + '-' + '1',
    A_Minus_one = (3 * 'A') + '-' + '1',
    D_Plus_A    = (3 * 'D') + '+' + 'A',
    D_Plus_M    = (3 * 'D') + '+' + 'M',
    D_Minus_A   = (3 * 'D') + '-' + 'A',
    D_Minus_M   = (3 * 'D') + '-' + 'M',
    A_Minus_D   = (3 * 'A') + '-' + 'D',
    M_Minus_D   = (3 * 'M') + '-' + 'D',
    D_And_A     = (3 * 'D') + '&' + 'A',
    D_And_M     = (3 * 'D') + '&' + 'M',
    D_Or_A      = (3 * 'D') + '|' + 'A',
    D_Or_M      = (3 * 'D') + '|' + 'M',

} Comp_Instruction;

typedef struct _instruction
{
    Instruction_Type type;
    char instructionString[MAX_INSTRUCTION_SIZE];
    char instructionBinaryFormat[INSTRUCTION_SIZE_BINARY + 1];
    int lineNumber;
    ulong_t lineSize;

    Comp_Instruction comp;
    Dest_Instruction dest;
    Jump_Instruction jump;

} instruction_t;

file_pointer_t InitParse(char const* path_to_file);
bool CurrentOpenedFileHasMoreLines(void);
char const* getLineFromStream(file_pointer_t openedFile);
instruction_t* GetNextInstruction();
int GetInstructionCount();

void close(file_pointer_t openedFile);
void PushInstruction(char const* instruction);
void PrintInstruction(instruction_t* instruction);
void PrintInstructions(void);

void Symbol(instruction_t* currentInstruction, char* stringBuffer);
void Dest(instruction_t* currentInstruction, char* stringBuffer);
void Comp(instruction_t* currentInstruction, char* stringBuffer);
void Jump(instruction_t* currentInstruction, char* stringBuffer);

typedef enum CInstructionType
{
    Dest_type,
    Comp_type,
    Jump_type,

} CInstructionType;

void ParseInstructions(void);

#endif
