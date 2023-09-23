#include "eprintf.h"

/**
 * eprint_char - Prints a single character to STDERR
 * @char_count: Pointer to number of characters printed.
 * @c: Character to print.
 *
 * Return: Pointer to number of characters printed.
 */
int eprint_char(int *char_count, char c)
{
    write(STDERR_FILENO, &c, 1);
    (*char_count)++;
    return (*char_count);
}

/**
 * eprint_string - Prints a string to STDERR
 * @char_count: Pointer to number of characters printed.
 * @str: Input string.
 *
 * Return: Pointer to number of characters printed.
 */
int eprint_string(int *char_count, const char *str)
{
    int len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    write(STDERR_FILENO, str, len);
    (*char_count) += len;
    return (*char_count);
}

/**
 * eprint_integer - Print an integer to STDERR using %i or %d format
 * @char_count: Pointer to number of characters printed.
 * @num: The integer to be printed.
 *
 * Return: Pointer to number of characters printed.
 */
int eprint_integer(int *char_count, int num)
{
    char buffer[12];
    int len = 0;
    int abs_num, i;
    int num_digits = 0;

    if (num == 0)
    {
        buffer[len++] = '0';
    }
    else
    {
        if (num < 0)
        {
            buffer[len++] = '-';
            num = -num;
        }

        abs_num = num;

        while (abs_num > 0)
        {
            abs_num /= 10;
            num_digits++;
        }

        abs_num = num;
        for (i = num_digits - 1; i >= 0; i--)
        {
            buffer[len + i] = '0' + (abs_num % 10);
            abs_num /= 10;
        }

        len += num_digits;
    }

    write(STDERR_FILENO, buffer, len);
    (*char_count) += len;
    return (*char_count);
}

/**
 * eprint_percent - Prints a percentage sign to STDERR.
 * @char_count: Pointer to number of characters printed.
 *
 * Return: Pointer to number of characters printed.
 */
int eprint_percent(int *char_count)
{
    write(STDERR_FILENO, "%", 1);
    (*char_count)++;
    return (*char_count);
}

/**
 * econdition - Handles format specifier for eprintf
 * @p: Input format string.
 * @args: List of va_arg arguments.
 * @char_count: Pointer to number of characters printed.
 *
 * Return: Nothing.
 */
void econdition(const char *p, va_list args, int *char_count)
{
    while (*p != '\0')
    {
        if (*p == '%')
        {
            p++;
            switch (*p)
            {
                case 'c':
                {
                    *char_count += eprint_char(char_count, *p);
                    break;
                }
                case 's':
                {
                    char *s = va_arg(args, char *);
                    *char_count += eprint_string(char_count, s);
                    break;
                }
                case 'i':
                case 'd':
                {
                    int num = va_arg(args, int);
                    *char_count += eprint_integer(char_count, num);
                    break;
                }
                default:
                    *char_count += eprint_char(char_count, *p);
            }
        }
        else
            *char_count = eprint_char(char_count, *p);
        p++;
    }
}

