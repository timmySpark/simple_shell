#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>
#include <limits.h>

#define BUFFER_SIZE 1024

extern char **environ;

/* Shell Prototypes */

void interactive(char **envp, char *name);
void non_interactive(char *name);

/* Core Shell Functionality */
char *read_line(char *name);
char **split_line(char *line, char *name);
void execute_args(char **args, char *name);
char *find_command(const char *command);

/* Custom Functions */
char is_delim(char str, char *delim);
char *_strtok(char *str, char *delim);
char *substitute_var(char *token);
char **allocate(int bufsize, char *name);
char **expand_tokens(char **tokens, int *bufsize, char *name);
char **tokenize(char *line, char **tokens, char *name);

size_t _strlen(const char *str);
size_t allocate_buffer(char **line_ptr, size_t *n);
size_t reallocate(char **line_ptr, size_t *n, int char_count);
ssize_t read_fd(int fd, char *buffer, int *chars_left);
ssize_t _getline(char **line_ptr, size_t *n, FILE *stream);
void cd_command(char **args);
void be_free(char *line, char **args);
void handle_exit(char **args);
void handle_special_commands(char **args, char **envp, char *name);


/* utility functionalities*/
void _setenv(char **args);
void _unsetenv(char **args);
void print_environment(char **envp);
int execute_logical_operator(char **args, char **envp, int logical_operator);

#endif
