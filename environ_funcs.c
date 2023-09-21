#include "shell.h"

/**
 * _set_env - set environment variable
 * @args: Arguments
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
 * _unsetenv - unsets an environment variable
 * @args: arguments
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
 * @envp: environment
 */

void print_environment(char **envp)
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		printf("%s\n", envp[i]);
	}
}
