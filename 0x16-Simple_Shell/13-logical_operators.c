#include "main.h"

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
 * logical_command - Execute a single command.
 * @command: The command to execute.
 * @args: The arguments for the command.
 */
void logical_command(char *command, char *args[])
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execvp(command, args);
		perror("Execution error");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Forking error");
	}
	else
	{
		int status;
		wait(&status);
	}
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
		int should_execute = 1;

		if (strcmp(args[arg_count - 1], "&&") == 0)
		{
			should_execute = 0;
			args[arg_count - 1] = NULL;
		}
		else if (strcmp(args[arg_count - 1], "||") == 0)
		{
			should_execute = 1;
			args[arg_count - 1] = NULL;
		}

		pid_t pid = fork();

		if (pid == 0)
		{
			execvp(command, args);
			perror("Execution error");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("Forking error");
		}
		else
		{
			wait(&status);
			if (should_execute && WEXITSTATUS(status) != 0)
			{
				printf("Command failed\n");
			}
		}
	}

	return (0);
}
