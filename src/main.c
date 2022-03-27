#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

#define EXIT 48
#define OP1 49
#define OP2 50
#define OP3 51
#define OP4 52

char *nickname;
char *password;
char *path_users = "/app/resources/users.txt";

int row, col;

int login()
{
	FILE *ptr;
	char str[50];
	ptr = fopen(path_users, "a+");

	if (NULL == ptr)
	{
		printf("file can't be opened \n");
	}
	while (fgets(str, 50, ptr) != NULL)
	{
		char *users = strtok(str, ";");

		while (users != NULL)
		{
			char *user = strtok(str, ":");
			char *name;

			while (user != NULL)
			{
				if (!strcmp(nickname, user) || !strcmp(nickname, name))
				{
					name = nickname;
					if (!strcmp(password, user))
					{
						return 1;
					}
				}
				else
				{
					break;
				}
				user = strtok(NULL, " ");
			}
			users = strtok(NULL, " ");
		}
	}
	fclose(ptr);
	return 0;
}

int addNewUser()
{
	FILE *fPtr;
	fPtr = fopen(path_users, "a+");

	if (fPtr == NULL)
	{
		printf("\nUnable to open '%s' file.\n", "test.txt");
		printf("Please check whether file exists and you have write privilege.\n");
		exit(EXIT_FAILURE);
	}

	char dataToAppend[100] = "";
	strcat(dataToAppend, nickname);
	strcat(dataToAppend, ":");
	strcat(dataToAppend, password);
	strcat(dataToAppend, ";\n");

	if (strlen(nickname) > 20)
	{
		return 2;
	}
	if (validSpaces(nickname) == 1 || validSpaces(password) == 1)
	{
		return 3;
	}
	if (validOnlyName(fPtr) == 1)
	{
		return 4;
	}

	fputs(dataToAppend, fPtr);
	fclose(fPtr);
	return 1;
}

int validOnlyName(FILE *ptr)
{
	char str[50];

	while (fgets(str, 50, ptr) != NULL)
	{
		char *users = strtok(str, ";");

		while (users != NULL)
		{
			char *user = strtok(str, ":");

			while (user != NULL)
			{
				if (!strcmp(nickname, user))
				{
					return 1;
				}
				else
				{
					break;
				}
				user = strtok(NULL, " ");
			}
			users = strtok(NULL, " ");
		}
	}
	return 0;
}

int validSpaces(char str[])
{
	int i = 0;
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] == ' ')
		{
			return 1;
		}
	}
	return 0;
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
	mvprintw(row + 10, col, "             |>                                                                                             <|\n");
}

int screenInit()
{
	title();
	mvprintw(row + 11, col, "             |>                                 *****************************                               <|\n");
	mvprintw(row + 12, col, "             |>                                 *  DIGITE PARA ONDE QUER IR *                               <|\n");
	mvprintw(row + 13, col, "             |>                                 *****************************                               <|\n");
	mvprintw(row + 14, col, "             |>                                   _________________________                                 <|\n");
	mvprintw(row + 15, col, "             |>                                  | ENTRAR               (1)|                                <|\n");
	mvprintw(row + 16, col, "             |>                                  | CRIAR CONTA          (2)|                                <|\n");
	mvprintw(row + 17, col, "             |>                                  | RANKING              (3)|                                <|\n");
	mvprintw(row + 18, col, "             |>                                  | SOBRE O JOGO         (4)|                                <|\n");
	mvprintw(row + 19, col, "             |>                                  |_________________________|                                <|\n");
	mvprintw(row + 20, col, "             |>                                                                                             <|\n");
	mvprintw(row + 21, col, "             |>                                                                                             <|\n");
	mvprintw(row + 22, col, "             |>=============================================================================================<|\n");
	attron(COLOR_PAIR(1));
	refresh();
	int ch = 0;
	int change = 0;

	while (change == 0)
	{
		ch = getch();
		switch (ch)
		{
		case OP1:
			change = 2;
			break;
		case OP2:
			change = 3;
			break;
		case OP3:
			change = 4;
			break;
		case OP4:
			change = 5;
			break;
		case EXIT:
			endwin();
			exit(1);
			break;
		default:
			break;
		}
	}
	chooseScreen(change);
}

