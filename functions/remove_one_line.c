#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *nickname = "geoba";

char *pathSavedGame = "/app/resources/saved_game.txt";
char *pathSavedGameR = "/app/resources/saved_gamec.txt";

removeLine(int del)
{
    int result = 0;
    FILE *fptr1, *fptr2;
    char file1[] = "file1.txt";
    char file2[] = "file2.txt";
    char curr;
    int line_number = 0;

    fptr1 = fopen(pathSavedGame, "r");
    fptr2 = fopen(pathSavedGameR, "w");
    curr = getc(fptr1);
    if (curr != EOF)
    {
        line_number = 1;
    }
    while (1)
    {
        if (del != line_number)
            putc(curr, fptr2);
        curr = getc(fptr1);
        if (curr == '\n')
            line_number++;
        if (curr == EOF)
            break;
    }

    fclose(fptr1);
    fclose(fptr2);

    updateSaveGameTxt();

    return result;
}

updateSaveGameTxt()
{
    FILE *fptr1, *fptr2;
    char curr;
    int del, line_number = 0;

    fptr1 = fopen(pathSavedGameR, "r");
    fptr2 = fopen(pathSavedGame, "w");
    curr = getc(fptr1);
    if (curr != EOF)
    {
        line_number = 1;
    }
    while (1)
    {
        if (del != line_number)
            putc(curr, fptr2);
        curr = getc(fptr1);
        if (curr == '\n')
            line_number++;
        if (curr == EOF)
            break;
    }

    fclose(fptr1);
    fclose(fptr2);
}

int countPosition()
{
    int result, position = 1;
    int isSaved = 0;
    FILE *ptr;
    char str[400];

    ptr = fopen(pathSavedGame, "a+");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }
    while (fgets(str, 400, ptr) != NULL)
    {
        char *info = strtok(str, ",");
        int i = 0;
        while (info != NULL)
        {
            if (i == 0)
            {
                if (!strcmp(nickname, info))
                {
                    isSaved = 1;
                    position = result;
                }
                result++;
            }
            i++;
            info = strtok(NULL, ",");
        }
    }
    fclose(ptr);

    if (isSaved == 1)
    {
        return position;
    }
    return 0;
}

int main()
{
    //   removeLine();

    printf("p: %i \n", countPosition());
    removeLine(countPosition());
    return 0;
}