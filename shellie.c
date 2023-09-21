#include "shell.h"

/**
 * main -  check if file is connected to terminal
 * @argc: argument count
 * @argv: first arg on terminal
 * @envp: environment
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;

	if (isatty(STDIN_FILENO) == 1)
	{
		interactive(envp, argv[0]);
	}
	else
	{
		non_interactive(argv[0]);
	}
	return (0);
}
