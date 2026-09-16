/*
** EPITECH PROJECT, 2024
** B-CPE-101-LIL-1-1-miniprintf-theophile.riffe
** File description:
** utilities
*/

#include "../my.h"

void print_char(va_list args, buffer_t *buff,
    __attribute__((unused))format_t *flags)
{
    printf_putchar(va_arg(args, int), buff);
}

void print_string(va_list args, buffer_t *buff, format_t *flags)
{
    printf_putstr(va_arg(args, char *), buff, flags);
}

void print_int(va_list args, buffer_t *buff, format_t *flags)
{
    printf_putnbr(va_arg(args, int), buff, flags);
}

void print_mudulo(__attribute__((unused))va_list args, buffer_t *buff,
    __attribute__((unused))format_t *flags)
{
    printf_putchar('%', buff);
}

void print_float(va_list args, buffer_t *buff, format_t *flags)
{
    printf_putfloat(va_arg(args, double), buff, flags);
}
