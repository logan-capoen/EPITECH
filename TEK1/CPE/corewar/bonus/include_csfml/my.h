/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday08-theophile.riffe
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdarg.h>
    #include <unistd.h>
    #include <limits.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <sys/stat.h>
    #include <sys/sysmacros.h>
    #include <time.h>

// Character/Output Functions
void my_putchar(char);
void my_putstr(char const *);
int my_put_nbr(int);
void my_puterr(char const *);

// String Length/Comparison Functions
int my_strlen(char const *);
int my_strcmp(char const *, char const *);
int my_strncmp(char const *, char const *, int n);
int my_isalnum(char);

// String Manipulation Functions
char *my_strcat(char *, char const *);
char *my_strncat(char *, char const *, int n);
char *my_strcpy(char *, char const *);
char *my_strncpy(char *, char const *, int n);
char *my_revstr(char *);
char *my_strstr(char *, char const *);
char *my_strdup(char const *);

// String Case Functions
char *my_strcapitalize(char *);
char *my_strlowcase(char *);
char *my_strupcase(char *);

// String Property Functions
int my_str_isalpha(char const *);
int my_str_islower(char const *);
int my_str_isnum(char const *);
int my_str_isprintable(char const *);
int my_str_isupper(char const *);

// Number-related Functions
int my_getnbr(char const *);
int my_compute_power_rec(int, int);
int my_compute_square_root(int);
int my_find_prime_sup(int);
int my_is_prime(int);
int my_isneg(int);

// Array/Sorting Functions
void my_sort_int_array(int *, int);
void my_swap(int *, int *);

// Miscellaneous Functions
int my_showmem(char const *, int);
int my_showstr(char const *);

// Double array Functions
char **split_string(char const *, char const *);
int my_show_word_array(char *const *);
char **my_str_to_word_array(char const *str, char spliter);

/* PRINTF */

typedef struct buffer_s {
    char buffer[1024];
    int pos;
    int len;
} buffer_t;

typedef struct format_s {
    int flags;
    int width;
    int precision;
    int length;
} format_t;

typedef struct printf_s {
    char c;
    void (*func)(va_list, buffer_t *, format_t *);
} printf_t;

void put_buffer(buffer_t *buff, int fd);
int my_printf(char const *format, ...);
void manage_specifiers(char c, va_list args, buffer_t *buff, format_t *spec);

void printf_putchar(char c, buffer_t *buff);
void printf_putstr(char const *str, buffer_t *buff, format_t *flags);
int printf_putnbr(int n, buffer_t *buff, format_t *flags);
int my_printf(char const *format, ...);
char *convert_hex(int long);
char *convert_oct(int long);
void printf_putfloat(double, buffer_t *, format_t *);
char *printf_pointer(void *adress);
void printf_scientific(double nb, buffer_t *global, format_t *flags, int up);
int number_len(int n);
void printf_n_spec(int *n, buffer_t *buff);
void printf_decimal(int nbr, buffer_t *buff, format_t *flags);
void printf_g_spec(double nb, buffer_t *buffer, format_t *flags, int up);
void printf_tab(char **tab, buffer_t *buff);

void print_char(va_list, buffer_t *, format_t *);
void print_string(va_list, buffer_t *, format_t *);
void print_int(va_list, buffer_t *, format_t *);
void print_mudulo(va_list, buffer_t *, format_t *);
void print_float(va_list, buffer_t *, format_t *);
void print_pointer(va_list args, buffer_t *buff, format_t *spec);
void print_puthexmin(va_list args, buffer_t *buff, format_t *spec);
void print_puthexmaj(va_list args, buffer_t *buff, format_t *spec);
void print_octal(va_list args, buffer_t *buff, format_t *spec);
void print_scientific(va_list args, buffer_t *buff, format_t *spec);
void print_capscientific(va_list args, buffer_t *buff, format_t *spec);
void print_nspec(va_list args, buffer_t *buff, format_t *spec);
void parse_format(char const *, int *, format_t *, va_list);
void print_decimal(va_list args, buffer_t *buff, format_t *spec);
void print_g_low(va_list args, buffer_t *buff, format_t *spec);
void print_g_up(va_list args, buffer_t *buff, format_t *spec);

#endif /* !MY_H_ */
