#include "main.h"
#include "printf.h"

/**
 * print_char - Prints a single character
 * @char_count: Pointer to number of characters printed.
 * @c: Character to print.
 *
 * Return: Pointer to number of characters printed.
 */
int print_char(int *char_count, char c)
{
    write(STDOUT_FILENO, &c, 1);
    (*char_count)++;
    return (*char_count);
}

/**
 *print_str - Prints string
 *@str: Input string
 *
 *Return: Length of str
 */
int print_str(char *str)
{
    int i;
    int len = 0;

    for (i = 0; str[i] != '\0'; i++)
    {
        len++;
    }

    write(1, str, len);
    return (len);
}

/**
 * print_int - Print an integer using %i or %d format
 * @num: The integer to be printed
 *
 * Return: The number of characters printed
 */
int print_int(int num)
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

    write(1, buffer, len);

    return (len);
}

/**
 * print_percent - Prints percentage sign.
 * @char_count: Pointer to number of characters printed.
 *
 * Return: Pointer to number of characters printed.
 */
int print_percent(int *char_count)
{
    write(STDOUT_FILENO, "%", 1);
    (*char_count)++;
    return (*char_count);
}

/**
 * condition - Handles format specifier
 * @p: Input
 * @args: List of va_arg argument
 * @char_count: Pointer to number of characters printed.
 *
 * Return: Nothing.
 */
void condition(const char *p, va_list args, int *char_count)
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
                    *char_count += print_char(char_count, va_arg(args, int));
                    break;
                }
                case 's':
                {
                    char *s = va_arg(args, char *);
                    *char_count += print_str(s);
                    break;
                }
                case 'i':
                case 'd':
                {
                    int num = va_arg(args, int);
                    *char_count += print_int(num);
                    break;
                }
                default:
                    *char_count += print_char(char_count, *p);
            }
        }
        else
            *char_count = print_char(char_count, *p);
        p++;
    }
}

