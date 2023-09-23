#ifndef EPRINTF_H
#define EPRINTF_H

#include <unistd.h>
#include <stdarg.h>

int e_printf(const char *format, ...);
int eprint_char(int *char_count, char c);
int eprint_string(int *char_count, const char *str);
int eprint_integer(int *char_count, int num);
int eprint_percent(int *char_count);
int eprint_int(int num);
int eprint_str(char *str);
void econdition(const char *p, va_list args, int *char_count);

#endif 

