#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

/* Shell Prototypes */

void interactive(char **envp);
void non_interactive(void);

/* Core Shell Functionality */
char *read_line(void);
char **split_line(char *line);
int execute_args(char **args);
char *find_command(const char *command);

/* utility functionalities */
void print_environment(char **envp);
int execute_logical_operator(char **args, char **envp, int logical_operator);

#endif
