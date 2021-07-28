#include "parse_vm_code.h"
#include "process_vm_code.h"

#include <stdio.h>

static void InitMain(char const* parserArg)
{
    InitParser(parserArg);
    InitVmProcess();
}
static void CloseMain()
{
    CloseParser();
    CloseVmProcess();
}

int main(int argc, char const* argv[])
{
    if (argc != 2)
    {
        printf("Usage: pass one command line argument, the name of VM file, ended with .vm as extension and first character must be Capital\n");
        return -1;
    }

    InitMain(argv[1]);
    PrintInstructions();
    PrintSplitedLines(GetVmInstructions());
    WriteMachineInstructions(argv[1], GetLines());
    CloseMain();
    return 0;
}
