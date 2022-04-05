#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#define OP2 50

int level = 1;
int maxSquare = 64;
int score = 0;
int row, col;

int is_login = 1;

char *nickname = "GeoGeo";

char *addSpaces(char *dest, int size)
{
    int len = strlen(dest);

    char c[20] = "";
    strcat(c, dest);
    while (len < size)
    {
        strcat(c, " ");
        len = strlen(c);
    }
    dest = c;

    return dest;
}

title()
{
    clear();
    noecho();
    attron(COLOR_PAIR(1));

    mvprintw(row, col, "             |>=============================================================================================<|\n");
    mvprintw(row + 1, col, "             |>                                                                                             <|\n");
    mvprintw(row + 2, col, "             |>              ********         ***********         *        *           **********           <|\n");
    mvprintw(row + 3, col, "             |>                     *         *         *         *        *           *        *           <|\n");
    mvprintw(row + 4, col, "             |>                     *         *         *         *        *           *        *           <|\n");
    mvprintw(row + 5, col, "             |>              ********         *         *         **********           **********           <|\n");
    mvprintw(row + 6, col, "             |>              *                *         *                  *           *        *           <|\n");
    mvprintw(row + 7, col, "             |>              *                *         *                  *           *        *           <|\n");
    mvprintw(row + 8, col, "             |>              ********         ***********                  *           **********           <|\n");
    mvprintw(row + 9, col, "             |>                                                                                             <|\n");
    if (is_login == 0)
    {
        mvprintw(row + 10, col, "             |>                                                                                             <|\n");
    }
    else
    {
        mvprintw(row + 10, col, "             |>                                                                      %s   <|\n", addSpaces(nickname, 20));
    }
}

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

moveLineRight(int size, int board[size], int init, int actualP)
{

    int i;
    for (i = actualP; i > 0; i--)
    {
        if (board[i] != 0)
        {
            if (board[i] == board[i - 1] && init != 0)
            {
                board[i] += board[i - 1];
                board[i - 1] = 0;

                if (i == size - 1 || i + 1 != size - 1)
                {
                    moveLineRight(size, board, 0, size - 1);
                }
                else
                {
                    moveLineRight(size, board, i - 1, i - 2);
                }
            }
            else if (board[i - 1] == 0 && init != 0 && i == 1)
            {
                moveLineRight(size, board, 0, size - 1);
            }
        }
        else if (board[i - 1] != 0 && board[i] == 0)
        {
            board[i] = board[i - 1];
            board[i - 1] = 0;
            if (init == 0)
            {
                moveLineRight(size, board, 0, size - 1);
            }
            else
            {
                moveLineRight(size, board, init, init);
            }
        }
    }
}

moveRight(int size, int board[size][size])
{
    int i;
    for (i = 0; i < size; i++)
    {
        moveLineRight(size, board[i], size - 1, size - 1);
    }
}

moveLineLeft(int size, int board[size], int init, int actualP)
{
    int i;
    for (i = actualP != 0 ? 0 : actualP; i < size - 1; i++)
    {
        if (board[i] != 0)
        {
            if (board[i] == board[i + 1] && init != 0)
            {
                board[i] += board[i + 1];
                board[i + 1] = 0;

                if (i == size - 1 || i + 1 != size - 1)
                {
                    moveLineLeft(size, board, 0, 0);
                }
                else
                {
                    moveLineLeft(size, board, i + 1, i + 2);
                }
            }
            else if (board[i + 1] == 0 && init != 0 && i == size - 1)
            {
                moveLineLeft(size, board, 0, 0);
            }
        }
        else if (board[i + 1] != 0 && board[i] == 0)
        {
            board[i] = board[i + 1];
            board[i + 1] = 0;
            if (init == 0)
            {
                moveLineLeft(size, board, 0, 0);
            }
            else
            {
                moveLineLeft(size, board, init, init);
            }
        }
    }
}

moveLeft(int size, int board[size][size])
{
    int i;
    for (i = 0; i < size; i++)
    {
        moveLineLeft(size, board[i], 1, 0);
    }
}