chooseScreen(int screen)
{
	switch (screen)
	{
	case 1:
		screenInit();
		break;
	case 2:
		screenLogin();
		break;
	case 3:
		screenNewUser();
		break;
	case 4:
		screen_ranking_level1();
		break;
	case 5:
		screen_game_level1();
		break;
	default:
		break;
	}
}

screenLogin()
{
	int ch;
	title();
	mvprintw(row + 11, col, "             |>                          *******************************************                        <|\n");
	mvprintw(row + 12, col, "             |>                          * DIGITE SEUS DADOS DE ACESSO PARA ENTRAR *                        <|\n");
	mvprintw(row + 13, col, "             |>                          *******************************************                        <|\n");
	mvprintw(row + 14, col, "             |>                                                                                             <|\n");
	mvprintw(row + 15, col, "             |>                                     NOME:                                                   <|\n");
	mvprintw(row + 16, col, "             |>                                                                                             <|\n");
	mvprintw(row + 17, col, "             |>                                     SENHA:                                                  <|\n");
	mvprintw(row + 18, col, "             |>                                                                                             <|\n");
	mvprintw(row + 19, col, "             |>                                                                                             <|\n");
	mvprintw(row + 20, col, "             |>                                                                                             <|\n");
	mvprintw(row + 21, col, "             |>                                                                                             <|\n");
	mvprintw(row + 22, col, "             |>=============================================================================================<|\n");
	attron(COLOR_PAIR(1));

	char str[50];

	echo();

	mvprintw(row + 15, col + 58, "%s", "");
	getstr(str);
	nickname = strdup(str);

	mvprintw(row + 17, col + 59, "%s", "");
	getstr(str);
	password = strdup(str);

	mvprintw(LINES - 3, 0, "Você digitou: %s", nickname);
	mvprintw(LINES - 2, 0, "Você digitou: %s", password);
	attron(COLOR_PAIR(1));
	noecho();
	refresh();
	if (login() == 1)
	{
		screenMenu();
	}
	else
	{
		printw("\n Error \n");
		getch();
	}
}

screenNewUser()
{
	int ch;
	title();
	mvprintw(row + 11, col, "             |>                       ***********************************************                       <|\n");
	mvprintw(row + 12, col, "             |>                       * DIGITE SEUS DADOS DE ACESSO PARA O CADASTRO *                       <|\n");
	mvprintw(row + 13, col, "             |>                       ***********************************************                       <|\n");
	mvprintw(row + 14, col, "             |>                                                                                             <|\n");
	mvprintw(row + 15, col, "             |>                                     NOME:                                                   <|\n");
	mvprintw(row + 16, col, "             |>                                                                                             <|\n");
	mvprintw(row + 17, col, "             |>                                     SENHA:                                                  <|\n");
	mvprintw(row + 18, col, "             |>                                                                                             <|\n");
	mvprintw(row + 19, col, "             |>                                                                                             <|\n");
	mvprintw(row + 20, col, "             |>                                                                                             <|\n");
	mvprintw(row + 21, col, "             |>                                                                                             <|\n");
	mvprintw(row + 22, col, "             |>=============================================================================================<|\n");
	attron(COLOR_PAIR(1));

	char str[50];

	echo();

	mvprintw(row + 15, col + 58, "%s", "");
	getstr(str);
	nickname = strdup(str);

	mvprintw(row + 17, col + 59, "%s", "");
	getstr(str);
	password = strdup(str);

	mvprintw(LINES - 3, 0, "Você digitou: %s", nickname);
	mvprintw(LINES - 2, 0, "Você digitou: %s", password);
	attron(COLOR_PAIR(1));
	noecho();
	refresh();

	switch (addNewUser())
	{
	case 1:
		screenMenu();
		break;

	default:
		printw("\n Error \n");
		getch();
		break;
	}
}

