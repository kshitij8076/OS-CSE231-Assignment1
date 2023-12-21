#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
int filecheck(const char *filename)
{
    if (!access(filename, F_OK))
    {
        return 1;
    }
    else
    {
        perror("Error file not found\n");
        return 0;
    }
}

int cnt_word(char *filename)
{
    int wordCount = 0;
    int flag = 0;
    FILE *file = fopen(filename, "r");
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if ((ch == ' ' || ch == '\n' || ch == '\t') && flag == 0)
        {

            wordCount++;
            flag = 1;
        }
        else if ((ch == ' ' || ch == '\n' || ch == '\t') && flag == 1)
        {
            continue;
        }
        else
        {
            flag = 0;
        }
    }

    fclose(file);
    return wordCount;
}

int main(int *argc, char *argv[])
{
    int wordCount = 0;
    // printf("here\n");
    if (strcmp(argv[1], "-n") == 0) // for -n
    {
        if (filecheck(argv[2]))
        {
            char ch;
            FILE *file = fopen(argv[2], "r");
            int flag = 0;
            while ((ch = fgetc(file)) != EOF)
            {
                if ((ch == ' ' || ch == '\t') && flag == 0)
                {
                    wordCount++;
                    flag = 1;
                }
                else if ((ch == ' ' || ch == '\t') && flag == 1)
                {
                    continue;
                }
                else
                {
                    flag = 0;
                }
            }

            fclose(file);
            printf("Total number of words: %d\n", wordCount);
        }
    }

    else if (strcmp(argv[1], "-d") == 0) // for -d option
    {
        if (filecheck(argv[2]) && filecheck(argv[3]))
        {
            int words1 = cnt_word(argv[2]);
            int words2 = cnt_word(argv[3]);
            printf("Difference between total words between two file is: %d\n", abs(words1 - words2));
        }
    }
    else if (strcmp(argv[1], "0") == 0) // when no option
    {
        if (filecheck(argv[2]))
        {
            // printf("here now\n");
            int words = cnt_word(argv[2]);
            printf("Total number of words: %d\n", words);
        }
    }
    exit(1);
}