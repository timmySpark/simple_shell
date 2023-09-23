#include "shell.h"

/**
 * countSlashes - Counts forward slashes in a string.
 * @str: Input string.
 *
 * Useful for checking if a command was passed using its 
 * absolute path, e.g., "/bin/ls" instead of "ls."
 *
 * Return: Number of forward slashes.
 */

int countSlashes(char *str)
{
	int i, len, slashes = 0;

	len = _strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '/')
			slashes++;
	}
	return (slashes);
}

/**
 * checkAbsPath - Checks if an absolute path passed exists.
 * @str: Given command.
 *
 * Return: Absolute path if it exists, NULL otherwise.
 */

char *checkAbsPath(char *str)
{
	char *cmd;

	cmd = _strdup(str);
	if (!cmd)
	{
		perror("checkAbsPath");
		return (NULL);
	}
	if (access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

/**
 * extractCmd - Gets command from its absolute path.
 * @str: Absolute path of command.
 *
 * Return: Command, or NULL on failure.
 */

char *extractCmd(char *str)
{
	int i, j = 0, lastSlash = 0, len;
	char *cmd;

	len = _strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '/')
			lastSlash = i;
	}
	cmd = malloc(len - lastSlash);
	if (!cmd)
	{
		perror("extractCmd");
		return (NULL);
	}
	for (i = lastSlash; i < len; i++)
		cmd[j++] = str[i];
	cmd[j] = '\0';
	return (cmd);
}

/**
 * _realloc - Reallocates memory as necessary.
 * @lineptr: Double pointer to line storage array.
 * @n: Size of memory to allocate.
 * @bytesRead: Total bytes read into lineptr.
 *
 * Return: lineptr with updated memory, or NULL on failure.
 */

char *_realloc(char **lineptr, int n, ssize_t bytesRead)
{
	ssize_t i;
	char *tmp;

	tmp = (char *)malloc(n);
	if (!tmp)
		return (NULL);
	for (i = 0; i < bytesRead; i++)
		tmp[i] = (*lineptr)[i];
	free(*lineptr);
	*lineptr = tmp;
	return (*lineptr);
}

