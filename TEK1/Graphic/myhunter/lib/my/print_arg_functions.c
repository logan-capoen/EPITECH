/*
** EPITECH PROJECT, 2024
** print_arg_functions
** File description:
** functions for print_arg function
*/

#include "../../include/printf.h"
#include "../../include/struct_printf.h"
#include <stdlib.h>
#include "../../include/my.h"
#include <stdio.h>

char *flags(specifiers_t spec, char *buff_width)
{
    uint len = my_strlen(spec.flags);

    special_flags_case(&spec);
    sort_flags(&spec);
    for (int i = 0; i < len; i++) {
        buff_width = exe_ptr_on_fct(spec.flags[i], buff_width);
    }
    return buff_width;
}

char *width(specifiers_t spec, char *buff_precision)
{
    char *buffer;
    int len_precision = my_strlen(buff_precision);
    int index;

    if (spec.width < len_precision || spec.arg_type == '%')
        spec.width = len_precision;
    index = spec.width - len_precision;
    if (spec.width == -1)
        return buff_precision;
    buffer = malloc(sizeof(char) * (spec.width + 1));
    for (int i = 0; i < spec.width; i++)
        buffer[i] = ' ';
    for (int j = 0; j < len_precision; j++) {
        buffer[index] = buff_precision[j];
        index++;
    }
    buffer[spec.width] = '\0';
    return buffer;
}

char *arg_type(specifiers_t spec, va_list valist)
{
    for (int i = 0; arg_types_tab[i].letter != '\0'; i++) {
        if (arg_types_tab[i].letter == spec.arg_type) {
            return (*(arg_types_tab[i].function))(valist);
        }
    }
    return "'not handling for this arg type'";
}

static int precision_special_case(specifiers_t *spec, char *buff_arg_type)
{
    if (spec->arg_type == 'f' || spec->arg_type == 'F') {
        (*spec).precision += 1;
        for (int j = 0; buff_arg_type[j] != '.'; j++)
            (*spec).precision += 1;
        if (buff_arg_type[spec->precision] >= '5' &&
            buff_arg_type[spec->precision] != '\0')
            rounded(spec, buff_arg_type);
    }
    if (spec->arg_type != 's' && spec->arg_type != 'f' && spec->arg_type
        != 'F' && spec->precision < my_strlen(buff_arg_type)) {
        (*spec).precision = my_strlen(buff_arg_type);
    }
    return 0;
}

static char *add_zero(specifiers_t spec, char *buff_arg_type)
{
    if (spec.arg_type == 'i' || spec.arg_type == 'd' || spec.arg_type == 'o') {
            return handle_zero_i_d(spec, buff_arg_type);
    }
    if (spec.arg_type == 'f' || spec.arg_type == 'F') {
        return handle_zero_f(spec, buff_arg_type);
    }
    return buff_arg_type;
}

char *precision(specifiers_t spec, char *buff_arg_type)
{
    char *buffer_precision = malloc(sizeof(char) * (spec.precision + 1));

    if (spec.precision == -1)
        return buff_arg_type;
    precision_special_case(&spec, buff_arg_type);
    if (spec.precision > my_strlen(buff_arg_type))
        return add_zero(spec, buff_arg_type);
    for (int i = 0; i < spec.precision; i++)
        buffer_precision[i] = buff_arg_type[i];
    buffer_precision[spec.precision] = '\0';
    return buffer_precision;
}

static int replace_value(int i, char *buff, int *plus_one)
{
    if (buff[i] == '9' && *plus_one) {
        buff[i] = '0';
    } else if (*plus_one) {
        buff[i] += 1;
        *plus_one = 0;
    }
}

int rounded(specifiers_t *spec, char *buff_arg_type)
{
    int plus_one = 1;
    int i = spec->precision - 1;

    while (i >= 0) {
        if (buff_arg_type[i] == '.') {
            i--;
            continue;
        }
        replace_value(i, buff_arg_type, &plus_one);
        i--;
    }
    if (plus_one) {
        for (int j = spec->precision; j >= 0; j--) {
            buff_arg_type[j + 1] = buff_arg_type[j];
        }
        buff_arg_type[0] = '1';
        spec->precision += 1;
    }
    return 0;
}
