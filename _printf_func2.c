#include "shell.h"

/**
 * _print_percent - prubt percentage
 * @char_count: character count
 * Return: Int
 */

int _print_percent(int *char_count)
{
	_print_char(char_count, '%');
	return (1);
}

/**
 * phandle_format - handles format
 * @p: pointer p
 * @args: arguement
 * @char_count: character count
 */

void phandle_format(const char *p, va_list args, int *char_count)
{
	for (; *p != '\0'; p++)
	{
		if (*p != '%')
		{
			_print_char(char_count, *p);
			continue;
		}
		p++;
		switch (*p)
		{
			case 'c':
				_print_char(char_count, (char)va_arg(args, int));
				break;
			case 's':
				_print_str(va_arg(args, char *));
            			break;
			case 'i':
			case 'd':
				_print_int(va_arg(args, int));
				break;
			case '%':
				_print_percent(char_count);
				break;
			default:
				_print_char(char_count, *p);
				break;
		}
	}
}
