#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *nickname = "MA";
char *password = "789";
char *path_users = "/app/resources/users.txt";


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

int main()
{
	int a = login();
	printf("%d", a);
	return 0;
}