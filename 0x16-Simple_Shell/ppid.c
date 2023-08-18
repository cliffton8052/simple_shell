#include <stdio.h>
#include <unistd.h>

/**
 * main - PPID
 *
 * Return: Always 0
 */

int main(void) 
{
	pid_t parent_pid = getppid();
	printf("Parent PID: %u\n", parent_pid);
	return 0;
}

