#include "shell.h"


/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string to concatenate.
 *
 * This function concatenates two strings.
 *
 * Return: Pointer to the concatenated string (dest).
 */


char *_strcat(char *dest, char *src)
{
	int i;
	size_t len;

	if (dest == NULL || src == NULL)
		return (NULL);

	len = _strlen(dest);

	for (i = 0; src[i] != '\0'; i++)
		dest[len++] = src[i];
	dest[len] = '\0';

	return (dest);
}

/**
 * _strtok - Tokenize a string based on specified delimiters.
 *
 * @str: The string to tokenize.
 * @delim:   A string containing the delimiter characters.
 *
 * This function tokenizes @str using the characters specified in
 * @delim as separators. It returns a pointer to the next token in the
 * string on each subsequent call, or NULL when there are no more tokens.
 *
 * Return: A pointer to the next token
 * or NULL if no more tokens are found.
 */

char *_strtok(char *str, char *delim)
{
	static char *next_token;
	char *token_start = NULL;
	int found_delim = 0;

	if (str != NULL)
		next_token = str;

	token_start = next_token;

	while (next_token && *next_token != '\0')
	{
		if (_strchr(delim, *next_token) != NULL)
		{
			*next_token = '\0';
			next_token++;
			found_delim = 1;
			break;
		}
		next_token++;
	}

	if (found_delim || *token_start != '\0')
		return (token_start);
	else
		return (NULL);
}

/**
 * _strcpy - Copy a source string to a destination buffer.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: On success, return a pointer to 'dest'. If an error occurs due to
 * invalid pointers or insufficient destination buffer size, it returns NULL.
 */

char *_strcpy(char *dest, char *src)
{
	size_t i;
	size_t len;

	if (!src)
		return (NULL);

	len = _strlen(src);

	for (i = 0; i < len; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

