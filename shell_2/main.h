#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024
#define MAX_ARGS 128

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

/**
 * struct Buffer - Holds information for buffer used with _getline.
 * @data: Buffer.
 * @index: Current position in buffer
 * @count: Number of bytes read
 */
struct Buffer
{
    char data[BUFFER_SIZE];
    ssize_t index;
    ssize_t count;
};

typedef struct Buffer buff_t;

/**
 * struct Commands - Holds information about strings containing commands
 * @args: Arguments
 * @arg_count: Number of arguments
 * @piped: Tells if command as was passed at terminal or not.
 * If terminal, piped is false.
 * @foundPath: True if path to command was found.
 * @n_var_count: Index of new environment variable array
 * @new_vars: Array holding new environment variables.
 * @called_setenv: True if _setenv has been called, to enable freeing new_vars
 */
typedef struct Commands
{
    char *args[MAX_ARGS];
    int arg_count;
    bool piped;
    bool foundPath;
    int n_var_count;
    char *new_vars[1024];
    bool called_setenv;
} cmd_t;

/**
 * struct Scases - Handles special commands
 * @name: Name of command
 * @func: Function pointer to function related to @name
 */
typedef struct Scases
{
    char *name;
    bool (*func)(cmd_t *, cmd_t *, int, int, char *);
} sCases_t;

ssize_t _getline(char **lineptr, int *n, int fd, buff_t *buf);
char *_getenv(char *name);
int _strlen(char *c);
int _strncmp(char *s1, char *s2, int n);
char *_strchr(char *s, char c);
char *_strdup(char *s);
char *_strcat(char *dest, char *src);
char *_strtok(char *str, char *delim);
char *_strcpy(char *dest, char *src);
char *checkPath(char *cmd);
char *getPrompt();
void execute(cmd_t *args, cmd_t *cmmds, int cmd_count);
char **tokenize_cmd(char *cmd);
void cl_exec(char *cmd);
char *replace_char(char *str, char c, char s);
int exit_atoi(char *str);
void _ext(cmd_t *cmmds, cmd_t *args, int cCt, int idx, char *arg);
void free_args(char **args);
int count_slash(char *str);
char *abs_path(char *str);
ssize_t read_buffer(int fd, buff_t *buf);
char *_realloc(char **lineptr, int n, ssize_t tBytesRead);
cmd_t *init_cmd_t();
void looper(cmd_t *cmmds, cmd_t *args, char *argv_0, int *cmd_count);
char *read_file(char *input_file, char *argv_0, cmd_t *cmmds, cmd_t *args);
char *rmv_space(char *cmd);
char *rmv_double(char *cmd, char c);
int _setenv(char *variable, char *value, cmd_t *args);
int _unsetenv(char *variable);
bool sCases(cmd_t *cmmds, cmd_t *args, int cmd_count,
            int i, char *argv_0);
void copy_env(void);
void free_cmd_t(cmd_t *cmmd);
void cd(cmd_t *args, char *argv_0, int cmd_count);
char *free_strdup(char *s);
void cleanup(cmd_t *cmd);
int home(cmd_t *args);
int oldpwd(cmd_t *args);
void print_env();
bool cmd_setenv(cmd_t *args, cmd_t *cmmds, int cmd_count, int i, char *argv_0);
bool cmd_unsetenv(cmd_t *args, cmd_t *cmmds,
                  int cmd_count, int i, char *argv_0);
bool cmd_exit(cmd_t *args, cmd_t *cmmds,
              int cmd_count, int i, char *argv_0);
bool cmd_env(cmd_t *args, cmd_t *cmmds, int cmd_count,
             int i, char *argv_0);
int check_hash(char *cmd);

bool cmd_cd(cmd_t *args);


#endif /* MAIN_H */

