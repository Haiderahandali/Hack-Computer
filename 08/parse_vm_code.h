#ifndef PARSE_VMCODE_H
#define PARSE_VMCODE_H

#include "process_vm_code.h"
#include <stdio.h>

output_struct_t* CreateOutputStruct(char const* pathToFile);
void CloseOutputStruct(output_struct_t** f_ptr);
void WriteIunstruction(output_struct_t* o, char* filename);

void InitParser(char const* pathToFile);
void PrintInstructions(void);
void WriteMachineInstructions(output_struct_t* output, lines_t* lines, char* filename);
void CloseParser(void);
struct vm_code_t* GetVmInstructions(void);

output_struct_t* CreateOutputStruct(char const* pathToFile);
void CloseOutputStruct(output_struct_t** f_ptr);
void SetInfiniteLoop(FILE* openFile);
#endif