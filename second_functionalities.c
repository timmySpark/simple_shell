#include "shell.h"

#define BUFFER_SIZE 1024

int execute_args(char **args, **envp)
{
	pid_t pid;
	int status;

	char *command_path = find_command(args[0], envp);
	if (command_path == MULL)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		return (-1);
	}

	pid = fork();

	if (Pid == 0)
	{
		if (execve(command_path, args, envp) == -1)
		{
			perror("execve");
