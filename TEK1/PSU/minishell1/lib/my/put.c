/*
** EPITECH PROJECT, 2024
** put
** File description:
** take all put function
*/

#include "../../include/my.h"
#include "../../include/printf.h"


char *put_flags(char *format, int *i, char *flags)
{
    int len = flag_len(format);

    flags[len] = '\0';
    for (int j = 0; j < len; j++) {
        flags[j] = format[j];
        *i += 1;
    }
    return flags;
}

int put_width(char *format, int *i)
{
    int width = 0;

    if (format[0] >= '0' && format[0] <= '9') {
        width = my_getnbr(format);
        *i += my_len_int(width);
        return width;
    }
    return -1;
}

int put_precision(char *format, int *i)
{
    int precision = 0;

    if (format[0] == '.') {
        precision = my_getnbr(format + 1);
        *i += my_len_int(precision) + 1;
        if (precision == 0)
            return -1;
        return precision;
    }
    return -1;
}

char put_arg_type(char *format, int *i)
{
    *i += 1;
    return format[0];
}