moveLineDown(int size, int board[size][size], int column, int init, int actualP)
{

    int i;
    for (i = actualP; i > 0; i--)
    {
        if (board[i][column] != 0)
        {
            if (board[i][column] == board[i - 1][column] && init != 0)
            {
                board[i][column] += board[i - 1][column];
                board[i - 1][column] = 0;

                if (i == size - 1 || i + 1 != size - 1)
                {
                    moveLineDown(size, board, column, 0, size - 1);
                }
                else
                {
                    moveLineDown(size, board, column, i - 1, i - 2);
                }
            }
            else if (board[i - 1][column] == 0 && init != 0 && i == 1)
            {
                moveLineDown(size, board, column, 0, size - 1);
            }
        }
        else if (board[i - 1][column] != 0 && board[i][column] == 0)
        {
            board[i][column] = board[i - 1][column];
            board[i - 1][column] = 0;
            if (init == 0)
            {
                moveLineDown(size, board, column, 0, size - 1);
            }
            else
            {
                moveLineDown(size, board, column, init, init);
            }
        }
    }
}

moveDown(int size, int board[size][size])
{
    int i;
    for (i = 0; i < size; i++)
    {
        moveLineDown(size, board, i, size - 1, size - 1);
    }
}

moveLineUp(int size, int board[size][size], int column, int init, int actualP)
{
    int i;
    for (i = actualP != 0 ? 0 : actualP; i < size - 1; i++)
    {
        if (board[i][column] != 0)
        {
            if (board[i][column] == board[i + 1][column] && init != 0)
            {
                board[i][column] += board[i + 1][column];
                board[i + 1][column] = 0;

                if (i == size - 1 || i + 1 != size - 1)
                {
                    moveLineUp(size, board, column, 0, 0);
                }
                else
                {
                    moveLineUp(size, board, column, i + 1, i + 2);
                }
            }
            else if (board[i + 1] == 0 && init != 0 && i == size - 1)
            {
                moveLineUp(size, board, column, 0, 0);
            }
        }
        else if (board[i + 1][column] != 0 && board[i][column] == 0)
        {
            board[i][column] = board[i + 1][column];
            board[i + 1][column] = 0;
            if (init == 0)
            {
                moveLineUp(size, board, column, 0, 0);
            }
            else
            {
                moveLineUp(size, board, column, init, init);
            }
        }
    }
}

moveUp(int size, int board[size][size])
{
    int i;
    for (i = 0; i < size; i++)
    {
        moveLineUp(size, board, i, 1, 0);
    }
}

int moveGame(int size, int board[size][size], int direction, int boardBefore[size][size], int back)
{
    switch (direction)
    {
    case KEY_UP:
        moveUp(size, board);
        break;
    case KEY_DOWN:
        moveDown(size, board);
        break;
    case KEY_LEFT:
        moveLeft(size, board);
        break;
    case KEY_RIGHT:
        moveRight(size, board);
        break;
    default:
        break;
    }
    if (checkValidMove(size, board, boardBefore) == 1)
    {
        return checkStatus(size, board);
    }
    else
    {
        back = back == 1 ? 0 : 1;
        return 0;
    }
}

int checkValidMove(int size, int b1[size][size], int b2[size][size])
{
    int i, j;
    for (i = 0; i < size; i = i + 1)
        for (j = 0; j < size; j = j + 1)
            if (b2[i][j] != b1[i][j])
            {
                return 1;
            }
    return 0;
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
        return checkLose(size, board);
    }
    return 0;
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
    return 2;
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

char *formatNumber(int num)
{
    char str[10];
    sprintf(str, "%d", num);
    int len = strlen(str);
    char c[20] = "";

    while (len < 4)
    {
        strcat(c, " ");
        len++;
    }
    strcat(c, str);

    return strdup(c);
}

matrizCopy(int size, int b1[size][size], int b2[size][size])
{
    int i, j;
    for (i = 0; i < size; i = i + 1)
        for (j = 0; j < size; j = j + 1)
            b2[i][j] = b1[i][j];
}

