#include "main.h"

typedef struct
{
	char name[MAX_INPUT_SIZE];
	char value[MAX_INPUT_SIZE];
} Alias;

Alias aliases[MAX_ALIASES];
int num_aliases = 0;

/**
 * print_aliases - Print the defined aliases.
 *
 * Return: void
 */
void print_aliases(void)
{
	for (int i = 0; i < num_aliases; i++)
	{
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

/**
 * find_alias - Find an alias by name.
 * @name: The alias name to search for.
 *
 * Return: Index of the alias if found, -1 if not found.
 */
int find_alias(const char *name)
{
	for (int i = 0; i < num_aliases; i++)
	{

		if (strcmp(aliases[i].name, name) == 0)
		{
			return (i);
		}
	}
	return (-1);
}
/**
 * main - programs entry point
 *
 * Return: Always 0
 */
int main(void)
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

		if (strncmp(input, "alias", 5) == 0)
		{
			char *token = strtok(input + 5, " ");


			if (token == NULL)
			{
				print_aliases();
			}
			else if (strchr(token, '=') == NULL)
			{
				while (token != NULL)
				{
					int alias_index = find_alias(token);
					if (alias_index != -1) {
						printf("%s='%s'\n", aliases[alias_index].name,
								aliases[alias_index].value);
					}
					token = strtok(NULL, " ");
				}
			}
			else
			{
				while (token != NULL)
				{
					char *equals = strchr(token, '=');
					if (equals != NULL) {
						*equals = '\0';
						int alias_index = find_alias(token);
						if (alias_index != -1) {
							strcpy(aliases[alias_index].value, equals + 1);
						}
						else if (num_aliases < MAX_ALIASES)

						{
							strcpy(aliases[num_aliases].name, token);
							strcpy(aliases[num_aliases].value, equals + 1);
							num_aliases++;
						}
						else
						{
							printf("Maximum number of aliases reached\n");
						}
					}
					token = strtok(NULL, " ");
				}
			}
		}
		else
		{
			 int status;
                wait(&status);
                if (WEXITSTATUS(status) == 0)
                {
                    execute_command(command, args);
                }
            }
        }

        num_commands = 0;
    }

    return (0);
}

