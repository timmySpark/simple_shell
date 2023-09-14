#include "shell.h"

#define BUFFER_SIZE 1024

int execute_arguments(char **args, char **envp)
{
	pid_t pid;
	int status;

	char *command_path = find_command(args[0], envp);
	if (command_path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		return (-1);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execve(command_path, args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else
		{
			fprintf(stderr, "Child Process did not exit normally\n");
			return (-1);
		}
	}
	else
	{
		perror("fork");
		return (-1);
	}
}
char *find_command(const char *command, char **envp)
{
	char *path = getenv("PATH");
	char *token, *saveptr;
	
	(void)envp;
	token = strtok_r(path, ":", &saveptr);
	printf("%s", token);

	while (token != NULL)
	{
		char *full_path = malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free(full_path);
			exit(EXIT_FAILURE);
		}

		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}

		free (full_path);
		token = strtok_r(NULL, ":", &saveptr);

	}

	return (NULL);
}