screenLevel3(int size, int board[size][size])
{

    mvprintw(row + 12, col, "             |>                                                                                             <|\n");
    mvprintw(row + 13, col, "             |>                                                                  _________________________  <|\n");
    mvprintw(row + 14, col, "             |>      |%s|%s|%s|%s|                                      | NOVO JOGO            (1)| <|\n",
             formatNumber(board[0][0]), formatNumber(board[0][1]), formatNumber(board[0][2]), formatNumber(board[0][3]));
    mvprintw(row + 15, col, "             |>      |%s|%s|%s|%s|                                      | VOLTAR JOGADA        (2)| <|\n",
             formatNumber(board[1][0]), formatNumber(board[1][1]), formatNumber(board[1][2]), formatNumber(board[1][3]));
    mvprintw(row + 16, col, "             |>      |%s|%s|%s|%s|                                      | SALVAR JOGO          (3)| <|\n",
             formatNumber(board[2][0]), formatNumber(board[2][1]), formatNumber(board[2][2]), formatNumber(board[2][3]));
    mvprintw(row + 17, col, "             |>      |%s|%s|%s|%s|                                      | MENU                 (4)| <|\n",
             formatNumber(board[3][0]), formatNumber(board[3][1]), formatNumber(board[3][2]), formatNumber(board[3][3]));
    mvprintw(row + 18, col, "             |>                                                                 | SAIR                 (5)| <|\n");
    mvprintw(row + 19, col, "             |>                                                                 |_________________________| <|\n");
    mvprintw(row + 20, col, "             |>                                                                                             <|\n");
    mvprintw(row + 21, col, "             |>                                                                                             <|\n");
    mvprintw(row + 22, col, "             |>=============================================================================================<|\n");
}

screenLevel2(int size, int board[size][size])
{
    mvprintw(row + 12, col, "             |>                                                                                             <|\n");
    mvprintw(row + 13, col, "             |>                                                                  _________________________  <|\n");
    mvprintw(row + 14, col, "             |>      |%s|%s|%s|%s|%s|                                 | NOVO JOGO            (1)| <|\n",
             formatNumber(board[0][0]), formatNumber(board[0][1]), formatNumber(board[0][2]), formatNumber(board[0][3]), formatNumber(board[0][4]));
    mvprintw(row + 15, col, "             |>      |%s|%s|%s|%s|%s|                                 | VOLTAR JOGADA        (2)| <|\n",
             formatNumber(board[1][0]), formatNumber(board[1][1]), formatNumber(board[1][2]), formatNumber(board[1][3]), formatNumber(board[1][4]));
    mvprintw(row + 16, col, "             |>      |%s|%s|%s|%s|%s|                                 | SALVAR JOGO          (3)| <|\n",
             formatNumber(board[2][0]), formatNumber(board[2][1]), formatNumber(board[2][2]), formatNumber(board[2][3]), formatNumber(board[2][4]));
    mvprintw(row + 17, col, "             |>      |%s|%s|%s|%s|%s|                                 | MENU                 (4)| <|\n",
             formatNumber(board[3][0]), formatNumber(board[3][1]), formatNumber(board[3][2]), formatNumber(board[3][3]), formatNumber(board[3][4]));
    mvprintw(row + 18, col, "             |>      |%s|%s|%s|%s|%s|                                 | SAIR                 (5)| <|\n",
             formatNumber(board[4][0]), formatNumber(board[4][1]), formatNumber(board[4][2]), formatNumber(board[4][3]), formatNumber(board[4][4]));
    mvprintw(row + 19, col, "             |>                                                                 |_________________________| <|\n");
    mvprintw(row + 20, col, "             |>                                                                                             <|\n");
    mvprintw(row + 21, col, "             |>                                                                                             <|\n");
    mvprintw(row + 22, col, "             |>=============================================================================================<|\n");
}

