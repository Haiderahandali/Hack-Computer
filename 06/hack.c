#include "parse.h"
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("the program should be supplied with only one Command line argument, the path to the file to prase\n");
        return 1;
    }

    file_pointer_t currentOpenFile = InitParse(argv[1]); // the path to the file should be the only CL argument of the program
    while (CurrentOpenedFileHasMoreLines())
    {
        char const* currentLine = getLineFromStream(currentOpenFile);
        PushInstruction(currentLine);
    }

    ParseInstructions();

    close(currentOpenFile);
}
