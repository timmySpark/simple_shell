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
int execute_logical_operator(char **args, char **envp, int logical_operator)
{
	int operator_index = -1;
	int i;
	char **cmd1;
	char **cmd2;
	int cmd1_status;

	(void)envp;
	for (i = 0; args[i] != NULL; i++)
	{
		if ((strcmp(args[i], "&&") == 0 || strcmp(args[i], "||") == 0))
		{
			operator_index = i;
			break;
		}
	}

	if (operator_index == -1)
	{
		execute_args(args);
		return (0);
	}

	cmd1 = args;
	cmd2 = args + operator_index + 1;
	args[operator_index] = NULL;

	execute_args(cmd1);

	wait(&cmd1_status);

	if ((logical_operator == 1 && cmd1_status == 0) || (logical_operator == 2 && cmd1_status != 0))
	{
		execute_args(cmd2);
		return (0);
	}

	return (1); 
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
		else if(args[0] != NULL && (strcmp(args[0], "&&") == 0 || strcmp(args[0], "||") == 0))
		{
			fprintf(stderr, "Syntax error: Logical operator without a preceeding command. \n");
		}
		else
		{
			int result = execute_logical_operator(args, envp, 1);
			if (result != 0)
			{
				execute_logical_operator(args, envp, 2);
			}
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
