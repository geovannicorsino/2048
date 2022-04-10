#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

    // Mensagem aparece na tela
    char mesg[] = "Digite uma mensagem: ";
    char str[80];
    char *nick;

    // para armazenar o número de linhas e o número de colunas da tela
    int row, col;

    // inicia a ncurses
    initscr();
    start_color();        /* Começa a funcionalidade das cores */
    cbreak();             /* Buffer de linha desativado, passe tudo para mim */
    keypad(stdscr, TRUE); /* Preciso daquele F1 bacana */
    noecho();

    init_color(COLOR_BLACK, 0, 0, 0);

    // obtém o número de linhas e colunas
    getmaxyx(stdscr, row, col);

    // imprime a mensagem no centro da tela
    echo();
    mvprintw(row / 2, col / 2, "%s", "mesg");
    getstr(str);
    nick = str;

    mvprintw(LINES - 2, 0, "Você digitou: %s", nick);
    getch();
    endwin();

    return 0;
}