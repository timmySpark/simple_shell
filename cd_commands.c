#include "shell.h"

/**
 * cd - Change the current working directory.
 * @args: Pointer to the command arguments.
 * @argv_0: The name of the program.
 * @cmd_count: The command count.
 */
void cd(cmd_t *args, char *argv_0, int cmd_count)
{
	char *arg = args->args[1];
	char current_dir[10240];
	char *new_pwd;

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("cd");
		return;
	}
	if (arg == NULL || _strncmp(arg, "~", 1) == 0 ||
			_strncmp(arg, "$HOME", 5) == 0)
	{
		if (show_home(args) == -1)
			return;
	}
	else if (_strncmp(arg, "-", 1) == 0 || _strncmp(arg, "$OLDPWD", 7) == 0)
	{
		if (get_oldpwd(args) == -1)
			return;
	}
	else
	{
		if (chdir(arg) == -1)
		{
			e_printf("%s: %d: cd: can't cd to %s\n", argv_0, cmd_count, arg);
			return;
		}
	}
	new_pwd = getcwd(NULL, 0);
	_setenv("OLDPWD", current_dir, args);
	_setenv("PWD", new_pwd, args);
	free(new_pwd);
}

/**
 * show_home - Handles home command for cd
 * @args: args
 *
 * Return: Nothing
 */
int show_home(cmd_t *args)
{
	const char *home = _getenv("HOME");
	int cd;

	if (home == NULL)
		home = _getenv("PWD");
	cd = chdir(home);
	if (cd == -1)
	{
		perror("cd");
		args->foundPath = 0;
		return (-1);
	}
	args->foundPath = 1;
	return (0);
}

/**
 * get_oldpwd - Handles home command for cd
 * @args: args
 *
 * Return: Nothing
 */
int get_oldpwd(cmd_t *args)
{
	const char *oldpwd = _getenv("OLDPWD");
	int cd;

	if (oldpwd == NULL)
		oldpwd = _getenv("PWD");
	cd = chdir(oldpwd);
	if (cd == -1)
	{
		perror("cd");
		args->foundPath = 0;
		return (-1);
	}
	_printf("%s\n", oldpwd);
	args->foundPath = 1;
	return (0);
}


/**
 * clean - Frees necessary items
 * @cmmds: Cmmds
 * @args: Args
 *
 * Return: Nothing
 */
void clean(cmd_t *cmmds, cmd_t *args)
{
	if (args->foundPath == 0)
	{
		free_cmd(args);
		free(cmmds), free(environ);
		exit(127);
	}
	free_cmd(args);
	free(cmmds), free(environ);
}

