#ifndef WRITE_INSTRUCTION_H
#define WRITE_INSTRUCTION_H
#include <stdio.h>

void PushConstant(int constantValue, FILE* openedFile);

void Add(FILE* openedFile);
void Sub(FILE* openedFile);
void Or(FILE* openedFile);
void Not(FILE* openedFile);
void And(FILE* openedFile);
void Equal(FILE* openedFile);
void LessThan(FILE* openedFile);
void GreaterThan(FILE* openedFile);
void Neg(FILE* openedFile);

void PushArgument(int location, FILE* openFile);
void PushLocal(int value, FILE* openFile);
void PushThat(int value, FILE* openFile);
void PushThis(int value, FILE* openFile);

void PushTemp(int value, FILE* openFile);
void PushStatic(int value, FILE* openedFile, char* fileName);

void PopArgument(int location, FILE* openFile);
void PopLocal(int value, FILE* openFile);
void PopThat(int value, FILE* openFile);
void PopThis(int value, FILE* openFile);

void PopPointer(int pointer, FILE* openFile);
void PushPointer(int pointer, FILE* openFile);

void PopTemp(int value, FILE* openFile);
void PopStatic(int STATIC, FILE* openedFile, char* fileName);

void WriteLabel(FILE* openFile, char* label);
void WriteIfGoto(FILE* openFile, char* label);
void WriteGoto(FILE* openFile, char* label);
void SetInfiniteLoop(FILE* openedFile);
void GenerateFunctionLable(FILE* openedFile, char* functionName, int nVars);
void ReturnFunc(FILE* openFile);
void CallFunction(FILE* openFile, char* functionName, int nArgs);
#endif