screenMenu()
{
	title();
	mvprintw(row + 11, col, "             |>                                 *****************************                               <|\n");
	mvprintw(row + 12, col, "             |>                                 *  DIGITE PARA ONDE QUER IR *                               <|\n");
	mvprintw(row + 13, col, "             |>                                 *****************************                               <|\n");
	mvprintw(row + 14, col, "             |>                                   _________________________                                 <|\n");
	mvprintw(row + 15, col, "             |>                                  | NOVO JOGO            (1)|                                <|\n");
	mvprintw(row + 16, col, "             |>                                  | RANKING              (2)|                                <|\n");
	mvprintw(row + 17, col, "             |>                                  | SAIR                 (3)|                                <|\n");
	mvprintw(row + 18, col, "             |>                                  |_________________________|                                <|\n");
	mvprintw(row + 19, col, "             |>                                                                                             <|\n");
	mvprintw(row + 20, col, "             |>                                                                                             <|\n");
	mvprintw(row + 21, col, "             |>                                                                                             <|\n");
	mvprintw(row + 22, col, "             |>=============================================================================================<|\n");
	int ch = 0;
	int change = 0;

	while (change == 0)
	{
		ch = getch();
		switch (ch)
		{
		case OP1:
			change = 5;
			break;
		case OP2:
			change = 4;
			break;
		case OP3:
			change = 1;
			break;
		case EXIT:
			endwin();
			exit(1);
			break;
		default:
			break;
		}
	}
	chooseScreen(change);
}

int screen_ranking_level1()
{
	printw("             |>=============================================================================================<|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                             ******   ******   *    *   ******                               <|\n");
	printw("             |>                                  *   *    *   *    *   *    *                               <|\n");
	printw("             |>                             ******   *    *   ******   ******                               <|\n");
	printw("             |>                             *        *    *        *   *    *                               <|\n");
	printw("             |>                             ******   ******        *   ******                               <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                      RANKING DO NÍVEL 1                                     <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                   1*-                                                       <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                                                                             <|\n");
	printw("             |>                                       SAIR (0)                                              <|\n");
	printw("             |>=============================================================================================<|\n");
}

screen_game_level1()
{
	title();
	mvprintw(row + 11, col, "             |>                   ____________                                                              <|\n");
	mvprintw(row + 12, col, "             |>                  |            |                                                             <|\n");
	mvprintw(row + 13, col, "             |>                  |            |                                  _________________________  <|\n");
	mvprintw(row + 14, col, "             |>                  |            |                                 | NOVO JOGO            (1)| <|\n");
	mvprintw(row + 15, col, "             |>                  |            |                                 | VOLTAR JOGADA        (2)| <|\n");
	mvprintw(row + 16, col, "             |>                  |            |                                 | SALVAR JOGO          (3)| <|\n");
	mvprintw(row + 17, col, "             |>                  |            |                                 | MENU                 (4)| <|\n");
	mvprintw(row + 18, col, "             |>                  |            |                                 | SAIR                 (5)| <|\n");
	mvprintw(row + 19, col, "             |>                  |____________|                                 |_________________________| <|\n");
	mvprintw(row + 20, col, "             |>                                                                                             <|\n");
	mvprintw(row + 21, col, "             |>                                                                                             <|\n");
	mvprintw(row + 22, col, "             |>=============================================================================================<|\n");
	getch();
}

int main()
{

	int ch = 0;

	initscr();
	start_color(); // Começa a funcionalidade das cores
	// cbreak();			   Buffer de linha desativado, passe tudo para mim
	keypad(stdscr, TRUE); // Preciso daquele F1 bacana
	noecho();
	getmaxyx(stdscr, row, col);
	col = col / 8;
	row = row / 8;

	init_color(COLOR_BLACK, 0, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	int option = screenInit();
	endwin();
	return 0;
}
