#include "main.h"

/**
 * read_line - Read a line of text from the magical paper.
 * @line: The place to write the line of text.
 *
 * Return: Number of letters read.
 */
int read_line(char *line)
{
	static char buffer[BUFFER_SIZE];
	static int position = 0;
	static int chars_in_buffer = 0;

	int i = 0;

	if (position >= chars_in_buffer)
	{
		chars_in_buffer = read(0, buffer, BUFFER_SIZE);
		position = 0;
		if (chars_in_buffer <= 0)
		{
			return (0);
		}
	}

	while (position < chars_in_buffer && buffer[position] != '\n')
	{
		line[i] = buffer[position];
		i++;
		position++;
	}

	line[i] = '\0';
	position++;

	return (i);
}
/**
 * main - programme entry point
 *
 * Return: Always 0
 */

int main(void)
{
	char input[BUFFER_SIZE];

	while (1)
	{
		printf("Tell me something magical: ");
		int letters_read = read_line(input);

		if (letters_read == 0)
		{
			break;
		}

		printf("You said: %s\n", input);
	}

	printf("Goodbye, magical friend!\n");

	return (0);
}

