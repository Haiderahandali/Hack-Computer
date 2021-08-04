#include "parse_vm_code.h"
#include "process_vm_code.h"
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    struct output_struct_t* output = CreateOutputStruct(argv[1]);

    char* extension = strchr(argv[1], '.'); //assuming a single dot (.) in the file name for the extension
    if (extension != NULL)
    {
        if (strcmp(extension, ".vm") == 0)
        {
            size_t size = strlen(argv[1]);

            char fileName[size + 1];
            strncpy(fileName, argv[1], extension - argv[1]);

            fileName[size - 3] = '\0';

            InitMain(argv[1]);
            PrintInstructions();
            PrintSplitedLines(GetVmInstructions());

            WriteMachineInstructions(output, GetLines(), fileName);
            CloseMain();
        }
        else
        {
            printf("error not the exepcted file extension (expected .vm)\n");
            return 2;
        }
    }
    else
    {
        DIR* folder;
        struct dirent* entry;
        struct stat filestat;

        folder = opendir(argv[1]);

        if (folder == NULL)
        {
            perror("Unable to read directory");
            return (1);
        }

        /* Read directory entries */
        while ((entry = readdir(folder)))
        {
            size_t arglen  = strlen(argv[1]);
            char* fullpath = malloc(arglen + strlen(entry->d_name) + 2);
            if (fullpath == NULL)
            {
                printf("malloc failed\n");
                return -1;
            }
            sprintf(fullpath, "%s/%s", argv[1], entry->d_name);

            if (S_ISDIR(filestat.st_mode))
            {
                printf("Dir: %s\n", fullpath);
            }
            else
            {
                printf("File: %s\n", fullpath);
                char* extension = strchr(fullpath, '.'); //assuming a single dot (.) in the file name for the extension
                if (extension != NULL)
                {
                    if (strcmp(extension, ".vm") == 0)
                    {
                        size_t size = strlen(fullpath);

                        char fileName[size + 1];
                        strncpy(fileName, fullpath, extension - fullpath);

                        fileName[size - 3] = '\0';

                        InitMain(fullpath);
                        PrintInstructions();
                        PrintSplitedLines(GetVmInstructions());

                        WriteMachineInstructions(output, GetLines(), fileName);
                        CloseMain();
                    }
                    else
                    {
                        printf("not a vm extension, returning...\n");
                    }
                }
                free(fullpath);
            }
        }

        closedir(folder);
    }
    CloseOutputStruct(&output);
    return 0;
}
