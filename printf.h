#ifndef PRINTF_H
#define PRINTF_H

/* Printf custom functons*/
int _printf(const char *format, ...);
int print_char(int *char_count, char c);
int print_strings(int *char_count, const char *str);
int print_integers(int *char_count, int num);
int print_percent(int *char_count);
int print_int(int num);
int print_str(char *str);
void phandle_format(const char *f,va_list args, int *char_count);

#endif

