#include "shell.h"
/**
 * _printf_percent - prubt percentage
 * @char_count: character count
 * Return: Int
 */
int _printf_percent(int *char_count)
{
	_printf_char(char_count, '%');
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
			_printf_char(char_count, *p);
			continue;
		}
		p++;
		switch (*p)
		{
			case 'c':
				_printf_char(char_count, (char)va_arg(args, int));
				break;
			case 's':
				_printf_str(va_arg(args, char *));
            			break;
			case 'i':
			case 'd':
				_printf_int(va_arg(args, int));
				break;
			case '%':
				_printf_percent(char_count);
				break;
			default:
				_printf_char(char_count, *p);
				break;
		}
	}
}
