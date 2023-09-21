#include "shell.h"

/**
 * execute_logical_operator - runs a logical operator flar
 * Return: An int
 */

int execute_logical_operator(char **args, char **envp, int logical_operator)
{
	int status = 0;
	int i;
	int cmd_status;
	int cmd_count = 0;
	int cmd_index = 0;
	char ***commands;

	(void)envp;
	while (args[i] != NULL)
	{
		if (strcmp(args[i], "&&") == 0 || strcmp(args[i], "||") == 0)
		{
			cmd_count++;
		}
		i++;
	}

	commands = malloc((cmd_count + 1) * sizeof(char **));
	if (commands == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	cmd_index = 0;
	commands[cmd_index] = args;

	for (i = 0; i <= cmd_count; i++)
	{
		if (strcmp(args[i], "&&") == 0 || strcmp(args[i], "||") == 0)
		{
			args[i] = NULL;
			cmd_index++;
			commands[cmd_index] = &args[i + 1];
		}
	}

	for (i = 0; args[i] != NULL; i++)
	{
		if ((logical_operator == 1 && status == 0) ||
				(logical_operator == 2 && status != 0))
		{
			execute_args(commands[i]);
			wait(&cmd_status);
			if (WIFEXITED(cmd_status))
			{
				status = WEXITSTATUS(cmd_status);
			}
		}
		else
		{
			break;
		}
	}

	free(commands);
	return (status);

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
