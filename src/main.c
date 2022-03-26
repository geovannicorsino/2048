#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char nickname[50];
char password[50];

title()
{
	system("clear");
	printf("             |>=============================================================================================<|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>              ********         ***********         *        *           **********           <|\n");
	printf("             |>                     *         *         *         *        *           *        *           <|\n");
	printf("             |>                     *         *         *         *        *           *        *           <|\n");
	printf("             |>              ********         *         *         **********           **********           <|\n");
	printf("             |>              *                *         *                  *           *        *           <|\n");
	printf("             |>              *                *         *                  *           *        *           <|\n");
	printf("             |>              ********         ***********                  *           **********           <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
}

int screen_init()
{
	title();
	printf("             |>                                 *****************************                               <|\n");
	printf("             |>                                 *  DIGITE A OPÇÃO DESEJADA  *                               <|\n");
	printf("             |>                                 *****************************                               <|\n");
	printf("             |>                                   _________________________                                 <|\n");
	printf("             |>                                  | ENTRAR               (1)|                                <|\n");
	printf("             |>                                  | CRIAR CONTA          (2)|                                <|\n");
	printf("             |>                                  | CLASSIFICAÇÃO        (3)|                                <|\n");
	printf("             |>                                  | CRÉDITOS             (4)|                                <|\n");
	printf("             |>                                  | SOBRE O JOGO         (5)|                                <|\n");
	printf("             |>                                  |_________________________|                                <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>=============================================================================================<|\n");
	int b;
	scanf("%i", &b);
	return b;
}

screen_login()
{
	title();
	printf("             |>                                 *******************************                             <|\n");
	printf("             |>                                 * DIGITE SEUS DADOS DE ACESSO *                             <|\n");
	printf("             |>                                 *******************************                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                     NOME:                                                   <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                     SENHA:                                                  <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>=============================================================================================<|\n");
	scanf("%s", &nickname);
	scanf("%s", &password);
}

int screen_menu()
{
	title();
	printf("             |>                                 *****************************                               <|\n");
	printf("             |>                                 *  DIGITE A OPÇÃO DESEJADA  *                               <|\n");
	printf("             |>                                 *****************************                               <|\n");
	printf("             |>                                   _________________________                                 <|\n");
	printf("             |>                                  | NOVO JOGO            (1)|                                <|\n");
	printf("             |>                                  | CRIAR CONTA          (2)|                                <|\n");
	printf("             |>                                  | CLASSIFICAÇÃO        (3)|                                <|\n");
	printf("             |>                                  | CRÉDITOS             (4)|                                <|\n");
	printf("             |>                                  | SAIR                 (5)|                                <|\n");
	printf("             |>                                  |_________________________|                                <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>=============================================================================================<|\n");
	int b;
	scanf("%i", &b);
	return b;
}

int screen_ranking_level1()
{
	printf("             |>=============================================================================================<|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                             ******   ******   *    *   ******                               <|\n");
	printf("             |>                                  *   *    *   *    *   *    *                               <|\n");
	printf("             |>                             ******   *    *   ******   ******                               <|\n");
	printf("             |>                             *        *    *        *   *    *                               <|\n");
	printf("             |>                             ******   ******        *   ******                               <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                CLASSIFICAÇÃO DO NÍVEL 1                                     <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                   1*-                                                       <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                       SAIR (0)                                              <|\n");
	printf("             |>=============================================================================================<|\n");
	int b;
	scanf("%i", &b);
	return b;
}

screen_game_level1()
{
	printf("             |>=============================================================================================<|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                             ******   ******   *    *   ******                               <|\n");
	printf("             |>                                  *   *    *   *    *   *    *                               <|\n");
	printf("             |>                             ******   *    *   ******   ******                               <|\n");
	printf("             |>                             *        *    *        *   *    *                               <|\n");
	printf("             |>                             ******   ******        *   ******                               <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>    __                                                   _________________________           <|\n");
	printf("             |>   |2 |                                                  | NOVO JOGO            (1)|          <|\n");
	printf("             |>   |__|                                                  | VOLTAR JOGADA        (2)|          <|\n");
	printf("             |>   |0 |                                                 | SALVAR JOGO          (3)|          <|\n");
	printf("             |>   |__|                                                  | MENU                 (4)|          <|\n");
	printf("             |>   |0 |                                                 | SAIR                 (5)|          <|\n");
	printf("             |>   |__|                                                 |_________________________|          <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>                                                                                             <|\n");
	printf("             |>=============================================================================================<|\n");
}

int main()
{
	int option = screen_init();

	switch (option)
	{
	case 2:
		screen_login();
	default:
		break;
	}

	return 0;
}