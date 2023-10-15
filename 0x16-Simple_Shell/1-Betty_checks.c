#include "main.h"

/**
 * count_words - Count the number of words in a sentence.
 * @sentence: The sentence to be counted.
 *
 * Return: The number of words in the sentence.
 */
int count_words(char *sentence)
{
	int count = 0;
	int i = 0;
	int in_word = 0;

	while (sentence[i] != '\0')
	{
		if (sentence[i] != ' ' && sentence[i] != '\t' && sentence[i]
				!= '\n')
		{
			if (!in_word)
			{
				in_word = 1;
				count++;
			}
		}
		else
		{
			in_word = 0;
		}
		i++;
	}

	return (count);
}

/**
 * main - print number words
 *
 * Return: Always 0
 */
int main(void)
{
	char sentence[100];
	int word_count = count_words(sentence);

	strcpy(sentence, "BETTY CHECKED");

	printf("BETTY CHECKED: ");
	fgets(sentence, sizeof(sentence), stdin);

	printf("Number of words: %d\n", word_count);

	return (0);
}
