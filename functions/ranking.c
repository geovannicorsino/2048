#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pathRanking = "/app/resources/";

seeRanking()
{
    int level = 1;

    switch (level)
    {
    case 1:
        readRanking("ranking_level1.txt");
    default:
        break;
    }
}

readRanking(char nameFile[])
{  
    FILE *ptr;
    char str[50];
    char path[60] = "";
    strcat(path, pathRanking);
    strcat(path, nameFile);
    ptr = fopen(pathRanking, "a+");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }
    while (fgets(str, 50, ptr) != NULL)
    {
        char *users = strtok(str, ";");

        while (users != NULL)
        {
            char *user = strtok(str, ":");

            while (user != NULL)
            {

                user = strtok(NULL, " ");
            }
            users = strtok(NULL, " ");
        }
    }
    fclose(ptr);
    return 0;
}

int main()
{
    return 0;
}
