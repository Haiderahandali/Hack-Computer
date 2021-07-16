#include "parse.h"

bool gHasMoreLines;

file_pointer_t InitParse(char const* pathToFile)
{

    gHasMoreLines = true;
    return fopen(pathToFile, "r");
}

char advance(file_pointer_t openedFile)
{
    char c = fgetc(openedFile);
    switch (c)
    {

        case EOF:
        {
            gHasMoreLines = false;
            c             = false;
            break;
        }

        case '\n':
        case ' ':
        {
            c = advance(openedFile);
            break;
        }

        //handing comments
        case '/':
        {
            if (fgetc(openedFile) == '/')
            {
                while (true)
                {
                    char ch = fgetc(openedFile);
                    if ((ch == '\n') || (ch == EOF))
                    {
                        c = advance(openedFile);
                        break;
                    }
                }
            }
            else
            {
                printf("Error expected a comment but couldn't found the second slash\n");
            }
            break;
        }

        default:
        {
            break;
        }
    }
    return c;
}

bool CurrentOpenedFileHasMoreLines()
{
    return gHasMoreLines == true;
}
