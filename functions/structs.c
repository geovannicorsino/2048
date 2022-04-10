#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PlayerScore
{
    char *name;
    int score;
};

setData(struct PlayerScore players[5])
{
    players[0].name = "Geo";
    players[0].score = 10;
    players[1].name = "jao";
    players[1].score = 10;
    printf("Name: %s\n", players[0].name);
    printf("Total %d\n", players[0].score);
    printf("Name: %s\n", players[1].name);
    printf("Total %d\n", players[1].score);
}

int main()
{
    struct PlayerScore players[5];

    setData(players);

    printf("Name: %s\n", players[0].name);
    printf("Total %d\n", players[0].score);
    printf("Name: %s\n", players[1].name);
    printf("Total %d\n", players[1].score);

    return 0;
}