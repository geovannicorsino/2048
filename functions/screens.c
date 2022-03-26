#include <ncurses.h>

int main()
{
    int ch;

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    printw("Pressione alguma tecla e a mesma será exibida em negrito.\n");
    ch = getch();

    if (ch == KEY_F(1))
    {
        printw("A tecla F1 foi pressionada!");
    }
    else
    {
        printw("A tecla que você pressionou foi: ");
        // attron(A_BOLD);
        if (ch == KEY_UP)
        {
            printw("boa %c", ch);
        }

        // attroff(A_BOLD);
    }
    refresh();
    getch();
    endwin();

    return 0;
}