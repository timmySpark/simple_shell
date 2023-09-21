#include "shell.h"

/**
 * allocate_buffer - allocate buffer to n if line ptr is null
 * @line_ptr: pointer to the line
 * @n: size
 * Return: 0
 */

size_t allocate_buffer(char **line_ptr, size_t *n)
{
	if (!(*line_ptr))
	{
		*n = BUFFER_SIZE;
		*line_ptr = malloc(sizeof(char) * *n);

		if (!(*line_ptr))
			return (-1);
	}

	return (0);
}


/**
 * reallocate - reallocate buffer if the lengtht is greater than the size
 * @line_ptr: pointer to the string
 * @n: size of string
 * @char_count: length of string
 *
 * Return: 0
 */

size_t reallocate(char **line_ptr, size_t *n, int char_count)
{
	char *new_ptr;

	if ((size_t)char_count + 1 > *n)
	{
		*n += BUFFER_SIZE;
		new_ptr = realloc(*line_ptr, *n);

		if (!new_ptr)
			return (-1);

		*line_ptr = new_ptr;
	}
	return (0);
}

/**
 * read_fd - read from file descriptor
 * @fd: file descriptor
 * @buffer: buffer
 * @chars_left: characters remaining
 *
 * Return: 0
 */

ssize_t read_fd(int fd, char *buffer, int *chars_left)
{
	*chars_left = read(fd, buffer, BUFFER_SIZE);
	buffer[*chars_left] = '\0';

	if (*chars_left <= 0)
		return (-1);
	return (0);
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

	if (allocate_buffer(line_ptr, n) == -1)
		return (-1);
	while (1)
	{
		if (chars_left <= 0)
		{
			if (read_fd(fd, buffer, &chars_left) == -1)
			{
				if (char_count == 0)
					return (-1);
				break;
			}
			buf_ptr = buffer;
		}
		if (reallocate(line_ptr, n, char_count) == -1)
			return (-1);
		if (*buf_ptr == '\n' || *buf_ptr == '\0')
		{
			(*line_ptr)[char_count++] = '\0';
			if (*buf_ptr != '\0')
			{
				buf_ptr++;
				chars_left--;
			}
			return (char_count);
		}
		(*line_ptr)[char_count++] = *buf_ptr++;
		chars_left--;
	}
	(*line_ptr)[char_count] = '\0';
	return (char_count);
}
