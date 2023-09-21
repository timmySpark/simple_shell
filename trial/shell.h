#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n"

extern char **environ;


void interactive_shell(char **envp, char *name);
void not_interactive_shell(char *name);

char is_delim(char str, char *delim);
char *read_line(char *name);
char **split_line(char *line,  char *name);
char *_strtok(char *str, char *delim);
int _command(char **args, char *name);
char *find_command(const char *command);
void run_command(char **args, char *name);
void cd_command(char **args);

void _setenv(char **args);
void _unsetenv(char **args);
void print_environment(char **envp);


size_t _strlen(const char *str);
ssize_t _getline(char **line_ptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
#endif