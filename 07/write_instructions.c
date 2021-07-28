#include "write_instructions.h"

void PushConstant(int constantValue, FILE* openedFile)
{

    fprintf(openedFile, "@%d \n"
                        "D = A \n"
                        "@SP \n"
                        "A = M \n"
                        "M = D \n"
                        "@SP\n"
                        "M = M + 1\n",
        constantValue);
}

void Sub(FILE* openedFile)
{

    fprintf(openedFile,
        "@SP \n"
        "A = M - 1\n"
        "D = M\n"

        "@SP\n"
        "M = M - 1\n"
        "A = M - 1\n"
        "M = M - D\n");
}

void Add(FILE* openedFile)
{

    fprintf(openedFile, "@SP\n"
                        "A = M - 1\n"
                        "D = M\n"
                        "@SP\n"
                        "M = M - 1\n"
                        "A = M - 1\n"
                        "M = M + D\n");
}

void Neg(FILE* openedFile)
{

    fprintf(openedFile, "@SP\n"
                        "A = M -1 \n"
                        "M = -M\n");
}

void Not(FILE* openedFile)
{

    fprintf(openedFile,
        "@SP\n"
        "A = M - 1\n"
        "M = !M\n");
}

void And(FILE* openedFile)
{
    fprintf(openedFile,

        "@SP\n"
        "A = M - 1\n"
        "D = M\n"

        "@SP \n"
        "M = M - 1\n"
        "A = M - 1\n"

        "M = D & M\n");
}

void Or(FILE* openedFile)
{

    fprintf(openedFile,

        "@SP\n"
        "A = M - 1\n"
        "D = M\n"

        "@SP \n"
        "M = M - 1\n"
        "A = M - 1\n"

        "M = D | M\n");
}

void Equal(FILE* openedFile)
{
    static int i = 0;

    fprintf(openedFile,

        "@SP\n"
        "A = M - 1\n"
        "D = M\n"

        "@SP\n"
        "M = M - 1\n"
        "A = M - 1\n"

        "D = D - M\n"
        "@EQUAL%d\n"
        "D - M; JEQ\n"

        "@SP\n"
        "A = M - 1\n"
        "M = 0\n"
        "@EQDONE%d\n"
        "0;JMP\n"

        "(EQUAL%d)\n"
        "@SP \n"
        "A = M - 1\n"
        "M = -1\n"
        "(EQDONE%d)\n",
        i, i, i, i);
    ++i;
}
void LessThan(FILE* openedFile)
{
    static int i = 0;
    fprintf(openedFile,
        "@SP\n"
        "A = M - 1\n"
        "D = M\n"

        "@SP\n"
        "M = M - 1\n"
        "A = M - 1\n"

        "D = M - D\n"
        "@LESSTHAN%d\n"
        "D - M; JLT\n"
        "\n"

        "@SP\n"
        "A = M - 1\n"
        "M = 0\n"
        "@LTDONE%d\n"
        "0;JMP\n"

        "(LESSTHAN%d)\n"
        "@SP \n"
        "A = M - 1\n"
        "M = -1\n"

        "(LTDONE%d)\n",
        i, i, i, i);

    ++i;
}

void GreaterThan(FILE* openedFile)
{
    static int i = 0;
    fprintf(openedFile,
        "@SP\n"
        "A = M - 1\n"
        "D = M;\n"
        "@SP\n"
        "M = M - 1\n"
        "A = M - 1\n"
        "D = M - D\n"
        "@GREATERTHAN%d\n"
        "D - M; JGT\n"
        "\n"
        "//less than\n"
        "@SP\n"
        "A = M - 1\n"
        "M = 0\n"
        "@GTDONE%d\n"
        "0;JMP\n"
        "(GREATERTHAN%d)\n"
        "@SP \n"
        "A = M - 1\n"
        "M = -1\n"
        "(GTDONE%d)\n",
        i, i, i, i);
    ++i;
}

