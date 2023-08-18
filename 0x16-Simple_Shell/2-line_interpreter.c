#include "main.h"

/**
 * main - Entry point for the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];
	char *args[] = {NULL};
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
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{

			execve(input, args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{

			waitpid(child_pid, &status, 0);
		}
	}

	return (0);
}

