#include "shell.h"

#define BUFFER_SIZE 64
#define TOKEN_DELIM " \t\r\n"

/**
 * read_line - read lines
 */

char *read_line(void)
{
	char *line;
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
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}

	return (line);

}

/**
 * split_line - split line into tokens
 * @line: line to be split
 *
 * Return: a pointer to the tokens
 */

char **split_line(char *line)
{
	int i = 0, buf_size = BUFFER_SIZE;
	char *split_str;
	char **tokens;

	tokens = malloc(sizeof(char *) * buf_size);

	if (!tokens)
	{
		perror("./shell");
		exit(EXIT_FAILURE);
	}

	split_str = strtok(line, TOKEN_DELIM);

	while (split_str != NULL)
	{
		tokens[i] = split_str;
		i++;
		split_str = strtok(NULL, TOKEN_DELIM);

	}

	tokens[i] = NULL;
	return (tokens);

}

/**
 * execute_args - execute the arguments using execve
 * @args: arguments to be executed
 *
 */

void execute_args(char **args)
{
	pid_t pid, wpid;
	int status;
	
	(void) wpid;
	pid = fork();

	if (pid == 0)
	{
		char *encvp[] = {NULL};

		if (execve(args[0], args, encvp) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		wpid = waitpid(pid, &status, 0);

		while (1)
		{
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break;
		}
	}
	else
	{
		perror("./shell");
		exit(EXIT_FAILURE);
	}
}