screenLevel1(int size, int board[size][size])
{
    mvprintw(row + 12, col, "             |>                                                                                             <|\n");
    mvprintw(row + 13, col, "             |>                                                                  _________________________  <|\n");
    mvprintw(row + 14, col, "             |>      |%s|%s|%s|%s|%s|%s|                            | NOVO JOGO            (1)| <|\n",
             formatNumber(board[0][0]), formatNumber(board[0][1]), formatNumber(board[0][2]), formatNumber(board[0][3]), formatNumber(board[0][4]), formatNumber(board[0][5]));
    mvprintw(row + 15, col, "             |>      |%s|%s|%s|%s|%s|%s|                            | VOLTAR JOGADA        (2)| <|\n",
             formatNumber(board[1][0]), formatNumber(board[1][1]), formatNumber(board[1][2]), formatNumber(board[1][3]), formatNumber(board[1][4]), formatNumber(board[1][5]));
    mvprintw(row + 16, col, "             |>      |%s|%s|%s|%s|%s|%s|                            | SALVAR JOGO          (3)| <|\n",
             formatNumber(board[2][0]), formatNumber(board[2][1]), formatNumber(board[2][2]), formatNumber(board[2][3]), formatNumber(board[2][4]), formatNumber(board[2][5]));
    mvprintw(row + 17, col, "             |>      |%s|%s|%s|%s|%s|%s|                            | MENU                 (4)| <|\n",
             formatNumber(board[3][0]), formatNumber(board[3][1]), formatNumber(board[3][2]), formatNumber(board[3][3]), formatNumber(board[3][4]), formatNumber(board[3][5]));
    mvprintw(row + 18, col, "             |>      |%s|%s|%s|%s|%s|%s|                            | SAIR                 (5)| <|\n",
             formatNumber(board[4][0]), formatNumber(board[4][1]), formatNumber(board[4][2]), formatNumber(board[4][3]), formatNumber(board[4][4]), formatNumber(board[4][5]));
    mvprintw(row + 19, col, "             |>      |%s|%s|%s|%s|%s|%s|                            |_________________________| <|\n",
             formatNumber(board[5][0]), formatNumber(board[5][1]), formatNumber(board[5][2]), formatNumber(board[5][3]), formatNumber(board[5][4]), formatNumber(board[5][5]));
    mvprintw(row + 20, col, "             |>                                                                                             <|\n");
    mvprintw(row + 21, col, "             |>                                                                                             <|\n");
    mvprintw(row + 22, col, "             |>=============================================================================================<|\n");
}

showGame(int size, int board[size][size])
{
    clear();
    title();
    mvprintw(row + 11, col, "             |>      | LEVEL: %d | SCORE: %s |                                                             <|\n",
             level, formatNumber(score));
    switch (level)
    {
    case 1:
        screenLevel1(size, board);
        break;
    case 2:
        screenLevel2(size, board);
        break;
    case 3:
        screenLevel3(size, board);
        break;

    default:
        break;
    }
    refresh();
}

int main(void)
{
    initscr();
    start_color();
    // cbreak();			   Buffer de linha desativado, passe tudo para mim
    keypad(stdscr, TRUE);
    noecho();
    getmaxyx(stdscr, row, col);
    col = col / 8;
    row = row / 8;

    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    // raw();
    int boardSize = getBoardSize();
    int board[boardSize][boardSize];
    int boardCopy0[boardSize][boardSize];
    int boardCopy1[boardSize][boardSize];
    int position = 0;

    generateBoard(boardSize, board);
    matrizCopy(boardSize, board, boardCopy0);
    matrizCopy(boardSize, board, boardCopy1);

    showGame(boardSize, board);

    int end = 1;
    int keep = 0;
    int back = 0;
    int is_back = 1;

    while (position != 48 && keep == 0)
    {

        if (back == 0)
        {
            matrizCopy(boardSize, board, boardCopy0);
            back = 1;
        }
        else if (back == 1)
        {
            matrizCopy(boardSize, board, boardCopy1);
            back = 0;
        }

        position = getch();
        if (position == OP2)
        {
            if (is_back == 1)
            {
                matrizCopy(boardSize, back == 0 ? boardCopy0 : boardCopy1, board);
                score -= 2;
                is_back = 0;
            }
        }
        else
        {
            keep = moveGame(boardSize, board, position, back == 1 ? boardCopy0 : boardCopy1, back);
            is_back = 1;
        }
        showGame(boardSize, board);
    }
    if (keep == 1)
    {
        clear();
        printw("Boa \n");
    }
    else if (keep == 2)
    {
        printw("Perdeu \n");
    }

    getch();

    endwin();

    return 0;
}