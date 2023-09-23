#include "shell.h"

/**
 */

volatile sig_atomic_t child_pid = 0;

void sigint_handler(int signum)
{
	(void) signum;

	if (child_pid != 0)
		kill(child_pid, SIGINT);
	else
		write(STDOUT_FILENO, "\nshellO:) ", 10);
}
