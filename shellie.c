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
