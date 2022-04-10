#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int level = 1;
int score = 100;
char *nickname = "geoa";
char *pathSavedGame = "/app/resources/saved_game.txt";
char *pathSavedGameR = "/app/resources/saved_gamec.txt";

int getBoardSize()
{
    int size = 0;
    if (level == 3)
    {
        size = 4;
    }
    else if (level == 2)
    {
        return 5;
    }
    else if (level == 1)
    {
        return 6;
    }
    return size;
}

int generateBoard(int size, int board[size][size])
{
    int i;
    int j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = 2;
        }
    }

    return 0;
}
/*
int generateBoardSavedGame(int size, int numbers[36])
{
    int board[size][size];
    int i;
    int j;
    int n = 0;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = numbers[n];
            n++;
        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%i = %i - %i\n", board[i][j], i, j);
        }
    }
    return 0;
}
*/
removeLine(int del)
{
    FILE *fptr1, *fptr2;
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
}

updateSaveGameTxt()
{
    FILE *fptr12, *fptr22;
    char curr;
    int del, line_number = 0;

    fptr12 = fopen(pathSavedGameR, "r");
    fptr22 = fopen(pathSavedGame, "w");
    curr = getc(fptr12);
    if (curr != EOF)
    {
        line_number = 1;
    }
    while (1)
    {
        if (del != line_number)
            putc(curr, fptr22);
        curr = getc(fptr12);
        if (curr == '\n')
            line_number++;
        if (curr == EOF)
            break;
    }

    fclose(fptr12);
    fclose(fptr22);
}

int countPosition()
{
    int result = 1;
    int position = 0;
    int isSaved = 0;
    FILE *ptr;
    char str[400] = "";

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
                    printf("%s \n ", info);
                    isSaved = 1;
                    position = result;
                    printf("posi: %i\n", position);
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

int saveGame(int size, int board[size][size])
{
    char line[400] = "\n";
    char str[10];
    strcat(line, nickname);
    strcat(line, ",");
    sprintf(str, "%d", level);
    strcat(line, str);
    strcat(line, ",");
    sprintf(str, "%d", score);
    strcat(line, str);

    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            sprintf(str, "%d", board[i][j]);
            strcat(line, ",");
            strcat(line, str);
        }
    }
    strcat(line, ";");

    int position = countPosition();
    printf("a %i\n", position);
    if (position > 0)
    {
        printf("b %i\n", position);
        removeLine(position);
    }

    saveGameTxt(line);
}

int saveGameTxt(char data[400])
{
    FILE *fPtr;
    fPtr = fopen(pathSavedGame, "a+");

    if (fPtr == NULL)
    {
        printf("\nUnable to open '%s' file.\n", "test.txt");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }

    fputs(data, fPtr);
    fclose(fPtr);
    return 1;
}

int getSavedGame(int numbers[36])
{
    int result = 0;
    FILE *ptr;
    char str[500] = "";

    ptr = fopen(pathSavedGame, "a+");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }
    while (fgets(str, 500, ptr) != NULL)
    {
        char *info = strtok(str, ",");
        int i = 0;
        while (info != NULL)
        {
            if (i == 0)
            {
                if (strcmp(nickname, info))
                {
                    break;
                }
            }
            else if (i == 1)
            {
                result = 1;
                level = atoi(info);
            }
            else if (i == 2)
            {
                score = atoi(info);
            }
            else
            {
                numbers[i - 2] = atoi(info);
            }
            info = strtok(NULL, ",");
            i++;
        }
    }
    fclose(ptr);

    return result;
}

int main(int argc, char const *argv[])
{
    /*
    int size = 4;
    int score = 0;
    char matriz[100] = "4 0 0 0 4 0 0 0 4 0 0 0 4 0 0 0";
    char *values = strtok(matriz, " ");

    int mv[size * size];

    int actual = 0;
    while (values != NULL)
    {
        mv[actual] = atol(values);
        actual++;
        values = strtok(NULL, " ");
    }

    int board[size][size];
    int now = 0;
    int i;
    int j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = mv[now];
            now++;
        }
    }
    printf("----2-0-4-8----------\n");
    printf("score: %d \n", score);
    printf("%i, %i, %i, %i \n", board[0][0], board[0][1], board[0][2], board[0][3]);
    printf("%i, %i, %i, %i \n", board[1][0], board[1][1], board[1][2], board[1][3]);
    printf("%i, %i, %i, %i \n", board[2][0], board[2][1], board[2][2], board[2][3]);
    printf("%i, %i, %i, %i \n", board[3][0], board[3][1], board[3][2], board[3][3]);
    printf("--------------------\n");
    printf("exit(0) \n");
    */

    int boardSize = getBoardSize();
    int board[boardSize][boardSize];

    generateBoard(boardSize, board);

    saveGame(boardSize, board);

    /*
     int numbers[36];
     int r = getSavedGame(numbers);

     if (r == 1)
     {
         int i;
         for (i = 0; i < 36; i++)
         {
             printf("N: %i V: %i \n", i, numbers[i]);
         }

         printf("Level: %i \n", level);
         printf("Score: %i \n", score);
     }
     else
     {
         printf("ops \n");
     }*/

    return 0;
}
