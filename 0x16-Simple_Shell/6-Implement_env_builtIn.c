#include "main.h"

#define MAX_INPUT_SIZE 100

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
 * execute_env - Execute the env built-in command.
 */
void execute_env(void)
{
	char **env = __environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
/**
 * main - programme entry point
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
			printf("Goodbye!\n");
			break;
		}
		else if (strcmp(input, "env") == 0)
		{
			execute_env();
		}
		else
		{
			char *command = strtok(input, " ");
			char *full_path = check_command(command);

		}
	}

	return (0);
}

