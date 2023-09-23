#include "shell.h"

/**
 * interactive_shell - this is the part of the shell you interact with
 * @envp: environment path (where programs are)
 * @name: name of the program
 */
void interactive_shell(char **envp, char *name)
{
	char *line;
	char **args;

	while (1)
	{
		printf("shellO:) ");
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
			free(line);
			free(args);
		}

		handle_special_commands(args, envp, name);
		free(line);
		free(args);
	}
}
/**
 * not_interactive_shell - this shell doesn't interact
 * @name: Name of the program
 */
void not_interactive_shell(char *name)
{
	char *line;
	char **args;

	while (!feof(stdin))
	{
		line = read_line(name);

		if (!line)
			break;

		args = split_line(line, name);

		if (args && args[0])
		{
			run_command(args, name);
		}

		free(line);
		free(args);
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
		run_command(args, name);
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

