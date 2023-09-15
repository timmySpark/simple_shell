#include "shell.h"

/**
 * main -  check if file is connected to terminal
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	if (isatty(STDIN_FILENO) == 1)
	{
		interactive(envp);
	}
	else
	{
		non_interactive();
	}
	return (0);
}

/**
 * print_environment - prints env variables
 */
void print_environment(char **envp)
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		printf("%s\n", envp[i]);
	}
}
/**
 * interactive - functions used when shell is waiting for user input
 *
 */

void interactive(char **envp)
{
	char *line;
	char **args;

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
		if (args[0] != NULL && strcmp(args[0], "env") == 0)
		{
			print_environment(envp);
		}
		else
		{
			execute_args(args);
		}
		if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		{
			if (args[1] != NULL)
			{
				int status = atoi(args[1]);
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
		
		execute_args(args);

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
