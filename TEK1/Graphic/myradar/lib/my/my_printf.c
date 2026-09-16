/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** just a simple copy of printf
*/

#include "../../include/struct_printf.h"
#include "../../include/my.h"
#include <stdarg.h>
#include "../../include/printf.h"
#include <stdlib.h>

int my_printf(char *format, ...)
{
    int len = 0;
    va_list valist;

    va_start(valist, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%')
            print_arg(format + 1, valist, &i, &len);
        else {
            my_putchar(format[i]);
        }
    }
    return len;
}

int print_arg(char *format, va_list valist, int *i, int *len)
{
    specifiers_t spec = tab_spec(format, i);
    char *buff_arg_type = arg_type(spec, valist);
    char *buff_precision = precision(spec, buff_arg_type);
    char *buff_width = width(spec, buff_precision);
    char *buff_flag = flags(spec, buff_width);

    my_putstr(buff_flag);
    return 0;
}

specifiers_t tab_spec(char *format, int *i)
{
    specifiers_t spec;

    spec.flags = malloc(sizeof(char) * (flag_len(format) + 1));
    put_flags(format + *i, i, spec.flags);
    spec.width = put_width(format + *i, i);
    spec.precision = put_precision(format + *i, i);
    spec.arg_type = put_arg_type(format + *i, i);
    return spec;
}
