#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *nickname = "Geovanni";
char *password = "123";
char *path_users = "/app/resources/users.txt";

int addNewUser()
{
    FILE *fPtr;
    fPtr = fopen(path_users, "a+");

    if (fPtr == NULL)
    {
        printf("\nUnable to open '%s' file.\n", "test.txt");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }

    char dataToAppend[100] = "";
    strcat(dataToAppend, nickname);
    strcat(dataToAppend, ":");
    strcat(dataToAppend, password);
    strcat(dataToAppend, ";\n");

    if (strlen(nickname) > 20)
    {
        return 2;
    }
    if (validSpaces(nickname) == 1 || validSpaces(password) == 1)
    {
        return 2;
    }
    if (validOnlyName(fPtr) == 1)
    {
        return 2;
    }

    fputs(dataToAppend, fPtr);
    fclose(fPtr);
    return 1;
}

int validOnlyName(FILE *ptr)
{
    char str[50];

    while (fgets(str, 50, ptr) != NULL)
    {
        char *users = strtok(str, ";");

        while (users != NULL)
        {
            char *user = strtok(str, ":");

            while (user != NULL)
            {
                if (!strcmp(nickname, user))
                {
                    return 1;
                }
                else
                {
                    break;
                }
                user = strtok(NULL, " ");
            }
            users = strtok(NULL, " ");
        }
    }
    return 0;
}

int validSpaces(char str[])
{
    int i = 0;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    addNewUser();
    return 0;
}
