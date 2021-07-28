#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process_vm_code.h"

#define MAX_LINES 30000
#define MAX_WORDS_PER_LINE 20
#define MAX_WORD_SIZE 256

static lines_t* gLineManager;
static int gCurrentLine;

lines_t* GetLines()
{
    return gLineManager;
}

void InitVmProcess()
{
    gLineManager        = malloc(sizeof(lines_t));
    gLineManager->lines = malloc(sizeof(words_t) * MAX_LINES);
}

void SplitWords(char* line)
{
    int currentWord = 0;

    gLineManager->lines[gCurrentLine].words = malloc(sizeof(char*) * MAX_WORDS_PER_LINE);

    //skip white spaces
    int i = 0;
    while (line[i] == ' ')
    {
        ++i;
    }

    char c; //hold the current character
    char buffer[MAX_WORD_SIZE]; //buffer for each word
    int j = 0;
    while ((c = line[i++]) != '\0')
    {
        switch (c)
        {
            case ' ':
            {
                if (j == 0) //just in case someone pushed extra spaces between words
                {
                    break;
                }

                buffer[j] = '\0';
                j         = 0;

                gLineManager->lines[gCurrentLine].words[currentWord++] = strdup(buffer);
                break;
            }
            default:
            {
                buffer[j++] = c;
                break;
            }
        }
    }

    if (j > 0) //if we hit a word that doesn't have a space after it
    {
        buffer[j]                                              = '\0';
        gLineManager->lines[gCurrentLine].words[currentWord++] = strdup(buffer);
    }
    gLineManager->lines[gCurrentLine].wordCount = currentWord;

    if (currentWord != 0)
    {
        ++gCurrentLine;
    }
    gLineManager->lineCount = gCurrentLine;
}

void CloseVmProcess()
{
    for (int i = 0, lineCount = gLineManager->lineCount; i < lineCount; ++i)
    {
        for (int currentWord = 0, wordCount = gLineManager->lines[i].wordCount; currentWord < wordCount; ++currentWord)
        {
            free(gLineManager->lines[i].words[currentWord]);
        }
        free(gLineManager->lines[i].words);
    }
    free(gLineManager->lines);
    free(gLineManager);
}
void PrintSplitedLines(vm_code_t* vmInstructions)
{

    for (uint32_t i = 0, size = vmInstructions->vmLOC; i < size; ++i)
    {
        SplitWords(vmInstructions->vm_instructions[i].vmInstructionString);
    }

    FILE* logFile = fopen("SplitedWords.txt", "w+");

    for (int i = 0, lineCount = gLineManager->lineCount; i < lineCount; ++i)
    {
        fprintf(logFile, "--------------------------------------------\nline %d: |", i);
        for (int j = 0, wordCount = gLineManager->lines[i].wordCount; j < wordCount; ++j)
        {
            fprintf(logFile, "%s|", gLineManager->lines[i].words[j]);
        }
        fprintf(logFile, "\n--------------------------------------------\n");
    }

    fclose(logFile);
}
