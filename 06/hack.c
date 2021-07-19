#include "parse.h"
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("the program should be supplied with only one Command line argument, the path to the file to prase\n");
        return 1;
    }

    file_pointer_t currentOpenFile = InitParse(argv[1]); // the path to the file should be the first CL argument of the program
    while (CurrentOpenedFileHasMoreLines())
    {
        char const* currentLine = GetLineFromStream(currentOpenFile);
        PushInstruction(currentLine);
    }

    ParseInstructions();
    PrintAllInstructionInfo();

    // writing to a file
    ulong_t outputFileSize = strlen(argv[1]) + 3;

    char outputFileName[outputFileSize];
    strcpy(outputFileName, argv[1]);

    char* dotSign = strchr(outputFileName, '.');
    if (dotSign)
    {
        dotSign[1] = 'h';
        dotSign[2] = 'a';
        dotSign[3] = 'c';
        dotSign[4] = 'k';
        dotSign[5] = '\0';
    }
    printf("writing to file: %s \n", outputFileName);

    WriteBinaryInstructions(outputFileName);
    close(currentOpenFile);
}
