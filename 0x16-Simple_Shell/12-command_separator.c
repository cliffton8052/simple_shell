#include "main.h"
#include <sys/wait.h>

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
	int status;
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
 * execute_command - Execute a single command.
 * @command: The command to execute.
 * @args: The arguments for the command.
 */
void execute_command(char *command, char *args[])
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
		wait(&status);
	}
	else
	{
		perror("forking error");
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
	char *commands[MAX_INPUT_SIZE];
	int num_commands = 0;

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

		char *token = strtok(input, ";");
		while (token != NULL)
		{
			commands[num_commands++] = token;
			token = strtok(NULL, ";");
		}
		int i;

		for (int i = 0; i < num_commands; i++)
		{
			char command[MAX_INPUT_SIZE];
			char *args[MAX_INPUT_SIZE];
			int arg_count = split_input(commands[i], command, args);

			if (strcmp(command, "cd") == 0)
			{
				int exit_status = 0;
				if (arg_count >= 2)
				{
					exit_status = atoi(args[1]);
				}

				printf("Exiting with status %d\n", exit_status);
				exit(exit_status);
			}
			else if (strcmp(command, "exit") == 0)
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
					wait(&status);
				}
			}
			else
			{
				execute_command(command, args);
			}
		}

		num_commands = 0;
	}

	return 0;
}

