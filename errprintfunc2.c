#include "shell.h"

/**
 * eprint_percent - prints a percent to the STDERR
 * @char_count: number of characters printed
 *
 * Return: 1
 */

int eprint_percent(int *char_count)
{
	eprint_char(char_count, '%');
	return (1);
}

/**
 * handle_format - handle format for commands
 * @p: Input
 * @args: List to va_arg argument
 * @char_count: Pointer to number of characters printed
 */

void handle_format(const char *p, va_list args, int *char_count)
{
	for (; *p != '\0'; p++)
	{
		if (*p != '%')
		{
			eprint_char(char_count, *p);
			continue;
		}

		p++;

		switch (*p)
		{
			case 'c':
				eprint_char(char_count,
						(char)va_arg(args, int));
				break;

			case 's':
				eprint_str(va_arg(args, char *));
				break;
			case 'i':
			case 'd':
				eprint_int(va_arg(args, int));
				break;
			case '%':
				eprint_percent(char_count);
				break;
			default:
				eprint_char(char_count, *p);
				break;
		}
	}
}
