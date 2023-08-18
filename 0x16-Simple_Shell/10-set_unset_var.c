#include "main.h"
#include <stdlib.h>

#define MAX_INPUT_LENGTH 100

/**
 * split_input - Split input into command and arguments.
 * @input: The input string.
 * @command: The pointer to store the command.
 * @args: The array to store arguments.
 *
 * Return: Number of arguments.
 */

int split_input(char *input, char *command, char *args[])
{
	int arg_count = 0;
	char *token = strtok(input, " ");

	while (token != NULL)
	{
		if (arg_count == 0)
		{
			strcpy(command, token);
		}
		else if (arg_count <= MAX_ARGS)
		{
			args[arg_count - 1] = token;
		}

		token = strtok(NULL, " ");
		arg_count++;
	}

	return (arg_count - 1);
}
/**
 * main - programms entry point
 *
 * Return: Always 0
 */

int main()
{
	char input[MAX_INPUT_LENGTH];
	char *args[3];
	int num_args;

	while (1)
	{
		printf("($) ");
		if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
		{
			break;
		}

		num_args = 0;
		args[num_args] = strtok(input, " \t\n");
		while (args[num_args] != NULL)
		{
			num_args++;
			args[num_args] = strtok(NULL, " \t\n");
		}
		args[num_args] = NULL;

		if (num_args > 0)
		{
			if (strcmp(args[0], "setenv") == 0)
			{
				if (num_args != 3)
				{
					fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
				}
				else 
				{
					if (setenv(args[1], args[2], 1) != 0)
					{
						perror("setenv");
					}
				}
			}
			else if (strcmp(args[0], "unsetenv") == 0)
			{
				if (num_args != 2) {
					fprintf(stderr, "Usage: unsetenv VARIABLE\n");
				}
				else 
				{
					if (unsetenv(args[1]) != 0) 
					{
						perror("unsetenv");
					}
				}
			}
			else 
			{

				printf("Executing: %s\n", args[0]);
			}
		}
	}

	return (0);
}

