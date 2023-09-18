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
 * _strtok - tokenize a string
 * @str: string to be tokenized
 * @delim: delimeter used to tokenize a string
 * Return: a pointer to the first tokenized string
 */

char *_strtok(char *str, char *delim)
{
	static char *next_str;
	char *curr_str;

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
 * _getline - accepts string from the input stream as an input
 * @line_ptr: place of char array initial character
 * @n: size
 * @stream: stream from where file will be read
 * Return: char count
 */

ssize_t _getline(char **line_ptr, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE];
	static char *buf_ptr;
	static int chars_left;
	int char_count = 0;
	int fd = fileno(stream);

	chars_left = 0;
	if (!(*line_ptr))
	{
		*n = BUFFER_SIZE;
		*line_ptr = malloc(sizeof(char *) * *n);
		if (!(*line_ptr))
			return (-1);
	}
	while (1)
	{
		if (chars_left <= 0)
		{
			chars_left = read(fd, buffer, BUFFER_SIZE);
			buf_ptr = buffer;
			if (chars_left <= 0)
			{
				if (char_count == 0)
					return (-1);
				break;
			}
		}
		if (char_count + 1 > *n)
		{
			*n += BUFFER_SIZE;
			*line_ptr = realloc(*line_ptr, *n);
			if (!(*line_ptr))
				return (-1);
		}
		if (*buf_ptr == '\n')
		{
			(*line_ptr)[char_count++] = '\0';
			buf_ptr++;
			chars_left--;
			return (char_count);
		}
		(*line_ptr)[char_count++] = *buf_ptr++;
		chars_left--;
	}
	(*line_ptr)[char_count] = '\0';
	return (char_count);
}
