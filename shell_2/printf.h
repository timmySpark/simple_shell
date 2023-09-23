#ifndef MY_PRINTF_UTILS_H
#define MY_PRINTF_UTILS_H

#include <unistd.h>
#include <stdarg.h>

int _printf(const char *format, ...);
int print_char(int *char_count, char c);
int print_string(int *char_count, const char *str);
int print_integer(int *char_count, int num);
int print_percent(int *char_count);
int print_int(int num);
int print_str(char *str);
void condition(const char *p, va_list args, int *char_count);

#endif /* MY_PRINTF_UTILS_H */

