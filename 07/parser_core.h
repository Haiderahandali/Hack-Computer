#ifndef PARSER_CORE_H
#define PARSER_CORE_H

#include <stdint.h>

typedef enum InstructionType
{
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL

} InstructionType;

typedef struct vm_instruction_t
{
    char* vmInstructionString;
    InstructionType vmInstructionType;
    uint32_t lineNo;

} vm_instruction_t;

typedef struct vm_code_t
{
    vm_instruction_t* vm_instructions;
    uint32_t vmLOC; //lines of code (LOC)

} vm_code_t;
#endif