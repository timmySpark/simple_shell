#include "shell.h"

/**
 * substitute_var - substitute variable if token is $
 * @token: token
 * Return: The token substituted
 */

char *substitute_var(char *token)
{
	if (token[0] == '$')
	{
		char *value = getenv(token + 1);

		if (value)
			return (value);
	}

	return (token);
}

/**
 * read_line - read lines
 */

char *read_line(char *name)
{
	char *line = NULL;
	size_t buf = 0;

	if (getline(&line, &buf, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(line);
			perror(name);
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 * execute_args - execute the arguments using execve
 * @args: arguments to be executed
 * @name: name of the first argument
 */

void execute_args(char **args, char *name)
{
	pid_t pid;
	int i, status;
	char *command_path;

	extern char **environ;
	for (i = 0; args[i]; i++)
		args[i] = substitute_var(args[i]);
	command_path = find_command(args[0]);
	printf("%s", command_path);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: Command not found: %s\n", name, args[0]);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		printf("Attempting to execute %s\n", command_path);
		if (execve(command_path, args, environ) == -1)
		{
			perror(name);
			free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror(name);
		free(command_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		do
			waitpid(pid, &status, WUNTRACED);
		while
			(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(command_path);
}

/**
 * find_command - find command
 * @command: command to be found
 */

char *find_command(const char *command)
{
	char *path_orig = getenv("PATH");
	char *path = strdup(path_orig);
	char *token, *full_path;

	printf("path_orig: %s\n", path_orig);
	printf("path: %s\n", path);


	if (!path_orig)
	{
		free(path);
		return (NULL);
	}

	if (!path)
		return (NULL);
	if (command[0] == '/')
	{
		return(strdup(command));
	}

	token = strtok(path, ":");
	printf("tokens(1): %s\n", token);
	full_path = malloc(_strlen(token) + _strlen(command) + 2);

	while (token != NULL)
	{
		printf("full path: %s", full_path);
		if (full_path == NULL)
		{
			perror("malloc");
			free(full_path);
			return (NULL);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);
		printf("full path: %s\n", full_path);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
		printf("token(2): %s\n", token);
	}
	free(path);
	return (NULL);
}
