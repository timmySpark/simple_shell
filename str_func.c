#include "shell.h"


int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (-1);
	while (s[len])
		len++;
	return (len);
}


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

