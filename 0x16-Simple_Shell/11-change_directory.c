#include "main.h"
#include <sys/types.h>
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
 * execute_cd - Execute the "cd" command.
 * @args: The array of arguments.
 *
 * Return: 0 on success, -1 on failure.
 */

int execute_cd(char *args[])
{
	char cwd[MAX_INPUT_SIZE];
	char *new_directory = args[1];

	if (new_directory == NULL)
	{
		new_directory = getenv("HOME");
	}

	if (chdir(new_directory) != 0)
	{
		perror("cd error");
		return (-1);
	}

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("PWD", cwd, 1);
	}
	else
	{
		perror("getcwd error");
		return (-1);
	}

	return (0);
}

/**
 * main - programmes main entry point
 *
 * Return: Always 0
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];
	char command[MAX_INPUT_SIZE];
	char *args[MAX_INPUT_SIZE];
	int status;

	int arg_count;

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

		switch (command[0])
		{
			case 'c':
				if (strcmp(command, "cd") == 0)
				{
					execute_cd(args);
				}
				else
				{
					printf("Command not found: %s\n", command);
				}
				break;

			case 'e':
				if (strcmp(command, "exit") == 0)
				{
					int exit_status = 0;
					if (arg_count >= 2)
					{
						exit_status = atoi(args[1]);
					}

					printf("Exiting with status %d\n", exit_status);
					exit(exit_status);
				}
				else
				{
					printf("Command not found: %s\n",
							command);
				}
				break;

			default:
				pid_t pid = fork();

				if (pid == 0)
				{
					execvp(command, args);
					perror("Execution error");
					exit(EXIT_FAILURE);
				}
				else if (pid < 0)
				{
					wait(wait&status);
				}
				else
				{
					perror("forking error");
				}
				break;
		}
	}

	return (0);
}

