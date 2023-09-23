#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024
#define MAX_ARGS 128

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include "printf.h"

extern char **environ;

/* ======================= STRUCT DEFINITIONS ======================== */

/**
 * struct Buffer - Details for _getline functions' buffer
 * @data: Holds buffer data
 * @index: Current position in buffer
 * @count: Number of bytes read
 */
typedef struct Buffer
{
	char data[BUFFER_SIZE];
	ssize_t index;
	ssize_t count;
} buff_t;

/**
 * struct Commands - Contains command-related data.
 * @args: Array holding command arguments
 * @arg_count: Total number of arguments
 * @pipe: Indicates whether the input came from a terminal or not
 * @foundPath: Status indicating if the command path was found
 * @var_count: Index of the new environment variables array
 * @new_vars: Array holding new environment variables
 * @called_setenv: Status indicating if _setenv was called or not
 */
typedef struct Commands
{
	char *args[MAX_ARGS];
	int arg_count;
	int pipe;
	int foundPath;
	int var_count;
	char *new_vars[1024];
	int called_setenv;
} cmd_t;

/**
 * struct cases - Manages special command cases
 * @name: Command name identifier
 * @func: Function pointer associated with the command
 */
typedef struct cases
{
	char *name;
	int (*func)(cmd_t *, cmd_t *, int, int, char *);
} scases_t;

/* ======================== STRING FUNCTIONS ======================== */

int _strlen(char *c);
int _strncmp(char *s1, char *s2, int n);
char *_strchr(char *s, char c);
char *_strdup(char *s);
char *_strcat(char *dest, char *src);
char *_strtok(char *str, char *delim);
char *_strcpy(char *dest, char *src);


/* ======================== EPRINT FUNCTIONS ======================= */

int e_printf(const char *format, ...);
int eprint_char(int *char_count, char c);
int eprint_strings(int *char_count, const char *str);
int eprint_integers(int *char_count, int num);
int eprint_percent(int *char_count);
int eprint_int(int num);
int eprint_str(char *str);
void handle_format(const char *f, va_list args, int *char_count);

/* ======================== PATH FUNCTIONS ========================= */

char *findPath(char *cmd);
int tokenize(char *cmd, char *argumentsArr[], char *separator);
int countSlashes(char *str);
char *checkAbsPath(char *str);
char *extractCmd(char *str);
char *_realloc(char **lineptr, int n, ssize_t bytesRead);
char *userInput(cmd_t *commands, cmd_t *arguments);
void runCommand(cmd_t *arguments, cmd_t *commands, int cmdCount);

/* ===================== ENVIRONMENT FUNCTIONS ===================== */

char *_getenv(char *name);
void print_env(void);
int _setenv(char *var, char *val, cmd_t *args);
int _unsetenv(char *var);
void copy_env(void);
void free_cmd(cmd_t *cmd);
void free_args(char *args[], int num_token);
char *userInput(cmd_t *commands, cmd_t *arguments);


/* ================== LINE MANIPULATION FUNCTIONS ================== */

ssize_t _getline(char **buf_line, int *buf_size, int fd, buff_t *buff_info);
ssize_t buffer_read(int fd, buff_t *buff_info);

/* ====================== SPECIAL FUNCTIONS ======================== */

int cases(cmd_t *cmmds, cmd_t *args, int cmd_count, int i, char *argv_0);
int _setenv_cmd(cmd_t *args, cmd_t *cmmds, int cmd_count, int i, char *argv_0);
int _unsetenv_cmd(cmd_t *args, cmd_t *cmmds, int cmd_count, int i, char *argv_0);
int _exit_cmd(cmd_t *args, cmd_t *cmmds, int cmd_count, int i, char *argv_0);
int _env_cmd(cmd_t *args, cmd_t *cmmds, int cmd_count, int i, char *argv_0);
int cd_cmd(cmd_t *args, cmd_t *cmmds, int cmd_count, int i, char *argv_0);
void cd(cmd_t *args, char *argv_0, int cmd_count);
int show_home(cmd_t *args);
int get_oldpwd(cmd_t *args);
void clean(cmd_t *cmmds, cmd_t *args);
char *check_hash(char *str);
void cl_exec(cmd_t *cmmds, cmd_t *args, int cmd_count, char *arg);
char *rmv_space(char *cmd);
int exit_atoi(char *str);
void _exits(cmd_t *cmmds, cmd_t *args, int cCt, int idx, char *arg);
void looper(cmd_t *cmmds, cmd_t *args, char *argv_0, int *cmd_count);
cmd_t *init_cmd_t();
char *read_file(char *input_file, char *argv_0, cmd_t *cmmds, cmd_t *args);
char *replace_char(char *str, char c, char s);
char *rmv_double(char *cmd, char c);

#endif

