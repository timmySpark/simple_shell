#include "shell.h"

/**
 * _printf_char - Prints a single character to STDERR.
 * @char_count: Counter for the number of characters printed.
 * @c: The character to print.
 * Return: Updated count of printed characters.
 */
int _printf_char(int *char_count, char c)
{
	write(STDERR_FILENO, &c, 1);
	(*char_count)++;
	return (*char_count);
}

/**
 * _printf_strings - prints string
 * @char_count: character count
 *
 * Return: int
 */
int _printf_strings(int *char_count, const char *str)
{
	int len = 0;

	while (str[len])
	{
		_printf_char(char_count, str[len]);
		len++;
	}
	return (len);
}

/**
 * _printf_integers - prints an integer
 * @char_count: count of the character
 *
 * Return: int
 */
int _printf_integers(int *char_count, int num)
{
	if (num < 0)
	{
		_printf_char(char_count, '-');
		num = -num;
	}
	if (num / 10)
		_printf_integers(char_count, num / 10);
		_printf_char(char_count, (num % 10) + '0');
		return (*char_count);
}

/**
 * _printf_str - Prints a string to STDERR.
 * @str: The string to print.
 * Return: Number of characters in the string.
 */

int _printf_str(char *str)
{
	int count = 0;

	_printf_strings(&count, str);
	return (count);
}

/**
 * _printf_int - prints an integer
 * @num: Integer number
 * Return: int
 */
int _printf_int(int num)
{
	int count = 0;

	_printf_integers(&count, num);
	return (count);
}

