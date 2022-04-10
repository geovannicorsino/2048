#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

int ESC = 27;
int ENTER = 10;
int DEL = 263;
int DEL2 = 330;
int EXIT = 48;

int row, col = 0;

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

    return strdup(dest);
}

char *readInput(int field)
{
    int num;
    char ch;
    char name[20] = "";
    while (num != ESC && num != ENTER)
    {
        if (field == 1)
        {
            mvprintw(row + 15, col, "|>                                     NOME: %s                              <|\n", addSpaces(name, 20));
        }
        else
        {
            mvprintw(row + 17, col, "|>                                     SENHA: %s                             <|\n", addSpaces(name, 20));
        }
        refresh();
        num = getch();
        printw("%i", num);
        getch();
        if ((num >= 97 && num <= 122) || (num >= 65 && num <= 90))
        {
            ch = num;
            strncat(name, &ch, 1);
        }
        else if (num == DEL || num == DEL2 || num == EXIT)
        {
            name[strlen(name) - 1] = '\0';
        }
    }
    num = 0;
    return strdup(name);
}

int main(void)
{

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    getmaxyx(stdscr, row, col);
    col = col / 4;
    row = row / 6;

    curs_set(0);

    clear();
    mvprintw(row + 11, col, "|>                          *******************************************                        <|\n");
    mvprintw(row + 12, col, "|>                          * DIGITE SEUS DADOS DE ACESSO PARA ENTRAR *                        <|\n");
    mvprintw(row + 13, col, "|>                          *******************************************                        <|\n");
    mvprintw(row + 14, col, "|>                                                                                             <|\n");
    mvprintw(row + 15, col, "|>                                     NOME:                                                   <|\n");
    mvprintw(row + 16, col, "|>                                                                                             <|\n");
    mvprintw(row + 17, col, "|>                                     SENHA:                                                  <|\n");
    mvprintw(row + 18, col, "|>                                                                                             <|\n");
    mvprintw(row + 19, col, "|>                                                                                             <|\n");
    mvprintw(row + 20, col, "|>                                                                                             <|\n");
    mvprintw(row + 21, col, "|>                                                                                             <|\n");
    mvprintw(row + 22, col, "|>=============================================================================================<|\n");
    readInput(2);
    readInput(1);
    refresh();
    endwin();

    return 0;
}
