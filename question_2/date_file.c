#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void Time(const struct tm *timeStruct)
{
    char formattedTime[50];
    strftime(formattedTime, sizeof(formattedTime), "%a, %d %b %Y %H:%M:%S +0000", timeStruct);
    printf("Last modified time (RFC 5322 format): %s\n", formattedTime);
}

void yestime(const struct tm *timeStruct)
{
    char formattedTime[100];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", timeStruct);
    printf("Last modified time: %s\n", formattedTime);
}

void getFileModificationTime(const char *path, time_t *mt)
{
    struct stat attr;
    if (stat(path, &attr) == 0)
    {
        *mt = attr.st_mtime;
    }
    else
    {
        perror("stat error");
    }
}

int isYesterday(const time_t *timestamp)
{
    time_t now = time(NULL);
    struct tm *nowTime = localtime(&now);

    struct tm ystime = *nowTime;
    struct tm *tmdetails = localtime(timestamp);
    ystime.tm_mday--;

    return (ystime.tm_mday == tmdetails->tm_mday &&
            ystime.tm_mon == tmdetails->tm_mon &&
            ystime.tm_year == tmdetails->tm_year);
}

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

void IST_TIME(char *path)
{
    struct stat attr;
    stat(path, &attr);
    printf("Last modified time: %s", ctime(&attr.st_mtime));
}

void getFileCreationTime(const char *path)
{
    struct stat attr;
    if (stat(path, &attr) == 0)
    {
        struct tm *timeInfo = gmtime(&attr.st_mtime);
        if (timeInfo != NULL)
        {
            Time(timeInfo);
        }
        else
        {
            perror("gmtime error");
        }
    }
    else
    {
        perror("stat error");
    }
}

int main(char *argc, char *argv[])
{
    char Path[100];
    getcwd(Path, 100);
    strcat(Path, "/");

    if (strcmp(argv[1], "-R") == 0)
    {
        if (filecheck(argv[2]))
        {
            strcat(Path, argv[2]);
            getFileCreationTime(Path);
        }
        exit(1);
    }

    else if (strcmp(argv[1], "-d") == 0)
    {
        if (strcmp(argv[2], "yesterday") == 0 && filecheck(argv[3]))
        {
            const char *file = argv[3];
            time_t mt;

            getFileModificationTime(file, &mt);

            if (isYesterday(&mt))
            {
                struct tm *mt_info = localtime(&mt);
                yestime(mt_info);
                printf("The file was last modified yesterday.\n");
            }
            else
            {
                printf("The file was not last modified yesterday.\n");
            }
        }

        else if (strcmp(argv[2], "today") == 0 && filecheck(argv[3]))
        {

            strcat(Path, argv[3]);
            IST_TIME(Path);
        }
        exit(1);
    }
    else if (strcmp(argv[1], "0") == 0)
    {
        if (filecheck(argv[2]))
        {
            strcat(Path, argv[2]);
            IST_TIME(Path);
        }
        exit(1);
    }
    return 0;
}
