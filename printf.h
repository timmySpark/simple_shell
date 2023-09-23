#ifndef PRINTF_H
#define PRINTF_H


/* ======================= PRINTF FUNCTIONS ======================== */

int _printf(const char *format, ...);
int _print_char(int *char_count, char c);
int _print_strings(int *char_count, const char *str);
int _print_integers(int *char_count, int num);
int _print_percent(int *char_count);
int _print_int(int num);
int _print_str(char *str);
void phandle_format(const char *f, va_list args, int *char_count);

#endif
