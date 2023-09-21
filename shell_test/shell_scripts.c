#include "shell.h"

/**
 * interactive - shell is waiting for user input
 * @envp: environment
 * @name: first arg on terminal
 *
 */

void interactive(char **envp, char *name)
{
	char *line;
	char **args;
	int result, status;

	while (1)
	{
		printf("#shell:) ");
		fflush(stdout);

		line = read_line(name);

		if (!line)
			continue;

		args = split_line(line, name);

		if (args[0] == NULL)
		{
			be_free(line, args);
			continue;
		}
		execute_args(args, name);
		be_free(line, args);
	}
}

/**
 * non_interactive - functions used when shell is processing automated commands
 * @name: first arg on terminal
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
		be_free(line, args);
	}
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
 * be_free -  free line and args of memory
 * @line: line to be freed
 * @args: arguments to be freed
 */

void be_free(char *line, char **args)
{
	free(line);
	free(args);
}
