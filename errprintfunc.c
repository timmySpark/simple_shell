#include "shell.h"

/**
 * eprint_char - Prints a single character to STDERR.
 * @char_count: Counter for the number of characters printed.
 * @c: The character to print.
 * Return: Updated count of printed characters.
 */

int eprint_char(int *char_count, char c)
{
	write(STDERR_FILENO, &c, 1);
	(*char_count)++;
	return (*char_count);
}

/**
 * eprint_strings - Print strings to STDERR
 * @char_count: Counter for number of characters printed
 * @str: The string to be printed
 *
 * Return: length of the strings
 */

int eprint_strings(int *char_count, const char *str)
{
	int len = 0;

	while (str[len])
	{
		eprint_char(char_count, str[len]);
		len++;
	}

	return (len);
}

/**
 * eprint_integers - print integers to the STDERR
 * @char_count: Count for numbers to be printed
 * @num: number to be printed
 *
 * Return: integers to be printed
 */

int eprint_integers(int *char_count, int num)
{
	if (num < 0)
	{
		eprint_char(char_count, '-');
		num = -num;
	}

	if (num / 10)
		eprint_integers(char_count, num / 10);
	eprint_char(char_count, (num % 10) + '0');

	return (*char_count);
}

/**
 * eprint_str - Prints a string to STDERR.
 * @str: The string to print.
 * Return: Number of characters in the string.
 */

int eprint_str(char *str)
{
	int count = 0;

	eprint_strings(&count, str);
	return (count);
}

/**
 * eprint_int - prints an integer to the STDERR
 * @num: number to the printed
 *
 * Return: number of integers
 */

int eprint_int(int num)
{
	int count = 0;

	eprint_integers(&count, num);
	return (count);
}
