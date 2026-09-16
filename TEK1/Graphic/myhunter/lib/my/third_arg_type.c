/*
** EPITECH PROJECT, 2024
** third_arg_type
** File description:
** third definition of arg type fonctions
*/

#include <stdarg.h>
#include <stdlib.h>
#include "../../include/my.h"
#include "../../include/printf.h"
#include <stdio.h>

static char *is_f_between_zero_and_one(long num_long, char *buff)
{
    int i = 0;

    buff = malloc(sizeof(char) * 9);
    for (; num_long > 0; i++) {
        if (i == 6) {
            buff[i] = '.';
            i++;
        }
        buff[i] = num_long % 10 + '0';
        num_long /= 10;
    }
    for (; i < 7; i++) {
        if (i == 6) {
            buff[i] = '.';
            i++;
        }
        buff[i] = '0';
    }
    return my_revstr(buff);
}

char *f_type(va_list valist)
{
    double num_float = va_arg(valist, double);
    long num_long = (long)(num_float * 1000000);
    char *buff;

    if (num_float < 1.0 && num_float >= 0.0)
        return is_f_between_zero_and_one(num_long, buff);
    buff = malloc(sizeof(char) * (my_len_int(num_long) + 2));
    if (num_long < 0) {
        num_long *= -1;
        buff[my_len_int(num_long) + 1] = '-';
    }
    for (int i = 0; num_long > 0; i++) {
        if (i == 6) {
            buff[i] = '.';
            i++;
        }
        buff[i] = num_long % 10 + '0';
        num_long /= 10;
    }
    return my_revstr(buff);
}

char *g_type(va_list valist)
{
    return 0;
}

char *g_uppercase_type(va_list valist)
{
    return 0;
}
