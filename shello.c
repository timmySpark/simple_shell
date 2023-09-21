#include "shell.h"
/**
 * main - main function
 * @argc: arguement count
 * @argv: arguements
 * @envp: environment variable
 *
 * Return: an int
 */
int  main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	if (isatty(STDIN_FILENO) == 1)
	{
		interactive_shell(envp, argv[0]);
	}
	else
	{
		not_interactive_shell(argv[0]);
	}
	return (0);
}

