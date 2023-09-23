#include "shell.h"

/**
 * _getline - Read a line from a file descriptor
 * and dynamically resize the buffer.
 * @buf_line: A pointer to where the line will be stored.
 * @buf_size: Size of the buffer.
 * @fd: The file descriptor from which to read the line.
 * @buff_info: Struct containing information about buffer.
 * Return: The number of characters read, or -1 on error.
 */

ssize_t _getline(char **buf_line, int *buf_size, int fd, buff_t *buff_info)
{
	char chr;
	ssize_t total_bytes = 0, buffer_result;

	if (!buf_line || !buf_size || !buff_info)
		return (-1);

	if (!(*buf_line) || *buf_size < 2)
	{
		*buf_size = 64;
		*buf_line = malloc(*buf_size);
		if (!(*buf_line))
			return (-1);
	}

	while (1)
	{
		if (total_bytes >= (*buf_size) - 2)
		{
			*buf_size *= 2;
			*buf_line = _realloc(buf_line, *buf_size, total_bytes);
		}
		buffer_result = buffer_read(fd, buff_info);
		if (buffer_result < 0)
			return (-1);
		else if (buffer_result == 0 && total_bytes == 0)
			return (0);
		else if (buffer_result == 0)
			break;

		chr = buff_info->data[buff_info->index++];
		(*buf_line)[total_bytes++] = chr;

		if (chr == '\n' && isatty(STDIN_FILENO) != 0)
			break;
	}
	(*buf_line)[total_bytes] = '\0';
	return (total_bytes);
}

/**
 * buffer_read - Stores read data in a buffer.
 * @fd: File descriptor.
 * @buff_info: Struct with buffer details.
 * Return: Number of bytes read.
 */


ssize_t buffer_read(int fd, buff_t *buff_info)
{
	if (buff_info->index >= buff_info->count)
	{
		buff_info->count = read(fd, buff_info->data, BUFFER_SIZE);
		if (buff_info->count <= 0)
			return (buff_info->count);
		buff_info->index = 0;
	}
	return (buff_info->count);
}

