#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
#define MAX_INPUT_SIZE 100
#define MAX_ALIASES 10
#define MAX_VARIABLES 2
#define MAX_ARGS 100

typedef struct
{
        char name[MAX_INPUT_SIZE];
        char value[MAX_INPUT_SIZE];
} Alias;

Alias aliases[MAX_ALIASES];
int num_aliases = 0;

int main(void);
int count_words(char *sentence);
char *check_command(char *command);
char *get_command(char *command);
void execute_env(void);
int read_line(char *line);
void separate_command_args(char *input, char *command, char *args[]);
int split_input(char *input, char *command, char *args[]);
int execute_cd(char *args[]);
void execute_command(char *command, char *args[]);
void print_aliases(void);
int find_alias(const char *name);
void remove_comments(char *input);
int tmpmain(int argc, char *argv[]);
void file_command(char *command);


#endif /* MAIN_H */
