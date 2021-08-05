#include "write_instructions.h"
#include <string.h>
void PushConstant(int constantValue, FILE* openedFile)
{

    fprintf(openedFile, "//Push Constant %d\n"
                        "@%d \n"
                        "D = A \n"
                        "@SP \n"
                        "A = M \n"
                        "M = D \n"
                        "@SP\n"
                        "M = M + 1\n",
        constantValue, constantValue);
}

void Sub(FILE* openedFile)
{

    fprintf(openedFile,
        "//Sub\n"
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

    fprintf(openedFile, "//Add\n"
                        "@SP\n"
                        "A = M - 1\n"
                        "D = M\n"
                        "@SP\n"
                        "M = M - 1\n"
                        "A = M - 1\n"
                        "M = M + D\n");
}

void Neg(FILE* openedFile)
{

    fprintf(openedFile, "//Neg\n"
                        "@SP\n"
                        "A = M -1 \n"
                        "M = -M\n");
}

void Not(FILE* openedFile)
{

    fprintf(openedFile, "//Not\n"
                        "@SP\n"
                        "A = M - 1\n"
                        "M = !M\n");
}

void And(FILE* openedFile)
{
    fprintf(openedFile,
        "//And\n"
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
        "//OR\n"
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
        "//Equal\n"
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
        "//Less Than\n"
        "@SP\n"
        "A = M - 1\n"
        "D = M\n"

        "@SP\n"
        "M = M - 1\n"
        "A = M - 1\n"

        "D = M - D\n"
        "@LESSTHAN%d\n"
        "D; JLT\n"
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
        "//Greater Than \n"
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
    fprintf(openedFile,
        "// Push Arg %d\n"
        "@%d \n"
        "D = A\n"

        "@ARG \n"
        "A = M + D   \n"
        "D = M \n"

        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        ARG,
        ARG);
}
void PushThat(int THAT, FILE* openedFile)
{
    //same as PushArgment, except we load the THIS instead of ARG

    fprintf(openedFile,
        "//Push That %d\n"
        "@%d \n"
        "D = A\n"

        "@THAT \n"
        "A = M + D   \n"
        "D = M \n"

        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        THAT, THAT);
}
void PushLocal(int LCL, FILE* openedFile)
{

    //same as PushArgment, except we load the LCL instead of ARG

    fprintf(openedFile,
        "//Push Local %d\n"
        "@%d \n"
        "D = A\n"

        "@LCL \n"
        "A = M + D   \n"
        "D = M \n"

        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        LCL, LCL);
}
void PushThis(int THIS, FILE* openedFile)
{
    //same as PushArgment, except we load the THIS instead of ARG

    fprintf(openedFile,
        "//Push This %d\n"
        "@%d \n"
        "D = A\n"

        "@THIS \n"
        "A = M + D   \n"
        "D = M \n"

        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        THIS, THIS);
}
void PushTemp(int TEMP, FILE* openedFile)
{
    fprintf(openedFile,
        "//Push Temp %d\n"
        "@R%d\n"
        "D = M \n"
        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n",
        TEMP, 5 + TEMP);
}
void PushPointer(int pointerLocation, FILE* openedFile)
{

    if (pointerLocation == 1)
    {
        fprintf(openedFile,
            "//Push Pointer THAT\n"
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
            "//Push Pointer THIS\n"
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
}

void PushStatic(int STATIC, FILE* openedFile, char* fileName)
{
    char* slash = strchr(fileName, '/');
    if (slash != NULL)
    {
        PushStatic(STATIC, openedFile, (slash + 1));
    }
    else
    {
        fprintf(openedFile,
            "//Push static %d\n"
            "@%s.%d\n"
            "D = M \n"

            "@SP \n"
            "M = M + 1\n"
            "A = M - 1\n"
            "M = D\n",
            STATIC, fileName, STATIC);
    }
}

void PopStatic(int STATIC, FILE* openedFile, char* fileName)
{
    char* slash = strchr(fileName, '/');
    if (slash != NULL)
    {
        PopStatic(STATIC, openedFile, (slash + 1));
    }
    else
    {

        fprintf(openedFile,
            "//Pop Static %d \n"
            "@SP \n"
            "M = M - 1\n"
            "A = M\n"
            "D = M\n"

            "@%s.%d \n"
            "M = D\n",
            STATIC, fileName, STATIC);
    }
}
void PopTemp(int TEMP, FILE* openedFile)
{
    fprintf(openedFile,
        "//Pop Temp %d\n"
        "@SP\n"
        "M = M - 1\n"
        "A = M\n"
        "D = M \n"

        "@R%d\n"
        "M = D\n",
        TEMP, 5 + TEMP);
}
void PopArgument(int ARG, FILE* openedFile)
{

    fprintf(openedFile,
        "//Pop Argument %d \n"
        "@%d\n"
        "D = A\n"
        "@ARG \n"
        "D = M + D\n"
        "@R13\n"
        "M = D\n"

        "@SP\n"

        "M = M - 1\n"
        "A = M\n"

        "D = M \n"
        "@R13\n"
        "A = M\n"
        "M = D\n",
        ARG, ARG);
}
void PopLocal(int LCL, FILE* openedFile)
{

    fprintf(openedFile,
        "//Pop Local %d \n"
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
        LCL, LCL);
}
void PopThat(int THAT, FILE* openedFile)
{
    fprintf(openedFile,
        "//Pop That %d\n"
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
        THAT, THAT);
}
void PopThis(int THIS, FILE* openedFile)
{
    fprintf(openedFile,
        "//Pop This %d\n"
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
        THIS, THIS);
}

void PopPointer(int pointerLocation, FILE* openedFile)
{
    if (pointerLocation == 1)
    {
        fprintf(openedFile,
            "//Pop Pointer THAT\n"
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
            "//Pop Pointer THIS\n"
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

//--------------- Branches handling --------------//

void WriteIfGoto(FILE* openedFile, char* label)
{

    fprintf(openedFile,
        "//Write If Goto %s\n"
        "@SP\n"
        "M = M - 1\n"
        "A = M\n"
        "D = M\n"
        "@%s\n"
        "D;JNE\n",
        label, label);
}

void ReturnFunc(FILE* openedFile)
{

    fprintf(openedFile,
        "//Return Function\n"
        "@LCL\n"
        "D = M\n"
        "@R15 \n"
        "M = D\n"

        "@5\n"
        "D = A\n"
        "@R15\n"
        "A = M - D\n"
        "D = M\n"
        "@R14 \n"
        "M = D  \n");
    PopArgument(0, openedFile);
    fprintf(openedFile,
        "@ARG \n"
        "D = M + 1\n"
        "@SP\n"
        "M = D\n"

        "@1\n"
        "D = A\n"
        "@R15\n"
        "A = M - D\n"
        "D = M\n"
        "@THAT \n"
        "M = D\n"

        "@2\n"
        "D = A\n"
        "@R15\n"
        "A = M - D\n"
        "D = M\n"
        "@THIS \n"
        "M = D\n"

        "@3\n"
        "D = A\n"
        "@R15\n"
        "A = M - D\n"
        "D = M\n"
        "@ARG \n"
        "M = D\n"

        "@4\n"
        "D = A\n"
        "@R15\n"
        "A = M - D\n"
        "D = M\n"
        "@LCL \n"
        "M = D\n"

        "@R14\n"
        "A = M\n"
        "0;JMP\n");
}

void WriteGoto(FILE* openedFile, char* label)
{
    fprintf(openedFile,
        "//Write goto %s\n"
        "@%s\n"
        "0;JMP\n",
        label, label);
}

void WriteLabel(FILE* openedFile, char* label)
{

    fprintf(openedFile, "(%s)\n", label);
}

void CallFunction(FILE* openedFile, char* functionName, int nArgs)
{
    static int i = 0; //the number of times a function is being called, help with recursiveness

    fprintf(openedFile,
        "//Call function %s\n"
        "@%s$ret.%d\n // push @returnAddress\n"
        "D = A\n"
        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n"
        "@LCL \n// Push LCL\n"
        "D = M\n"
        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n"

        "@ARG \n// Push ARG\n"
        "D = M\n"
        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n"

        "@THIS \n// Push THIS\n"
        "D = M\n"
        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n"

        "@THAT \n// Push THAT\n"
        "D = M\n"
        "@SP \n"
        "M = M + 1\n"
        "A = M - 1\n"
        "M = D\n"

        "\n// ARG = SP - 5 - nArgs\n"
        "@5\n"
        "D = A\n"
        "@SP\n"
        "D = M - D\n"
        "@%d\n"
        "D = D - A \n"

        "@ARG\n"
        "M = D\n"

        "//LCL = SP\n"
        "@SP\n"
        "D = M\n"
        "@LCL\n"
        "M = D\n"

        "//------calling the function label\n"
        "@%s \n"
        "0;JMP\n"

        "(%s$ret.%d)\n",
        functionName, functionName,
        i, nArgs, functionName, functionName, i

    );
    ++i;
}

void SetInfiniteLoop(FILE* openedFile)
{
    fprintf(openedFile, "(END)\n"
                        "@END\n"
                        "0;JMP\n");
}
void GenerateFunctionLable(FILE* openedFile, char* functionName, int nVars)
{
    fprintf(openedFile,
        "//Generate Function Label %s\n"
        "(%s)\n",
        functionName,
        functionName);

    for (int i = 0; i < nVars; ++i)
    {
        PushConstant(0, openedFile);
        PopLocal(i, openedFile);
    }
    fprintf(openedFile,
        "@%d\n"
        "D = A\n"
        "@SP\n"
        "M = M + D\n",
        nVars);
}

void SysInit(FILE* openedFile)
{
    // fprintf(openedFile, "@261\n"
    //                     "D = A\n"
    //                     "@SP\n"
    //                     "M = D\n"
    //                     "@Sys.init\n"
    //                     "0;JMP\n");
    fprintf(openedFile, "@Sys.init\n"
                        "0;JMP\n");
}