#include "parse.h"

bool gHasMoreLines;

static char buffer[MAX_INSTRUCTION_SIZE];

file_pointer_t InitParse(char const* pathToFile)
{

    gHasMoreLines = true;
    return fopen(pathToFile, "r");
}

//This already strip out extra tokens such as whitespaces, comments
char const* getLineFromStream(file_pointer_t openedFile)
{
    int i = 0;

    bool endOfLine = false;
    while (!endOfLine)
    {
        char c = fgetc(openedFile);
        switch (c)
        {
            case ' ':
            {
                break;
            }

            case '\n':
            {
                endOfLine = true;
                break;
            }

            case EOF:
            {
                gHasMoreLines = false;
                endOfLine     = true;
                break;
            }

            case '/':
            {

                char secondSlash = fgetc(openedFile);
                if (secondSlash != '/')
                {
                    printf("invalid comment expected next slash\n");
                    endOfLine = true;
                    break;
                }
                while (true)
                {
                    char ch = fgetc(openedFile);
                    if (ch == EOF || ch == '\n')
                    {
                        endOfLine = true;
                        break;
                    }
                }
                break;
            }

            default:
            {
                buffer[i] = c;
                ++i;
                break;
            }
        }
    }
    buffer[i] = '\0';
    return buffer;
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
