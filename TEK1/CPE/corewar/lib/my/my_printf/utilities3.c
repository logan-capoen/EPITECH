/*
** EPITECH PROJECT, 2024
** utilities
** File description:
** linker to function
*/

#include "../my.h"

void print_capscientific(va_list args, buffer_t *buff, format_t *spec)
{
    printf_scientific(va_arg(args, double), buff, spec, 1);
}

void print_scientific(va_list args, buffer_t *buff, format_t *spec)
{
    printf_scientific(va_arg(args, double), buff, spec, 0);
}

void print_decimal(va_list args, buffer_t *buff, format_t *spec)
{
    printf_decimal(va_arg(args, int), buff, spec);
}

void print_g_low(va_list args, buffer_t *buff, format_t *spec)
{
    printf_g_spec(va_arg(args, double), buff, spec, 0);
}

void print_g_up(va_list args, buffer_t *buff, format_t *spec)
{
    printf_g_spec(va_arg(args, double), buff, spec, 1);
}
