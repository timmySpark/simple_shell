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
 * execute_logical_operator - runs a logical operator flar
 * Return: An int
 */
void execute_logical_operator(char **args, char **envp)
{
	int i = 0;
	bool continue_execution = true;

	(void)envp;
	while (args[i] != NULL)
	{
		if (strcmp(args[i], "&&") == 0)
		{
			if (continue_execution)
			{
				execute_args(args);
			}
		i++;
		continue_execution = true;
		}
		else if (strcmp(args[i], "||") == 0)
		{
			args[i] = NULL;
			if (!continue_execution)
			{
				execute_args(args);
			}
			i++;
			continue_execution = true;
		}
		else 
		{
			i++;
		}
	}
	
	if (continue_execution)
	{
		execute_args(args);
	}
}
/**
 * _set_env - set environment variable
 *
 */
void _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUES\n");
		return;
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
	}
}
/**
 * _unsetenv - unsets an environment variavle
 *
 */
void _unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE VALUES\n");
		return;
	}
	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
	}
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
		if (args[0] != NULL && strcmp(args[0], "setenv") == 0)
		{
			_setenv(args);
		}
		else if (args[0] != NULL && strcmp(args[0], "unsetenv") == 0)
		{
			_unsetenv(args);
		}
		else if (args[0] != NULL && strcmp(args[0], "env") == 0)
		{
			print_environment(envp);
		}
		else if (args[0] != NULL && strcmp(args[0], "exit") == 0)
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
		else if (args[0] != NULL)
		{
			execute_logical_operator(args, envp);
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
