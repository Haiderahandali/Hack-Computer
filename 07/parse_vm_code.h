#ifndef PARSE_VMCODE_H
#define PARSE_VMCODE_H

#include "process_vm_code.h"
void InitParser(char const* pathToFile);
void PrintInstructions(void);
void WriteMachineInstructions(char const* pathToFile, lines_t* lines);
void CloseParser(void);
struct vm_code_t* GetVmInstructions(void);
#endif