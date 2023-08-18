#include "main.h"

/**
 * file_command - finds the command of the file
 * @command: command to be executed
 *
 * Return: file command
 */
void file_command(char *command)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		char *args[MAX_INPUT_SIZE];
		int arg_count = 0;

		char *token = strtok(command, " ");
		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		execvp(args[0], args);
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
 * tmpmain - programs entry point
 * @argc: argument count
 * @argv: array to pointer argument
 *
 * Return: Always 0
 */
int tmpmain(int argc, char *argv[])
{
	if (argc == 1)
	{
		char input[MAX_INPUT_SIZE];
		while (1) {
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

			execute_command(input);
		}
	}
	else if (argc == 2) 
	{
		FILE *file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("File opening error");
			return (EXIT_FAILURE);
		}

		char line[MAX_INPUT_SIZE];
		while (fgets(line, sizeof(line), file) != NULL)
		{
			line[strcspn(line, "\n")] = '\0';
			execute_command(line);
		}

		fclose(file);
	}

	return (0);
}

