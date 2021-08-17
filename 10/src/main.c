#include "compile.h"

static char* readFile(char const* path)
{

    FILE* file = fopen(path, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(CANNOT_OPEN_FILE);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = (size_t)ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(sizeof(char) * (fileSize + 1));
    if (buffer == NULL)
    {
        fprintf(stderr, "Could not allocate memory\n");
        exit(CANNOT_ALLOCATE_MEMORY);
    }
    size_t bytesRead  = fread(buffer, sizeof(char), fileSize, file);
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

static void runFile(char const* path)
{
    char* source = readFile(path);
    printf("%s\n", source);
    compile(source);

    free(source);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: compiler path_to_source_code\nsupply one command line argument which is the source code file path\n");
        return UNCORRECT_NUMBER_OF_ARGUMENTS;
    }

    else
    {
        runFile(argv[1]);
    }
}
