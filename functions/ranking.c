#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pathRanking = "/app/resources/";

struct PlayerScore
{
    char *name;
    int score;
};

seeRanking()
{
    struct PlayerScore players[10];
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

    int i;
    for (i = 0; i < quantityPlayers; i++)
    {
        printf("Name: %s \n", players[i].name);
        printf("Score: %d \n", players[i].score);
    }
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

int main()
{
    seeRanking();
    return 0;
}
