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
			return strdup(value);
	}

	return strdup(token);
}


/**
 * read_line - read lines
 * @name: program name
 *
 * Return: read line
 */

char *read_line(char *name)
{
	char *line = NULL;
	size_t buf = 0;

	if (_getline(&line, &buf, stdin) == -1)
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
 * run_command - execute the arguments using execve
 * @args: arguments to be executed
 * @name: name of the first argument
 */

void run_command(char **args, char *name)
{
	pid_t pid;
	int status, i;
	char *cmd_path;

	for (i = 0; args[i]; i++)
		args[i] = substitute_var(args[i]);
	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", name, args[0]);
		return;
	}

	pid = fork();

	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(cmd_path, args, NULL) == -1)
		{
			fprintf(stderr, "%s: %s: Not a directory\n", name, args[0]);
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror(name);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		do
			waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(cmd_path);
}

/**
 * find_command - find command
 * @command: command to be found
 *
 * Return: path
 */

char *find_command(const char *command)
{
	char *path_orig, *path, *token, *full_path;

	if (command[0] == '/')
		return (strdup((command)));

	path_orig = getenv("PATH");
	if (!path_orig)
		return (NULL);

	path = strdup(path_orig);
	if (!path)
		return (NULL);

	token = _strtok(path, ":");
	while (token != NULL)
	{
		full_path = malloc(_strlen(token) + _strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free(path);
			return (NULL);
		}

		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		token = _strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
