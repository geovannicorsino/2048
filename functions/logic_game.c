#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

int level = 3;
int maxSquare = 2048;
int score = 0;

int randomPosition(int maxNumber)
{
    int MAX = 10;
    srand(time(NULL));
    return rand() % maxNumber;
}

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
            board[i][j] = 0;
        }
    }
    int numberZeros = size * size;
    appendNumber(size, board, numberZeros);
    return 0;
}

moveLineRight(int size, int board[size])
{

    int i;
    for (i = 0; i < size - 1; i++)
    {
        if (board[i] != 0)
        {
            if (board[i] == board[i + 1] || board[i + 1] == 0)
            {
                board[i + 1] = board[i + 1] + board[i];
                board[i] = 0;

                if (i != 0)
                {
                    moveLineRight(size, board);
                }
            }
        }
    }
}

moveRight(int size, int board[size][size])
{
    int i;
    for (i = 0; i < size; i++)
    {
        moveLineRight(size, board[i]);
    }
}

moveLineLeft(int size, int board[size])
{
    int i;
    for (i = size - 1; i > 0; i--)
    {

        if (board[i] != 0)
        {
            if (board[i] == board[i - 1] || board[i - 1] == 0)
            {
                board[i - 1] = board[i - 1] + board[i];
                board[i] = 0;

                if (i != 3)
                {
                    moveLineLeft(size, board);
                }
            }
        }
    }
}

moveLeft(int size, int board[size][size])
{
    int i;
    for (i = 0; i < size; i++)
    {
        moveLineLeft(size, board[i]);
    }
}

moveLineDown(int size, int board[size][size], int column)
{
    int i;
    for (i = 0; i < size - 1; i++)
    {
        if (board[i][column] != 0)
        {
            if (board[i][column] == board[i + 1][column] || board[i + 1][column] == 0)
            {
                board[i + 1][column] = board[i + 1][column] + board[i][column];
                board[i][column] = 0;

                if (i != 0)
                {
                    moveLineDown(size, board, column);
                }
            }
        }
    }
}

moveDown(int size, int board[size][size])
{
    int i;
    for (i = 0; i < 4; i++)
    {
        moveLineDown(size, board, i);
    }
}

moveLineUp(int size, int board[size][size], int column)
{
    int i;
    for (i = size - 1; i > 0; i--)
    {
        if (board[i][column] != 0)
        {
            if (board[i][column] == board[i - 1][column] || board[i - 1][column] == 0)
            {
                board[i - 1][column] = board[i - 1][column] + board[i][column];
                board[i][column] = 0;

                if (i != (size - 1))
                {
                    moveLineUp(size, board, column);
                }
            }
        }
    }
}

moveUp(int size, int board[size][size])
{
    int i;
    for (i = 0; i < size; i++)
    {
        moveLineUp(size, board, i);
    }
}

moveGame(int size, int board[size][size], int direction)
{
    int w = 8;
    int s = 2;
    int l = 4;
    int r = 6;

    if (direction == KEY_UP)
    {
        moveUp(size, board);
    }
    else if (direction == KEY_DOWN)
    {
        moveDown(size, board);
    }
    else if (direction == KEY_LEFT)
    {
        moveLeft(size, board);
    }
    else if (direction == KEY_RIGHT)
    {
        moveRight(size, board);
    }
    checkStatus(size, board);
}

int checkStatus(int size, int board[size][size])
{
    int numberZeros = 0;
    int i;
    int j;
    score++;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (board[i][j] == 0)
            {
                numberZeros++;
            }
            else if (board[i][j] == maxSquare)
            {
                // win true
                return 1;
            }
        }
    }
    if (numberZeros > 0)
    {
        appendNumber(size, board, numberZeros);
    }
    else
    {
        checkLose(size, board);
    }
}

int checkLose(int size, int board[size][size])
{
    int i;
    int j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1; j++)
        {
            if (board[i][j] == board[i][j + 1])
            {
                return 0;
            }
        }
    }
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size; j++)
        {

            if (board[i][j] == board[i + 1][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int appendNumber(int size, int board[size][size], int numberZeros)
{

    int positionNewNumber = 0;
    while (positionNewNumber == 0)
    {
        positionNewNumber = randomPosition(numberZeros);
    }

    int totalZeros = 0;
    int i;
    int j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (board[i][j] == 0)
            {
                totalZeros++;
            }
            if (totalZeros == positionNewNumber)
            {
                board[i][j] = 2;
                return 1;
            }
        }
    }
    return 0;
}

int main(void)
{
    int boardSize = getBoardSize();
    int board[boardSize][boardSize];
    int position = 0;

    generateBoard(boardSize, board);

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    printw("%i, %i, %i, %i \n", board[0][0], board[0][1], board[0][2], board[0][3]);
    printw("%i, %i, %i, %i \n", board[1][0], board[1][1], board[1][2], board[1][3]);
    printw("%i, %i, %i, %i \n", board[2][0], board[2][1], board[2][2], board[2][3]);
    printw("%i, %i, %i, %i \n", board[3][0], board[3][1], board[3][2], board[3][3]);

    int end = 1;

    while (end != 48)
    {
        position = getch();
        moveGame(boardSize, board, position);
        clear();
        printw("----2-0-4-8----------\n");
        printw("score: %d \n", score);
        printw("%i, %i, %i, %i \n", board[0][0], board[0][1], board[0][2], board[0][3]);
        printw("%i, %i, %i, %i \n", board[1][0], board[1][1], board[1][2], board[1][3]);
        printw("%i, %i, %i, %i \n", board[2][0], board[2][1], board[2][2], board[2][3]);
        printw("%i, %i, %i, %i \n", board[3][0], board[3][1], board[3][2], board[3][3]);
        printw("--------------------\n");
        printw("exit(0) \n");
        refresh();
        end = position;
        printw("%d\n", end);
    }
    endwin();

    return 0;
}