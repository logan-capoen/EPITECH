/*
** EPITECH PROJECT, 2024
** utilities
** File description:
** linker to function
*/

#include "../my.h"

void print_puthexmin(va_list args, buffer_t *buff, format_t *spec)
{
    printf_putstr(convert_hex(va_arg(args, long)), buff, spec);
}

void print_puthexmaj(va_list args, buffer_t *buff, format_t *spec)
{
    printf_putstr(my_strupcase(convert_hex(va_arg(args, long))), buff, spec);
}

void print_octal(va_list args, buffer_t *buff, format_t *spec)
{
    printf_putstr(convert_oct(va_arg(args, long)), buff, spec);
}

void print_pointer(va_list args, buffer_t *buff, format_t *spec)
{
    printf_putstr(printf_pointer(va_arg(args, void *)), buff, spec);
}

void print_nspec(va_list args, buffer_t *buff,
    __attribute__((unused))format_t *spec)
{
    printf_n_spec(va_arg(args, int *), buff);
}
