#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

/* Shell Prototypes */

void interactive(void);
void non_interactive(void);

/* Core Shell Functionality */
char *read_line(void);
char **split_line(char *line);
void execute_args(char **args);
int execute_arguments(char **args, char **envp);
char *find_command(const char *command, char **envp);

#endif
