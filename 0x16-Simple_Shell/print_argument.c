#include <stdio.h>

/**
 * main - print argument
 * @ac: argument character
 * @av: pointer to argument vector
 *
 * Return: 0 always
 */

int main(int ac, char **av)
{
    for (int a = 1; av[a] != NULL; a++)
    {
        printf("%s\n", av[a]);
    }
    return (0);
}

