#include "shell.h"

/**
 * interactive - shell is waiting for user input
 *
 */

void interactive(char **envp, char *name)
{
	char *line;
	char **args;

	while (1)
	{
		printf("#shell:) ");
		fflush(stdout);

		line = read_line(name);

		if (!line)
		{
			free(line);
			continue;
		}

		args = split_line(line, name);

		if (args[0] == NULL)
		{
			_free(line, args);
			continue;
		}

		handle_special_commands(args, envp, name);
		_free(line, args);
	}
}

/**
 * non_interactive - functions used when shell is processing automated commands
 *
 */

void non_interactive(char *name)
{
	char *line;
	char **args;

	while (!feof(stdin))
	{
		line = read_line(name);

		if (!line)
		{
			free(line);
			continue;
		}

		args = split_line(line, name);
		execute_args(args, name);
		_free(line, args);
	}
}
/**
 * handle_special_commands- handle commands to  navigate in shell
 * @args: arguments
 * @envp: environment
 * @name: first argment in the terminal
 */

void handle_special_commands(char **args, char **envp, char *name)
{
	if (args[0] != NULL && strcmp(args[0], "setenv") == 0)
		_setenv(args);
	else if (args[0] != NULL && strcmp(args[0], "unsetenv") == 0)
		_unsetenv(args);
	else if (args[0] != NULL && strcmp(args[0], "env") == 0)
		print_environment(envp);
	else if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		handle_exit(args);
	else if (strcmp(args[0], "cd") == 0)
		cd_command(args);
	else
		execute_args(args, name);
}

/**
 * handle_exit - handle exiting from shell
 * @args: arguments
 */

void handle_exit(char **args)
{
	int status = EXIT_SUCCESS;

	if (args[1] != NULL)
		status = atoi(args[1]);
	exit(status);
}

/**
 * _free -  free line and args of memory
 * @line: line to be freed
 * @arguments: arguments to be freed
 */

void _free(char *line, char **args)
{
	free(line);
	free(args);
}
