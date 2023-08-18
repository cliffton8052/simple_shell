#include "main.h"

/**
 * check_command - Check if the command exists in the PATH.
 * @command: The command to check.
 *
 * Return: The full path of the command if found, otherwise NULL.
 */

char *check_command(char *command)
{
	char *path = getenv("PATH");
	char *token;
	char *full_path = malloc(MAX_INPUT_SIZE);

	if (path == NULL || full_path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		snprintf(full_path, MAX_INPUT_SIZE, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		token = strtok(NULL, ":");
	}

	free(full_path);
	return (NULL);
}

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
	char *token = input;

	while (*token != '\0')
	{
		while (*token == ' ')
			token++;

		if (*token == '\0')
			break;

		if (arg_count == 0)
		{

			while (*token != ' ' && *token != '\0')
			{
				*command = *token;
				command++;
				token++;
			}
			*command = '\0';
		}
		else
		{

			args[arg_count - 1] = token;
			arg_count++;


			while (*token != ' ' && *token != '\0')
				token++;

			if (*token == '\0')
				break;

			*token = '\0';
		}

		arg_count++;
	}

	return (arg_count - 1);
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

		int arg_count = split_input(input, command, args);

	}

	return (0);
}
