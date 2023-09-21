#include "shell.h"

/**
 * is_delim - check if char is a delim
 * @str: string to be checked for delimeters
 * @delim: delimeter
 * Return: if str is delim - 1
 */

char is_delim(char str, char *delim)
{
	while (*delim)
	{
		if (str == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _strlen - a function that returns the length of a string
 * @str: character input str
 * Return: The length of str
 */

size_t _strlen(const char *str)
{
	size_t length = 0;

	while (*str++)
		length++;

	return (length);
}


/**
 * _strtok - tokenize a string
 * @str: string to be tokenized
 * @delim: delimeter used to tokenize a string
 * Return: a pointer to the first tokenized string
 */

char *_strtok(char *str, char *delim)
{
	static char *next_str;
	char *curr_str;

	if (!next_str)
		next_str = NULL;
	if (str == NULL)
		str = next_str;
	if (str == NULL)
		return (NULL);
	while (*str && is_delim(*str, delim))
		str++;
	if (*str == '\0')
	{
		next_str = NULL;
		return (NULL);
	}
	curr_str = str;
	while (*str && !is_delim(*str, delim))
		str++;

	if (*str)
	{
		*str = '\0';
		next_str = str++;
	}
	else
		next_str = NULL;

	return (curr_str);
}

/**
 * cd_command - handle cd builtin command
 * @args: arguments
 */

void cd_command(char **args)
{
	char *directory = args[1];
	char cwd[1024];

	if (!directory || strcmp(directory, "~") == 0)
		directory = getenv("HOME");
	else if (strcmp(directory, "-") == 0)
		directory = getenv("OLDPWD");
	if (chdir(directory) != 0)
	{
		perror("cd");
		return;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	else
		perror("getcwd");
}
