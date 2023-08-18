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
 * main - handles full path
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

		char *full_path = check_command(input);

		if (full_path != NULL)
		{
			pid_t child_pid = fork();
			if (child_pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (child_pid == 0)
			{
				execve(full_path, (char *[]){input, NULL},
						NULL);
				perror(input);
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(child_pid, &status, 0);
			}
			free(full_path);
		}
		else
		{
			printf("./hsh: 1: %s: not found\n", input);
		}
	}

	return (0);
}

