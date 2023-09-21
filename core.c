#include "shell.h"
#define TOKEN_DELIM " \t\r\n"

/**
 * read_line - read lines
 * @name:  first argument in terminal
 * Return: read line
 */

char *read_line(char *name)
{
	char *line = NULL;
	size_t buf = BUFFER_SIZE;

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
 * split_line - split line into tokens
 * @line: line to be split
 * @name: name of the first argument in the terminal
 *
 * Return: a pointer to the tokens
 */


char **split_line(char *line, char *name)
{
	int i = 0, bufsize = BUFFER_SIZE;
	char *str;
	char **tokens;

	tokens = malloc(sizeof(char *) * bufsize);

	if (!tokens)
	{
		perror("Error: \n");
		exit(EXIT_FAILURE);
	}

	str = _strtok(line, TOKEN_DELIM);

	while (str != NULL)
	{
		if (str[0] == '#')
			break;
		tokens[i] = str;
		i++;

		if (i >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			tokens = _realloc(tokens, sizeof(char *) * bufsize);

			if (!tokens)
			{
				perror(name);
				exit(EXIT_FAILURE);
			}
		}

		str = _strtok(NULL, TOKEN_DELIM);
	}

	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute_args - execute the arguments using execve
 * @args: arguments to be executed
 * @name: name of the first argument
 */

void execute_args(char **args, char *name)
{
	pid_t pid, wpid;
	int status;
	char *exvp[] = {NULL};

	pid =  fork();

	if (pid == 0)
	{
		if (execve(args[0], args, exvp) == -1)
		{
			perror(name);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Shell Failed");
		exit(EXIT_FAILURE);
	}

	else
	{
		while (1)
		{
			wpid = waitpid(pid, &status, 0);

			if (WIFEXITED(status) || WIFSIGNALED(status))
				break;
		}
	}
}
