#include "main.h"

#define MAX_INPUT_SIZE 100

/**
 * get_command - Check if the command exists in the PATH.
 * @command: The command to check.
 *
 * Return: The full path of the command if found, otherwise NULL.
 */
char *get_command(char *command)
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
 * main - programmes entry point
 *
 * Return: Always 0
 */

int main(void)
{
	char input[MAX_INPUT_SIZE];
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
			printf("Exiting the shell...\n");
			break;
		}

		char *command = strtok(input, " ");
		char *full_path = check_command(command);

	}

	return (0);
}

