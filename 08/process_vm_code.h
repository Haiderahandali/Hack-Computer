#ifndef PROCESS_VM_CODE_H
#define PROCESS_VM_CODE_H
#include "parser_core.h"
typedef struct words_t
{
    char** words;
    int wordCount;

} words_t;

typedef struct lines_t
{
    words_t* lines;
    int lineCount;

} lines_t;

void SplitWords(char* line);

void InitVmProcess(void);
void CloseVmProcess(void);
void PrintSplitedLines(vm_code_t* vmInstructions);

lines_t* GetLines(void);

#endif