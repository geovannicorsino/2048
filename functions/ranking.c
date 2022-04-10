#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pathRanking = "/app/resources/";
char *nickname = "ha";
int score = 0;

struct PlayerScore
{
    char *name;
    int score;
};

seeRanking(struct PlayerScore players[10])
{
    int level = 1;
    int quantityPlayers = 0;

    switch (level)
    {
    case 1:
        quantityPlayers = readRanking("ranking_level1.txt", players);
    default:
        break;
    }

    bubbleSort(players, quantityPlayers);
}

int readRanking(char nameFile[], struct PlayerScore players[10])
{
    int quantityPlayers = 0;
    FILE *ptr;
    char str[50];
    char path[100] = "";
    strcat(path, pathRanking);
    strcat(path, nameFile);
    ptr = fopen(path, "a+");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }
    while (fgets(str, 50, ptr) != NULL)
    {
        int is_nickname = 1;
        char *user = strtok(str, ":");
        char *name;

        while (user != NULL)
        {
            if (is_nickname == 1)
            {
                players[quantityPlayers].name = strdup(user);
            }
            else
            {
                players[quantityPlayers].score = atoi(user);
            }
            is_nickname = 0;
            user = strtok(NULL, " ");
        }
        quantityPlayers++;
    }
    fclose(ptr);

    return quantityPlayers;
}

bubbleSort(struct PlayerScore players[10], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (players[j].score < players[j + 1].score)
            {
                char *name = strdup(players[j].name);
                int score = players[j].score;
                players[j].name = strdup(players[j + 1].name);
                players[j].score = players[j + 1].score;
                players[j + 1].name = strdup(name);
                players[j + 1].score = score;
            }
        }
    }
}

int addNewUserToRanking()
{
    char *nameFile = "ranking_level1.txt";
    char path[100] = "";
    strcat(path, pathRanking);
    strcat(path, nameFile);
    FILE *fPtr;
    fPtr = fopen(path, "a+");

    if (fPtr == NULL)
    {
        printf("\nUnable to open '%s' file.\n", "test.txt");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }

    char str[5];
    sprintf(str, "%d", score);

    char dataToAppend[100] = "";
    strcat(dataToAppend, nickname);
    strcat(dataToAppend, ":");
    strcat(dataToAppend, str);
    strcat(dataToAppend, ";\n");

    fputs(dataToAppend, fPtr);
    fclose(fPtr);
    return 1;
}

int main()
{
    // addNewUserToRanking();
    struct PlayerScore players[10];
    seeRanking(players);
    return 0;
}
