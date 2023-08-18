#include "main.h"

/**
 * main - handles command line
 *
 * Return: 0 always
 */

int main(void)
{
	char input[MAX_INPUT_SIZE];
	char *args[MAX_INPUT_SIZE / 2];
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

		char *command = strtok(input, " ");
		int i = 0;

		while (command != NULL)
		{
			args[i] = command;
			command = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;

		pid_t child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			execve(args[0], args, NULL);
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
	}

	return (0);
}

