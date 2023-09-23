#include "eprintf.h"

int e_printf(const char *format, ...)
{
    va_list args;
    const char *p = format;
    int char_count = 0;

    va_start(args, format);
    econdition(p, args, &char_count);
    va_end(args);
    return (char_count);
}

