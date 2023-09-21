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
 * cd_command - handle cd command
 * @args: args
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

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated
 * @new_size: bytes of the new memory block
 *
 * Return: If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block
 */

void *_realloc(void *ptr, unsigned int new_size)
{
	char *new_block;
	unsigned int copy_size;
	char *original;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_block = malloc(new_size);
	if (!new_block)
		return (NULL);

	copy_size = new_size;
	original = ptr;

	while (copy_size-- > 0)
		new_block[copy_size] = original[copy_size];
	free(ptr);
	return (new_block);
}

