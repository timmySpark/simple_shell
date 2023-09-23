#ifndef SPECIAL_H
#define SPECIAL_H
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


/* ====================== SPECIAL FUNCTIONS ======================== */

cmd_t *init_cmd_t();

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
char *read_file(char *input_file, char *argv_0, cmd_t *cmmds, cmd_t *args);
char *replace_char(char *str, char c, char s);
char *rmv_double(char *cmd, char c);

#endif

