#include "main.h"

/**
 * find_variable - Find a variable by name.
 * @name: The variable name to search for.
 *
 * Return: Pointer to the variable value if found, NULL if not found.
 */
char *find_variable(const char *name)
{
	for (int i = 0; i < num_variables; i++)
	{
		if (strcmp(variables[i].name, name) == 0)
		{
			return variables[i].value;
		}
	}
	return NULL;
}

/**
 * replace_variables - Replace special variables in the input.
 * @input: The input string to replace variables in.
 *
 * Return: The modified input string with variables replaced.
 */
char *replace_variables(char *input)
{
	char *result = malloc(MAX_INPUT_SIZE);
	char *token = strtok(input, " ");
	char *pos = result;

	while (token != NULL)
	{
		char *variable_value = NULL;
		if (strcmp(token, "$?") == 0) 
		{
			variable_value = find_variable("?");
		}
		else if (strcmp(token, "$$") == 0) 
		{
			snprintf(variables[num_variables].value, 
					sizeof(variables[num_variables].value), "%d", getpid());
			variable_value = variables[num_variables].value;
			num_variables++;
		}
		else 
		{
			variable_value = token;
		}

		size_t len = strlen(variable_value);
		memcpy(pos, variable_value, len);
		pos += len;
		*pos++ = ' ';
		token = strtok(NULL, " ");
	}
	*--pos = '\0';
	return result;
}

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

		if (strcmp(input, "exit") == 0)
		{
			printf("Goodbye!\n");
			break;
		}

		char *modified_input = replace_variables(input);
		pid_t pid = fork();

		if (pid == 0)
		{
			char *command = strtok(modified_input, " ");
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

		free(modified_input);
	}

	return (0);
}

