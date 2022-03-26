#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int randomPosition(int maxNumber)
{
    int MAX = 10;
    srand(time(NULL));
    return rand() % maxNumber;
}

int main()
{

    printf("%d\n", randomZ(10));

    // exit(EXIT_SUCCESS);
}
