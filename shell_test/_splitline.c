#include "shell.h"

#define TOKEN_DELIM " \t\r\n"


/**
 * allocate - allocate tokens
 * @bufsize: buffer size
 * @name: first argument in a terminal
 *
 * Return: tokens
 */

char **allocate(int bufsize, char *name)
{
	char **tokens;

	tokens = malloc(sizeof(char *) * bufsize);

	if (!tokens)
	{
		perror(name);
		exit(EXIT_FAILURE);
	}

	return (tokens);
}

/**
 * expand_tokens - expand tokens size
 * @tokens: tokens to be expanded
 * @bufsize: buffer size
 * @name: first argument inputed in the terminal
 *
 * Return: tokens
 */

char **expand_tokens(char **tokens, int *bufsize, char *name)
{
	*bufsize += BUFFER_SIZE;
	tokens = realloc(tokens, sizeof(char) * (*bufsize));

	if (!tokens)
	{
		perror(name);
		exit(EXIT_FAILURE);
	}

	return (tokens);
}

/**
 * tokenize - tokenize a line
 * @line: line to be tokenized
 * @tokens: tokens lines is split to
 * @name: first argument in the terminal
 *
 * Return: tokens
 */

char **tokenize(char *line, char **tokens, char *name)
{
	int i = 0, bufsize = BUFFER_SIZE;
	char *str;

	str = _strtok(line, TOKEN_DELIM);

	while (str != NULL)
	{
		if (str[0] == '#')
			break;

		tokens[i] = str;
		i++;

		if (i >= bufsize)
			tokens = expand_tokens(tokens, &bufsize, name);
		str = _strtok(NULL, TOKEN_DELIM);
	}

	tokens[i] = NULL;
	return (tokens);
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
	char **tokens = allocate(BUFFER_SIZE, name);

	return (tokenize(line, tokens, name));
}
