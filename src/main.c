#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#define EXIT 48
#define OP1 49
#define OP2 50
#define OP3 51
#define OP4 52
#define OP5 53

char *nickname;
char *password;
char *pathUsers = "/app/resources/users.txt";
char *pathRanking = "/app/resources/";
char *pathSavedGame = "/app/resources/saved_game.txt";
char *pathSavedGameR = "/app/resources/saved_gamec.txt";

int row, col, level = 0;
int score = 0;
int maxSquare = 2048;
int ENTER = 10;
int DEL = 263;
int DEL2 = 330;

int is_login = 0;

struct PlayerScore
{
	char *name;
	int score;
};

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
	mvprintw(row + 23, col, "|>=============================================================================================<|\n");
	switch (direction)
	{
	case KEY_UP:
		mvprintw(row + 24, col, "|>=============================================================================================<|\n");
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

int addNewUserToRanking()
{
	char *nameFile;
	if (level == 1)
	{
		nameFile = "ranking_level1.txt";
	}
	else if (level == 2)
	{
		nameFile = "ranking_level2.txt";
	}
	else if (level == 3)
	{
		nameFile = "ranking_level3.txt";
	}

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
				return addNewUserToRanking();
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

seeRanking(struct PlayerScore players[10], int level)
{
	int quantityPlayers = 0;

	if (level == 1)
	{
		quantityPlayers = readRanking("ranking_level1.txt", players);
	}
	else if (level == 2)
	{
		quantityPlayers = readRanking("ranking_level2.txt", players);
	}
	else if (level == 3)
	{
		quantityPlayers = readRanking("ranking_level3.txt", players);
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

char *addSpacesInt(int num, int size)
{
	char str[10];
	sprintf(str, "%i", num);
	printf("%s \n", str);

	return addSpaces(str, size);
}

char *readInput(int field, int screenError)
{
	int num;
	char ch;
	char name[20] = "";
	while (num != ENTER && num != EXIT)
	{
		if (field == 1)
		{
			mvprintw(row + 15, col, "|>                                  -> NOME: %s                              <|\n", addSpaces(name, 20));
		}
		else
		{
			mvprintw(row + 17, col, "|>                                  -> SENHA: %s                             <|\n", addSpaces(name, 20));
		}
		refresh();
		num = getch();
		if ((num >= 97 && num <= 122) || (num >= 65 && num <= 90))
		{
			ch = num;
			strncat(name, &ch, 1);
			if (strlen(name) >= 20)
			{
				if (screenError == 1)
				{
					screenInvalidLogin();
				}
				else if (screenError == 2)
				{
					screenInvalidNewUser(2);
				}
			}
		}
		else if (num == DEL || num == DEL2)
		{
			name[strlen(name) - 1] = '\0';
		}
	}
	if (num == ENTER)
	{
		mvprintw(row + 15, col, "|>                                     NOME: %s                              <|\n", addSpaces(name, 20));
	}

	if (num == EXIT)
	{
		num = 0;
		screenInit();
	}
	else if (strlen(name) == 0)
	{
		if (screenError == 1)
		{
			screenInvalidLogin();
		}
		else if (screenError == 2)
		{
			screenInvalidNewUser(2);
		}
	}

	num = 0;
	return strdup(name);
}

int login()
{
	FILE *ptr;
	char str[50];
	ptr = fopen(pathUsers, "a+");

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
	fPtr = fopen(pathUsers, "a+");

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

	mvprintw(row, col, "|>=============================================================================================<|\n");
	mvprintw(row + 1, col, "|>                                                                                             <|\n");
	mvprintw(row + 2, col, "|>              ********         ***********         *        *           **********           <|\n");
	mvprintw(row + 3, col, "|>                     *         *         *         *        *           *        *           <|\n");
	mvprintw(row + 4, col, "|>                     *         *         *         *        *           *        *           <|\n");
	mvprintw(row + 5, col, "|>              ********         *         *         **********           **********           <|\n");
	mvprintw(row + 6, col, "|>              *                *         *                  *           *        *           <|\n");
	mvprintw(row + 7, col, "|>              *                *         *                  *           *        *           <|\n");
	mvprintw(row + 8, col, "|>              ********         ***********                  *           **********           <|\n");
	mvprintw(row + 9, col, "|>                                                                                             <|\n");
	if (is_login == 0)
	{
		mvprintw(row + 10, col, "|>                                                                                             <|\n");
	}
	else
	{
		mvprintw(row + 10, col, "|>                                                                      %s   <|\n", addSpaces(nickname, 20));
	}
}

int screenInit()
{
	is_login = 0;
	title();
	mvprintw(row + 11, col, "|>                                 *****************************                               <|\n");
	mvprintw(row + 12, col, "|>                                 *  DIGITE PARA ONDE QUER IR *                               <|\n");
	mvprintw(row + 13, col, "|>                                 *****************************                               <|\n");
	mvprintw(row + 14, col, "|>                                   _________________________                                 <|\n");
	mvprintw(row + 15, col, "|>                                  | ENTRAR               (1)|                                <|\n");
	mvprintw(row + 16, col, "|>                                  | CRIAR CONTA          (2)|                                <|\n");
	mvprintw(row + 17, col, "|>                                  | MELHORES COLOCADOS   (3)|                                <|\n");
	mvprintw(row + 18, col, "|>                                  | SOBRE O JOGO         (4)|                                <|\n");
	mvprintw(row + 19, col, "|>                                  |_________________________|                                <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
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
			change = 7;
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
		screenChooseRanking();
		break;
	case 5:
		screenChooseLevelGame();
		break;
	case 6:
		screenMenu();
		break;
	case 7:
		screenAboutGame();
		break;
	default:
		break;
	}
}

int screenAboutGame()
{
	title();
	mvprintw(row + 11, col, "|>                                                                                             <|\n");
	mvprintw(row + 12, col, "|>                          2048 é um jogo de raciocínio criado em março de                 <|\n");
	mvprintw(row + 13, col, "|>                          2014 pelo desenvolvedor italiano Gabriele Cirulli, em              <|\n");
	mvprintw(row + 14, col, "|>                          que o objetivo é deslizar peças numeradas em uma                 <|\n");
	mvprintw(row + 15, col, "|>                          grade, combiná-las e criar um azulejo com o número 2048.           <|\n");
	mvprintw(row + 16, col, "|>                          Cirulli criou o jogo em um único fim de semana.                   <|\n");
	mvprintw(row + 17, col, "|>                                                                                             <|\n");
	mvprintw(row + 18, col, "|>                                                                                             <|\n");
	mvprintw(row + 19, col, "|>                                                                                             <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                             VOLTAR (0)      <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	int change = 0;
	int ch = 0;
	while (change == 0)
	{
		ch = getch();
		switch (ch)
		{
		case EXIT:
			screenInit();
			break;
		default:
			break;
		}
	}
	return 0;
}
screenChooseRanking()
{
	title();
	mvprintw(row + 11, col, "|>                               ***********************************                           <|\n");
	mvprintw(row + 12, col, "|>                               *  DIGITE QUAL TABELA DESEJA VER  *                           <|\n");
	mvprintw(row + 13, col, "|>                               ***********************************                           <|\n");
	mvprintw(row + 14, col, "|>                                   _________________________                                 <|\n");
	mvprintw(row + 15, col, "|>                                  | NIVEL 1              (1)|                                <|\n");
	mvprintw(row + 16, col, "|>                                  | NIVEL 2              (2)|                                <|\n");
	mvprintw(row + 17, col, "|>                                  | NIVEL 3              (3)|                                <|\n");
	mvprintw(row + 18, col, "|>                                  | SAIR                 (4)|                                <|\n");
	mvprintw(row + 19, col, "|>                                  |_________________________|                                <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	int change = 0;
	int ch = 0;
	while (change == 0)
	{
		ch = getch();
		switch (ch)
		{
		case OP1:
			screenRankingLevel(1);
			change = 1;
			break;
		case OP2:
			screenRankingLevel(2);
			change = 1;
			break;
		case OP3:
			screenRankingLevel(3);
			change = 1;
			break;
		case OP4:
			screenInit();
			change = 1;
			break;
		default:
			break;
		}
	}
}

int screenChooseLevelGame()
{
	title();
	mvprintw(row + 11, col, "|>                               ***********************************                           <|\n");
	mvprintw(row + 12, col, "|>                               * DIGITE QUAL NIVEL DESEJA JOGAR  *                           <|\n");
	mvprintw(row + 13, col, "|>                               ***********************************                           <|\n");
	mvprintw(row + 14, col, "|>                                   _________________________                                 <|\n");
	mvprintw(row + 15, col, "|>                                  | NIVEL 1              (1)|                                <|\n");
	mvprintw(row + 16, col, "|>                                  | NIVEL 2              (2)|                                <|\n");
	mvprintw(row + 17, col, "|>                                  | NIVEL 3              (3)|                                <|\n");
	mvprintw(row + 18, col, "|>                                  | SAIR                 (4)|                                <|\n");
	mvprintw(row + 19, col, "|>                                  |_________________________|                                <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	attron(COLOR_PAIR(1));
	int change = 0;
	int ch = 0;
	while (change == 0)
	{
		ch = getch();
		switch (ch)
		{
		case OP1:
			level = 1;
			return playGame(0);
			break;
		case OP2:
			level = 2;
			return playGame(0);
			break;
		case OP3:
			level = 3;
			return playGame(0);
			break;
		case OP4:
			return screenMenu();
			break;
		default:
			break;
		}
	}

	return 0;
}

screenInvalidLogin()
{
	title();
	mvprintw(row + 11, col, "|>                          *******************************************                        <|\n");
	mvprintw(row + 12, col, "|>                          *          NOME OU SENHA INCORRETOS       *                        <|\n");
	mvprintw(row + 13, col, "|>                          *******************************************                        <|\n");
	mvprintw(row + 14, col, "|>                                                                                             <|\n");
	mvprintw(row + 15, col, "|>                                   _________________________                                 <|\n");
	mvprintw(row + 16, col, "|>                                  | TENTAR NOVAMENTE     (1)|                                <|\n");
	mvprintw(row + 17, col, "|>                                  | VOLTAR PARA O INICIO (2)|                                <|\n");
	mvprintw(row + 18, col, "|>                                  |_________________________|                                <|\n");
	mvprintw(row + 19, col, "|>                                                                                             <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	int change = 0;
	int ch = 0;
	while (change == 0)
	{
		ch = getch();
		switch (ch)
		{
		case OP1:
			level = 1;
			screenLogin();
			break;
		case OP2:
			level = 2;
			screenInit();
			break;
		default:
			break;
		}
	}
}

screenLogin()
{
	title();
	mvprintw(row + 11, col, "|>                          *******************************************                        <|\n");
	mvprintw(row + 12, col, "|>                          * DIGITE SEUS DADOS DE ACESSO PARA ENTRAR *                        <|\n");
	mvprintw(row + 13, col, "|>                          *******************************************                        <|\n");
	mvprintw(row + 14, col, "|>                                                                                             <|\n");
	mvprintw(row + 15, col, "|>                                     NOME:                                                   <|\n");
	mvprintw(row + 16, col, "|>                                                                                             <|\n");
	mvprintw(row + 17, col, "|>                                     SENHA:                                                  <|\n");
	mvprintw(row + 18, col, "|>                                                                                             <|\n");
	mvprintw(row + 19, col, "|>                                                                                             <|\n");
	mvprintw(row + 20, col, "|>                                     | VOLTAR (0)|                                           <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	attron(COLOR_PAIR(1));

	char str[50];

	nickname = readInput(1, 1);

	password = readInput(2, 1);

	attron(COLOR_PAIR(1));

	refresh();
	if (login() == 1)
	{
		is_login = 1;
		screenMenu();
	}
	else
	{
		screenInvalidLogin();
	}
}

screenInvalidNewUser(int error)
{
	title();
	mvprintw(row + 11, col, "|>                          *******************************************                        <|\n");
	if (error == 4)
	{
		mvprintw(row + 12, col, "|>                          *  OUTRO JOGADOR POSSUI ESSE NOME         *                        <|\n");
	}
	else if (error == 2)
	{
		mvprintw(row + 12, col, "|>                          *  NOME OU SENHA MUITO LONGO              *                        <|\n");
	}

	else
	{
		mvprintw(row + 12, col, "|>                          *  TENTE COM OUTROS DADOS                 *                        <|\n");
	}

	mvprintw(row + 13, col, "|>                          *******************************************                        <|\n");
	mvprintw(row + 14, col, "|>                                                                                             <|\n");
	mvprintw(row + 15, col, "|>                                   _________________________                                 <|\n");
	mvprintw(row + 16, col, "|>                                  | TENTAR NOVAMENTE     (1)|                                <|\n");
	mvprintw(row + 17, col, "|>                                  | VOLTAR PARA O INICIO (2)|                                <|\n");
	mvprintw(row + 18, col, "|>                                  |_________________________|                                <|\n");
	mvprintw(row + 19, col, "|>                                                                                             <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	int change = 0;
	int ch = 0;
	while (change == 0)
	{
		ch = getch();
		switch (ch)
		{
		case OP1:
			level = 1;
			screenNewUser();
			break;
		case OP2:
			level = 2;
			screenInit();
			break;
		default:
			break;
		}
	}
}

screenNewUser()
{
	nickname = "";
	password = "";
	title();
	mvprintw(row + 11, col, "|>                       ***********************************************                       <|\n");
	mvprintw(row + 12, col, "|>                       * DIGITE SEUS DADOS DE ACESSO PARA O CADASTRO *                       <|\n");
	mvprintw(row + 13, col, "|>                       ***********************************************                       <|\n");
	mvprintw(row + 14, col, "|>                                                                                             <|\n");
	mvprintw(row + 15, col, "|>                                     NOME:                                                   <|\n");
	mvprintw(row + 16, col, "|>                                                                                             <|\n");
	mvprintw(row + 17, col, "|>                                     SENHA:                                                  <|\n");
	mvprintw(row + 18, col, "|>                                                                                             <|\n");
	mvprintw(row + 19, col, "|>                                                                                             <|\n");
	mvprintw(row + 20, col, "|>                                  | VOLTAR (0)|                                              <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	attron(COLOR_PAIR(1));

	nickname = readInput(1, 2);

	password = readInput(2, 2);

	int r = addNewUser();

	if (r == 1)
	{
		screenMenu();
	}
	else
	{
		screenInvalidNewUser(r);
	}

	screenMenu();
}

int screenMenu()
{
	title();
	mvprintw(row + 11, col, "|>                                 *****************************                               <|\n");
	mvprintw(row + 12, col, "|>                                 *  DIGITE PARA ONDE QUER IR *                               <|\n");
	mvprintw(row + 13, col, "|>                                 *****************************                               <|\n");
	mvprintw(row + 14, col, "|>                                   _________________________                                 <|\n");
	mvprintw(row + 15, col, "|>                                  | NOVO JOGO            (1)|                                <|\n");
	mvprintw(row + 16, col, "|>                                  | CONTINUAR PARTIDA    (2)|                                <|\n");
	mvprintw(row + 17, col, "|>                                  | RANKING              (3)|                                <|\n");
	mvprintw(row + 18, col, "|>                                  | SAIR                 (4)|                                <|\n");
	mvprintw(row + 19, col, "|>                                  |_________________________|                                <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	refresh();
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
			playGame(1);
			break;
		case OP3:
			change = 4;
			break;
		case OP4:
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

	return 0;
}

int screenRankingLevel(int level)
{
	struct PlayerScore players[10];
	seeRanking(players, level);
	title();
	mvprintw(row + 11, col, "|>                                   * MELHORES COLOCADOS DO NIVEL %i *                         <|\n", level);
	mvprintw(row + 12, col, "|>                                                                                             <|\n");
	mvprintw(row + 13, col, "|>                          1*- %s %s                                  <|\n", addSpaces(players[0].name, 20), addSpacesInt(players[0].score, 8));
	mvprintw(row + 14, col, "|>                                                                                             <|\n");
	mvprintw(row + 15, col, "|>                          2*- %s %s                                  <|\n", addSpaces(players[1].name, 20), addSpacesInt(players[1].score, 8));
	mvprintw(row + 16, col, "|>                                                                                             <|\n");
	mvprintw(row + 17, col, "|>                          3*- %s %s                                  <|\n", addSpaces(players[2].name, 20), addSpacesInt(players[2].score, 8));
	mvprintw(row + 18, col, "|>                                                                                             <|\n");
	mvprintw(row + 19, col, "|>                          4*- %s %s                                  <|\n", addSpaces(players[3].name, 20), addSpacesInt(players[3].score, 8));
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                          5*- %s %s                     VOLTAR(0)    <|\n", addSpaces(players[4].name, 20), addSpacesInt(players[4].score, 8));
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	int ch = 0;

	while (ch != EXIT)
	{
		ch = getch();
	}
	if (is_login == 0)
	{
		screenInit();
	}
	else if (is_login = 1)
	{
		screenMenu();
	}
}

screenLevel3(int size, int board[size][size])
{

	mvprintw(row + 12, col, "|>                                                                                             <|\n");
	mvprintw(row + 13, col, "|>                                                                  _________________________  <|\n");
	mvprintw(row + 14, col, "|>      |%s|%s|%s|%s|                                      | NOVO JOGO            (1)| <|\n",
			 formatNumber(board[0][0]), formatNumber(board[0][1]), formatNumber(board[0][2]), formatNumber(board[0][3]));
	mvprintw(row + 15, col, "|>      |%s|%s|%s|%s|                                      | VOLTAR JOGADA        (2)| <|\n",
			 formatNumber(board[1][0]), formatNumber(board[1][1]), formatNumber(board[1][2]), formatNumber(board[1][3]));
	mvprintw(row + 16, col, "|>      |%s|%s|%s|%s|                                      | SALVAR JOGO          (3)| <|\n",
			 formatNumber(board[2][0]), formatNumber(board[2][1]), formatNumber(board[2][2]), formatNumber(board[2][3]));
	mvprintw(row + 17, col, "|>      |%s|%s|%s|%s|                                      | MENU                 (4)| <|\n",
			 formatNumber(board[3][0]), formatNumber(board[3][1]), formatNumber(board[3][2]), formatNumber(board[3][3]));
	mvprintw(row + 18, col, "|>                                                                 | SAIR                 (5)| <|\n");
	mvprintw(row + 19, col, "|>                                                                 |_________________________| <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
}

screenLevel2(int size, int board[size][size])
{
	mvprintw(row + 12, col, "|>                                                                                             <|\n");
	mvprintw(row + 13, col, "|>                                                                  _________________________  <|\n");
	mvprintw(row + 14, col, "|>      |%s|%s|%s|%s|%s|                                 | NOVO JOGO            (1)| <|\n",
			 formatNumber(board[0][0]), formatNumber(board[0][1]), formatNumber(board[0][2]), formatNumber(board[0][3]), formatNumber(board[0][4]));
	mvprintw(row + 15, col, "|>      |%s|%s|%s|%s|%s|                                 | VOLTAR JOGADA        (2)| <|\n",
			 formatNumber(board[1][0]), formatNumber(board[1][1]), formatNumber(board[1][2]), formatNumber(board[1][3]), formatNumber(board[1][4]));
	mvprintw(row + 16, col, "|>      |%s|%s|%s|%s|%s|                                 | SALVAR JOGO          (3)| <|\n",
			 formatNumber(board[2][0]), formatNumber(board[2][1]), formatNumber(board[2][2]), formatNumber(board[2][3]), formatNumber(board[2][4]));
	mvprintw(row + 17, col, "|>      |%s|%s|%s|%s|%s|                                 | MENU                 (4)| <|\n",
			 formatNumber(board[3][0]), formatNumber(board[3][1]), formatNumber(board[3][2]), formatNumber(board[3][3]), formatNumber(board[3][4]));
	mvprintw(row + 18, col, "|>      |%s|%s|%s|%s|%s|                                 | SAIR                 (5)| <|\n",
			 formatNumber(board[4][0]), formatNumber(board[4][1]), formatNumber(board[4][2]), formatNumber(board[4][3]), formatNumber(board[4][4]));
	mvprintw(row + 19, col, "|>                                                                 |_________________________| <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
}

screenLevel1(int size, int board[size][size])
{
	mvprintw(row + 12, col, "|>                                                                                             <|\n");
	mvprintw(row + 13, col, "|>                                                                  _________________________  <|\n");
	mvprintw(row + 14, col, "|>      |%s|%s|%s|%s|%s|%s|                            | NOVO JOGO            (1)| <|\n",
			 formatNumber(board[0][0]), formatNumber(board[0][1]), formatNumber(board[0][2]), formatNumber(board[0][3]), formatNumber(board[0][4]), formatNumber(board[0][5]));
	mvprintw(row + 15, col, "|>      |%s|%s|%s|%s|%s|%s|                            | VOLTAR JOGADA        (2)| <|\n",
			 formatNumber(board[1][0]), formatNumber(board[1][1]), formatNumber(board[1][2]), formatNumber(board[1][3]), formatNumber(board[1][4]), formatNumber(board[1][5]));
	mvprintw(row + 16, col, "|>      |%s|%s|%s|%s|%s|%s|                            | SALVAR JOGO          (3)| <|\n",
			 formatNumber(board[2][0]), formatNumber(board[2][1]), formatNumber(board[2][2]), formatNumber(board[2][3]), formatNumber(board[2][4]), formatNumber(board[2][5]));
	mvprintw(row + 17, col, "|>      |%s|%s|%s|%s|%s|%s|                            | MENU                 (4)| <|\n",
			 formatNumber(board[3][0]), formatNumber(board[3][1]), formatNumber(board[3][2]), formatNumber(board[3][3]), formatNumber(board[3][4]), formatNumber(board[3][5]));
	mvprintw(row + 18, col, "|>      |%s|%s|%s|%s|%s|%s|                            | SAIR                 (5)| <|\n",
			 formatNumber(board[4][0]), formatNumber(board[4][1]), formatNumber(board[4][2]), formatNumber(board[4][3]), formatNumber(board[4][4]), formatNumber(board[4][5]));
	mvprintw(row + 19, col, "|>      |%s|%s|%s|%s|%s|%s|                            |_________________________| <|\n",
			 formatNumber(board[5][0]), formatNumber(board[5][1]), formatNumber(board[5][2]), formatNumber(board[5][3]), formatNumber(board[5][4]), formatNumber(board[5][5]));
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
}

showGame(int size, int board[size][size])
{
	clear();
	title();
	mvprintw(row + 11, col, "|>      | NIVEL: %d | SCORE: %s |                                                             <|\n",
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
		break;

	default:
		break;
	}
	refresh();
}

removeLine(int del)
{
	FILE *fptr1, *fptr2;
	char curr;
	int line_number = 0;

	fptr1 = fopen(pathSavedGame, "r");
	fptr2 = fopen(pathSavedGameR, "w");
	curr = getc(fptr1);
	if (curr != EOF)
	{
		line_number = 1;
	}
	while (1)
	{
		if (del != line_number)
			putc(curr, fptr2);
		curr = getc(fptr1);
		if (curr == '\n')
			line_number++;
		if (curr == EOF)
			break;
	}

	fclose(fptr1);
	fclose(fptr2);

	updateSaveGameTxt();
}

updateSaveGameTxt()
{
	FILE *fptr12, *fptr22;
	char curr;
	int del, line_number = 0;

	fptr12 = fopen(pathSavedGameR, "r");
	fptr22 = fopen(pathSavedGame, "w");
	curr = getc(fptr12);
	if (curr != EOF)
	{
		line_number = 1;
	}
	while (1)
	{
		if (del != line_number)
			putc(curr, fptr22);
		curr = getc(fptr12);
		if (curr == '\n')
			line_number++;
		if (curr == EOF)
			break;
	}

	fclose(fptr12);
	fclose(fptr22);
}

int countPosition()
{
	int result = 1;
	int position = 0;
	int isSaved = 0;
	FILE *ptr;
	char str[500] = "";

	ptr = fopen(pathSavedGame, "a+");

	if (NULL == ptr)
	{
		printf("file can't be opened \n");
	}
	while (fgets(str, 500, ptr) != NULL)
	{
		char *info = strtok(str, ",");
		int i = 0;
		while (info != NULL)
		{
			if (i == 0)
			{
				if (!strcmp(nickname, info))
				{
					isSaved = 1;
					position = result;
				}
				result++;
			}
			i++;
			info = strtok(NULL, ",");
		}
	}
	fclose(ptr);

	if (isSaved == 1)
	{
		return position;
	}
	return 0;
}

int saveGame(int size, int board[size][size])
{
	char line[400] = "\n";
	char str[10];
	strcat(line, nickname);
	strcat(line, ",");
	sprintf(str, "%d", level);
	strcat(line, str);
	strcat(line, ",");
	sprintf(str, "%d", score);
	strcat(line, str);

	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			sprintf(str, "%d", board[i][j]);
			strcat(line, ",");
			strcat(line, str);
		}
	}
	strcat(line, ";");

	int position = countPosition();
	if (position > 0)
	{
		removeLine(position);
	}

	saveGameTxt(line);
}

int saveGameTxt(char data[400])
{
	FILE *fPtr;
	fPtr = fopen(pathSavedGame, "a+");

	if (fPtr == NULL)
	{
		printf("\nUnable to open '%s' file.\n", "test.txt");
		printf("Please check whether file exists and you have write privilege.\n");
		exit(EXIT_FAILURE);
	}

	fputs(data, fPtr);
	fclose(fPtr);
	return 1;
}

int getSavedGame(int numbers[36])
{
	int result = 0;
	FILE *ptr;
	char str[1000];

	ptr = fopen(pathSavedGame, "a+");

	if (NULL == ptr)
	{
		printf("file can't be opened \n");
	}
	while (fgets(str, 1000, ptr) != NULL)
	{
		char *info = strtok(str, ",");
		int i = 0;
		while (info != NULL)
		{
			if (i == 0)
			{
				if (strcmp(nickname, info))
				{
					break;
				}
			}
			else if (i == 1)
			{
				result = 1;
				level = atoi(info);
			}
			else if (i == 2)
			{
				score = atoi(info);
			}
			else
			{
				numbers[i - 3] = atoi(info);
			}
			info = strtok(NULL, ",");
			i++;
		}
	}
	fclose(ptr);

	return result;
}

int screenGameNotFound()
{
	title();
	mvprintw(row + 11, col, "|>                          *******************************************                        <|\n");
	mvprintw(row + 12, col, "|>                          *             NENHUM JOGO SALVO           *                        <|\n");
	mvprintw(row + 13, col, "|>                          *******************************************                        <|\n");
	mvprintw(row + 14, col, "|>                                                                                             <|\n");
	mvprintw(row + 15, col, "|>                                   _________________________                                 <|\n");
	mvprintw(row + 16, col, "|>                                  | NOVO JOGO            (1)|                                <|\n");
	mvprintw(row + 17, col, "|>                                  | MENU                 (2)|                                <|\n");
	mvprintw(row + 18, col, "|>                                  |_________________________|                                <|\n");
	mvprintw(row + 19, col, "|>                                                                                             <|\n");
	mvprintw(row + 20, col, "|>                                                                                             <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	int change = 0;
	int ch = 0;
	while (change == 0)
	{
		ch = getch();
		switch (ch)
		{
		case OP1:
			return screenChooseLevelGame();
			break;
		case OP2:
			clear();
			return screenMenu();
			break;
		default:
			break;
		}
	}
	return 0;
}

int screenEndGame(int rg)
{
	title();
	mvprintw(row + 11, col, "|>                          *******************************************                        <|\n");
	if (rg == 1)
	{
		mvprintw(row + 12, col, "|>                          *               GANHOU                    *                        <|\n");
	}
	else
	{
		mvprintw(row + 12, col, "|>                          *               PERDEU                    *                        <|\n");
	}
	mvprintw(row + 13, col, "|>                          *******************************************                        <|\n");
	mvprintw(row + 14, col, "|>                                                                                             <|\n");
	mvprintw(row + 15, col, "|>                                   _________________________                                 <|\n");
	mvprintw(row + 16, col, "|>                                    NIVEL: %i                                                 <|\n", level);
	mvprintw(row + 17, col, "|>                                    PONTOS: %s                                             <|\n", formatNumber(score));
	mvprintw(row + 18, col, "|>                                   _________________________                                 <|\n");
	mvprintw(row + 19, col, "|>                                                                                             <|\n");
	mvprintw(row + 20, col, "|>                          PRESSIONE QUALQUER UMA TECLA PARA CONTINUAR                        <|\n");
	mvprintw(row + 21, col, "|>                                                                                             <|\n");
	mvprintw(row + 22, col, "|>=============================================================================================<|\n");
	getch();
	screenRankingLevel(level);
}

int playGame(int new)
{
	score = 0;
	int numbers[36];
	if (new == 1)
	{
		int r = getSavedGame(numbers);
		if (r == 0)
		{
			return screenGameNotFound();
		}
	}

	int boardSize = getBoardSize();
	int board[boardSize][boardSize];

	int boardCopy0[boardSize][boardSize];
	int boardCopy1[boardSize][boardSize];
	int position = 0;

	if (new == 1)
	{
		int now = 0;
		int i, j;
		for (i = 0; i < boardSize; i = i + 1)
		{
			for (j = 0; j < boardSize; j = j + 1)
			{
				board[i][j] = numbers[now];
				now++;
			}
		}
	}
	else
	{
		generateBoard(boardSize, board);
	}

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
		else if (position == OP3)
		{
			saveGame(boardSize, board);
		}

		else if (position == OP1 || position == OP4 || position == OP5)
		{
			keep = position;
			break;
		}

		else
		{
			keep = moveGame(boardSize, board, position, back == 1 ? boardCopy0 : boardCopy1, back);
			is_back = 1;
		}
		showGame(boardSize, board);
	}

	switch (keep)
	{
	case 1:
		screenEndGame(1);
		break;
	case 2:
		screenEndGame(0);
		break;
	case OP1:
		chooseScreen(5);
		break;
	case OP4:
		chooseScreen(6);
		break;
	case OP5:
		chooseScreen(1);
		break;
	default:
		break;
	}
	return 0;
}

int main()
{
	initscr();
	start_color();
	keypad(stdscr, TRUE);
	noecho();
	getmaxyx(stdscr, row, col);
	col = col / 4;
	row = row / 6;

	init_color(COLOR_BLACK, 0, 0, 0);
	init_pair(1, COLOR_RED, COLOR_BLACK);

	screenInit();

	endwin();
	return 0;
}
