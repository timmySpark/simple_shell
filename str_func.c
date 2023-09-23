#include "shell.h"

/**
 * _strlen - find the length of a string
 * @s: String to be counted
 *
 * Return: length of the string
 */

int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (-1);
	while (s[len])
		len++;
	return (len);
}

/**
 * _strncmp - compare two strings
 * @s1: String one
 * @s2: String two
 * @n: maximum num of characters to compare
 *
 * Return: 0 if strings are the same
 */

int _strncmp(char *s1, char *s2, int n)
{
	int i;

	if (!s1 || !s2)
		return (-1);
	for (i = 0; i < n; i++)
		if (s1[i] != s2[i])
			return (1);
	return (0);
}

/**
 * _strchr - find first occurence of character
 * @s: input string
 * @c: character to search for
 *
 * Return: length of the string
 */

char *_strchr(char *s, char c)
{
	if (!s || !c)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);

}

/**
 * _strdup - duplicates a string
 * @s: String to be duplicated
 *
 * Return: pointer to the duplicate string
 */

char *_strdup(char *s)
{
	char *dup;
	int i, len;

	if (!s)
		return (NULL);
	len = _strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}

