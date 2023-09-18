#include "shell.h"

/**
 * interactive - shell is waiting for user input
 *
 */

void interactive(char **envp)
{
	char *line;
	char **args;
	int result, status;

	while (1)
	{
		printf("#shell:) ");

		line = read_line();

		if (!line)
		{
			free(line);
			continue;
		}
		args = split_line(line);
		if (args[0] != NULL && strcmp(args[0], "setenv") == 0)
			_setenv(args);
		else if (args[0] != NULL && strcmp(args[0], "unsetenv") == 0)
			_unsetenv(args);
		else if (args[0] != NULL && strcmp(args[0], "env") == 0)
			print_environment(envp);
		else if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		{
			if (args[1] != NULL)
			{
				status = atoi(args[1]);
				free(line);
				free(args);
				exit(status);
			}
			else
			{
				free(line);
				free(args);
				exit(EXIT_SUCCESS);
			}
		}
		else if (args[0] != NULL && (strcmp(args[0], "&&") == 0 ||
					strcmp(args[0], "||") == 0))
		{
			fprintf(stderr, "Syntax error: Logical operator without a preceeding command. \n");
		}
		else
		{
			result = execute_logical_operator(args, envp, 1);
			if (result != 0)
				execute_logical_operator(args, envp, 2);
		}
		free(line);
		free(args);
	}
}

/**
 * non_interactive - functions used when shell is processing automated commands
 *
 */

void non_interactive(void)
{
	char *line;
	char **args;

	while (!feof(stdin))
	{
		line = read_line();

		if (!line)
		{
			free(line);
			continue;
		}

		args = split_line(line);
		execute_args(args);

		free(line);
		free(args);
	}
}
