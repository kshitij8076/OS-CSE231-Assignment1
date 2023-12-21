#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
    char ch;

    char s[100];
    getcwd(s, 100);
    while (1)
    {

        char input[200]; // Assuming input won't exceed 200 characters
        char command[50];
        char option[50];
        char fileName1[10];
        char fileName2[10];

        printf("Enter command and arguments: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s %s %s %s", command, option, fileName1, fileName2);

        // printf("Command: %s\n", command);
        // printf("Option: %s\n", option[0] == '\0' ? "None" : option);
        // printf("File Name 1: %s\n", fileName1);
        // printf("File Name 2: %s\n", fileName2);
        __pid_t pid;

        if (strcmp(command, "word") == 0)
        {
            pid = fork();
            if (pid == -1)
            {
                printf("Error in making fork\n");
                exit(1);
            }
            else if (pid == 0)
            {

                if (strcmp(option, "-n") == 0)
                {
                    char *args[10] = {"./word_file", "-n", fileName1};
                    execv("./word_file", args);
                }
                else if (strcmp(option, "-d") == 0)
                {
                    char *args[10] = {"./word_file", "-d", fileName1, fileName2};
                    execv("./word_file", args);
                }
                else
                {
                    char *args[10] = {"./word_file", "0", option};
                    execv("./word_file", args);
                }
                exit(1);
            }

            else
            {
                wait(NULL);
            }
        }

        else if (strcmp(command, "dir") == 0)
        {
            pid = vfork();
            char dirname[100];

            if (pid == -1)
            {
                perror("Error in making fork\n");
                exit(1);
            }
            else if (pid == 0)
            {
                if (strcmp(option, "-r") == 0 || strcmp(option, "-v") == 0)
                {
                    int vflag = 0;
                    if (strcmp(option, "-v") == 0)
                    {
                        vflag = 1;
                    }
                    int dir_exist = mkdir(fileName1, 0777);
                    if (vflag == 1)
                        printf("Checking Directory exist or not\n");
                    if (dir_exist == -1)
                    {
                        int ret = 0;
                        char cmd[32] = {0};
                        sprintf(cmd, "rm -rf %s", fileName1);
                        ret = system(cmd);
                        if (vflag == 1)
                            printf("Deleting existing Directory\n");
                        if (vflag == 1)
                            printf("Creating new Directory\n");
                        mkdir(fileName1, 0777);
                    }
                    getcwd(dirname, 100);
                    strcat(dirname, "/");
                    strcat(dirname, option);
                    if (vflag == 1)
                        printf("Changing Current directory path with new Directory created\n");
                    exit(1);
                }
                else
                {

                    int dir_exist = mkdir(option, 0777);
                    if (dir_exist == -1)
                    {
                        perror("Error Directory already exist\n");
                        exit(1);
                    }
                    getcwd(dirname, 100);
                    strcat(dirname, "/");
                    strcat(dirname, option);
                    exit(1);
                }
            }
            else
            {
                wait(NULL);
                char cwd[100];
                chdir(dirname);
                getcwd(cwd, 100);
                printf("%s\n", cwd);
            }
        }
        else if (strcmp(command, "date") == 0)
        {

            pid = fork();
            if (pid == -1)
            {
                perror("Error in making fork\n");
                exit(1);
            }
            else if (pid == 0)
            {
                if (strcmp(option, "-R") == 0)
                {
                    char *args[10] = {"./date_file", "-R", fileName1};
                    execv("./date_file", args);
                }

                else if (strcmp(option, "-d") == 0)
                {
                    char *args[10] = {"./date_file", "-d", fileName1, fileName2};
                    execv("./date_file", args);
                }
                else
                {
                    char *args[10] = {"./date_file", "0", option};

                    execv("./date_file", args);
                }
                exit(1);
            }
            else
            {

                wait(NULL);
            }
        }
        else if (strcmp(command, "cwd") == 0)
        {
            char curr_dir[100];
            getcwd(curr_dir, 100);
            printf("%s\n", curr_dir);
        }

        else if (strcmp(command, "exit") == 0)
        {
            exit(1);
        }
        else
        {
            perror("Wrong command \n");
        }
    }
    return 0;
}