void PushArgument(int ARG, FILE* openedFile)
{
    /*
    @ARG 
    D = A

    @ARG 
    A = M + D   
    D = M 

    @SP 
    M = M + 1
    A = M - 1
    M = D
    */

    fprintf(openedFile,
        "@%d \n"
        "D = A\n"

        "@ARG \n"
        "A = M + D   \n"
        "D = M \n"

        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        ARG);
}
void PushThat(int THAT, FILE* openedFile)
{
    //same as PushArgment, except we load the THIS instead of ARG

    fprintf(openedFile,
        "@%d \n"
        "D = A\n"

        "@THAT \n"
        "A = M + D   \n"
        "D = M \n"

        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        THAT);
}
void PushLocal(int LCL, FILE* openedFile)
{

    //same as PushArgment, except we load the LCL instead of ARG

    fprintf(openedFile,
        "@%d \n"
        "D = A\n"

        "@LCL \n"
        "A = M + D   \n"
        "D = M \n"

        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        LCL);
}
void PushThis(int THIS, FILE* openedFile)
{
    //same as PushArgment, except we load the THIS instead of ARG

    fprintf(openedFile,
        "@%d \n"
        "D = A\n"

        "@THIS \n"
        "A = M + D   \n"
        "D = M \n"

        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        THIS);
}
void PushTemp(int TEMP, FILE* openedFile)
{
    fprintf(openedFile,
        "@R%d\n"
        "D = M \n"
        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        5 + TEMP);
}
void PushPointer(int pointerLocation, FILE* openedFile)
{

    if (pointerLocation == 1)
    {
        fprintf(openedFile,
            "@THAT\n"
            " D = M\n"
            " @SP \n"
            " M = M + 1\n"
            " A = M - 1\n"
            " M = D\n");
    }
    else if (pointerLocation == 0)
    {
        fprintf(openedFile,
            "@THIS\n"
            " D = M\n"
            " @SP \n"
            " M = M + 1\n"
            " A = M - 1\n"
            " M = D\n");
    }
    else
    {
        printf("Error, expected pointer to be 0 or 1...returning \n");
        return;
    }
    /*
    @THAT
    D = M

    @SP 
    M = M + 1
    A = M - 1

    M = D
    */
}

void PushStatic(int STATIC, FILE* openedFile)
{
    fprintf(openedFile,
        "@Foo.%d\n"
        "D = M \n"

        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        STATIC);
}

void PopStatic(int STATIC, FILE* openedFile)
{
    fprintf(openedFile,
        "@SP \n"
        "M = M - 1\n"
        "A = M\n"
        "D = M\n"

        "@Foo.%u \n"
        "M = D\n",
        STATIC);
}
void PopTemp(int TEMP, FILE* openedFile)
{
    fprintf(openedFile,

        "@SP\n"
        "M = M - 1\n"
        "A = M\n"
        "D = M \n"

        "@R%d\n"
        "M = D\n",
        5 + TEMP);
}
void PopArgument(int ARG, FILE* openedFile)
{
    /**
     * 
     * 
     @ArgLoc
     D = A
     @ARG 
     D = M + D
    @R15
    M = D
    
    @SP

     M = M - 1
     A = M

     D = M 
     @R15
    A = M
    M = D
    
    */

    fprintf(openedFile,
        "@%d\n"
        "D = A\n"
        "@ARG \n"
        "D = M + D\n"
        "@R15\n"
        "M = D\n"

        "@SP\n"

        "M = M - 1\n"
        "A = M\n"

        "D = M \n"
        "@R15\n"
        "A = M\n"
        "M = D\n",
        ARG);
}
void PopLocal(int LCL, FILE* openedFile)
{

    fprintf(openedFile,
        "@%d\n"
        "D = A\n"
        "@LCL \n"
        "D = M + D\n"
        "@R15\n"
        "M = D\n"

        "@SP\n"

        "M = M - 1\n"
        "A = M\n"

        "D = M \n"
        "@R15\n"
        "A = M\n"
        "M = D\n",
        LCL);
}
void PopThat(int THAT, FILE* openedFile)
{
    fprintf(openedFile,
        "@%d\n"
        "D = A\n"
        "@THAT \n"
        "D = M + D\n"
        "@R15\n"
        "M = D\n"

        "@SP\n"

        "M = M - 1\n"
        "A = M\n"

        "D = M \n"
        "@R15\n"
        "A = M\n"
        "M = D\n",
        THAT);
}
void PopThis(int THIS, FILE* openedFile)
{
    fprintf(openedFile,
        "@%d\n"
        "D = A\n"
        "@THIS \n"
        "D = M + D\n"
        "@R15\n"
        "M = D\n"

        "@SP\n"

        "M = M - 1\n"
        "A = M\n"

        "D = M \n"
        "@R15\n"
        "A = M\n"
        "M = D\n",
        THIS);
}

void PopPointer(int pointerLocation, FILE* openedFile)
{
    if (pointerLocation == 1)
    {
        fprintf(openedFile,

            " @SP \n"
            " M = M - 1\n"
            " A = M\n"
            " D = M\n"

            "@THAT\n"
            " M = D\n");
    }
    else if (pointerLocation == 0)
    {
        fprintf(openedFile,

            " @SP \n"
            " M = M - 1\n"
            " A = M\n"
            " D = M\n"

            "@THIS\n"
            " M = D\n");
    }
    else
    {
        printf("Error, expected pointer to be 0 or 1...returning \n");
        return;
    }
}

void SetInfiniteLoop(FILE* openedFile)
{
    fprintf(openedFile, "(END)\n"
                        "@END\n"
                        "0;JMP\n");
}
