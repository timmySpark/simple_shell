#include "shell.h"

/**
 *cl_exec - Checks if command exists and calls execve
 *@cmmds: Pointer to struct containing command information
 *@args: Pointer to struct of arrays containing command information
 *@cmd_count: Number of commands carried out
 *@arg: Name of shell program(Contained at argv[0])
 *Return: Nothing
 */
void cl_exec(cmd_t *cmmds, cmd_t *args, int cmd_count, char *arg)
{
	char *fullPath;

	if (countSlashes(args->args[0]))
		fullPath = checkAbsPath(args->args[0]);
	else
		fullPath = findPath(args->args[0]);
	if (fullPath == NULL)
	{
		args->foundPath = 0;
		e_printf("%s: %i: %s: not found\n", arg, cmd_count, args->args[0]);
		free_args(args->args, args->arg_count);
		free(fullPath);
	}
	else
	{
		args->foundPath = 1;
		free(args->args[0]);
		args->args[0] = fullPath;
		runCommand(args, cmmds, cmd_count);
	}
}

/**
 *rmv_space - Removes unnecessary character from input string
 *@cmd: Input string
 *
 *Return: Corrected string
 */
char *rmv_space(char *cmd)
{
	int i, j = 0;
	char *cmd_clean;
	int prev_space = (cmd[0] == ' ' || cmd[0] == '\t');

	cmd_clean = malloc(_strlen(cmd) + 1);

	for (i = 0; cmd[i] != '\0'; i++)
	{
		if (cmd[i] == ' ' || cmd[i] == '\t')
		{
			if (!prev_space)
				cmd_clean[j++] = cmd[i];
			prev_space = 1;
		}
		else
		{
			cmd_clean[j++] = cmd[i];
			prev_space = 0;
		}
	}
	cmd_clean[j] = '\0';
	free(cmd);
	cmd = cmd_clean;
	return (cmd);
}

/**
 *exit_atoi - A string-to-integer converter for exit condition
 *@str: String to convert
 *
 *
 *Return: Integer if successful, -1 if non-numeric character found in input
 */
int exit_atoi(char *str)
{
	int i, len = 0;
	int total = 0;

	len = _strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			total = (total << 1) + (total << 3);
			total += (str[i] - '0');
		}
		else
			return (-1);
	}
	return (total);
}

/**
 *_exits - Handles exit condition
 *@cmmds: Commands separated by ";".
 *@args: Current Array containing arguments being executed
 *@idx: Current index of args.
 *@cCt: Number of commands already passed to shell
 *@arg: Name of shell program, held at argv[0].
 *
 *Return: Nothing
 */
void _exits(cmd_t *cmmds, cmd_t *args, int cCt, int idx, char *arg)
{
	int exit_num;

	if (args->args[1] == NULL && args->foundPath == 1)
	{
		free_cmd(args);
		free(cmmds->args[idx]);
		free(cmmds);
		free(environ);
		exit(0);
	}
	else if (args->args[1] == NULL && args->foundPath == 0)
	{
		free_cmd(args);
		free(cmmds->args[idx]);
		free(cmmds);
		free(environ);
		exit(2);
	}

	exit_num = exit_atoi(args->args[1]);
	if (exit_num == -1)
	{
		e_printf("%s: %i: %s: Illegal number:", arg, cCt, args->args[0]);
		e_printf(" %s\n", args->args[1]);
		free_cmd(args);
		free(cmmds->args[idx]);
		free(cmmds);
		free(environ);
		exit(2);
	}
	else
	{
		free(cmmds->args[idx]);
		free_cmd(args);
		free(cmmds->args[idx]);
		free(cmmds);
		free(environ);
		exit(exit_num);
	}
}

