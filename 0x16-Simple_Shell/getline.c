#include <stdio.h>
#include <stdlib.h>

/**
 * main - print line
 *
 * Return: Always 0
 */

int main() 
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			break;
		}

		printf("You entered: %s", line);
	}

	free(line);
	return (0);
}

