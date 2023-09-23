#include "shell.h"

/**
 * _printf - Custom printf for error messages.
 * @format: The format string containing the specifiers.
 *
 * This custom printf function handles char, char * and int types.
 * It prints messages to the error stream.
 *
 * Return: Number of characters printed.
 */

int _printf(const char *format, ...)
{
    va_list args;
    int char_count = 0;
    const char *f = format;

    va_start(args, format);
    phandle_format(f, args, &char_count);
    va_end(args);
    return (char_count);
}

