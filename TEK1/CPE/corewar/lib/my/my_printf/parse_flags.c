/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** parse_flags
*/

#include "../my.h"

static int my_isnum(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

static int get_num(char const *format, int *i, int num)
{
    while (my_isnum(format[*i])) {
        num = num * 10 + (format[*i] - '0');
        *i += 1;
    }
    return num;
}

int parse_width(char const *format, int *i, va_list args)
{
    int width = 0;

    if (format[*i] == '*') {
        width = va_arg(args, int);
        *i += 1;
    } else {
        width = get_num(format, i, width);
    }
    return width;
}

int parse_precision(char const *format, int *i, va_list args)
{
    int precision = -1;

    if (format[*i] == '.') {
        *i += 1;
        if (format[*i] == '*') {
            precision = va_arg(args, int);
            *i += 1;
        } else {
            precision = 0;
            precision = get_num(format, i, precision);
        }
    }
    return precision;
}

void parse_format(char const *format, int *i, format_t *spec, va_list args)
{
    spec->width = parse_width(format, i, args);
    spec->precision = parse_precision(format, i, args);
}
