#include "main.h"

/**
 * separate_command_args - separates commands and arguments
 * @input: input for the commands
 * @command: commands used for arguments
 * @args: argument types
 *
 * Return: 
 */

void separate_command_args(char *input, char *command, char *args[])
{
	char *token = strtok(input, " ");
	if (token == NULL)
	{
		command[0] = '\0';
		return;
	}

	strcpy(command, token);

	int arg_index = 0;
	while ((token = strtok(NULL, " ")) != NULL)
	{
		args[arg_index++] = token;
	}
	args[arg_index] = NULL;
}

/**
 * main - programmes entry point
 *
 * Return: Always 0
 */

int main(void)
{
	char input[MAX_INPUT_SIZE];
	char command[MAX_INPUT_SIZE];
	char *args[MAX_INPUT_SIZE];
	int status;

	while (1)
	{
		printf("($) ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			printf("Goodbye!\n");
			break;
		}

		separate_command_args(input, command, args);

		if (command[0] != '\0')
		{
			printf("Command: %s\n", command);
			printf("Arguments: ");

			for (int i = 0; args[i] != NULL; i++)
			{
				printf("%s ", args[i]);
			}
			printf("\n");
		}
	}

	return (0);
}

