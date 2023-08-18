#include "main.h"

/**
 * remove_comments - removes comments
 * @input: character of comments to be replaced
 *
 * Return: return the replaced comments as 0
 */

void remove_comments(char *input)
{
	char *comment = strchr(input, '#');
	if (comment != NULL)
	{
		*comment = '\0';
	}
}

/**
 * main - program entry point
 *
 * Return: Always 0
 */

int main(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		printf("($) ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0) {
			printf("Goodbye!\n");
			break;
		}
		char *comment = strchr(input, '#');
		if (comment != NULL) {
			*comment = '\0';
		}

		char *trimmed_input = input;
		while (*trimmed_input == ' ')
		{
			trimmed_input++;
		}
		int len = strlen(trimmed_input);
		while (len > 0 && trimmed_input[len - 1] == ' ')
		{
			trimmed_input[--len] = '\0';
		}

		if (strlen(trimmed_input) > 0)
		{
			pid_t pid = fork();

			if (pid == 0)
			{
				char *command = strtok(trimmed_input, " ");
				char *args[MAX_INPUT_SIZE];
				int arg_count = 0;

				while (command != NULL)
				{
					args[arg_count++] = command;
					command = strtok(NULL, " ");
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
	}

	return (0);
}

