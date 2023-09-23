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
    return *char_count;
}

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

int eprint_int(int num)
{
    int count = 0;
    eprint_integers(&count, num);
    return (count);
}


int eprint_percent(int *char_count)
{
    eprint_char(char_count, '%');
    return (1);
}


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
            eprint_char(char_count, (char)va_arg(args, int));
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

