/*
** EPITECH PROJECT, 2024
** second_arg_type
** File description:
** second definition of arg type fonctions
*/

#include <stdarg.h>
#include "../../include/printf.h"
#include <stdlib.h>
#include "../../include/my.h"

char *x_type(va_list valist)
{
    unsigned int num = va_arg(valist, unsigned int);
    char *buffer = malloc(sizeof(char) * (my_len_int(num) + 1));
    unsigned int index = 0;

    for (index; num > 15; index++) {
        if (num % 16 > 9)
            buffer[index] = (num % 16) + 48 + 39;
        else
            buffer[index] = (num % 16) + 48;
        num = num / 16;
    }
    if (num > 9)
        buffer[index] = num + 48 + 39;
    else
        buffer[index] = num + 48;
    buffer[index + 1] = '\0';
    return my_revstr(buffer);
}

char *x_uppercase_type(va_list valist)
{
    unsigned int num = va_arg(valist, unsigned int);
    char *buffer = malloc(sizeof(char) * (my_len_int(num) + 1));
    unsigned int index = 0;

    for (index; num > 15; index++) {
        if (num % 16 > 9)
            buffer[index] = (num % 16) + 48 + 7;
        else
            buffer[index] = (num % 16) + 48;
        num = num / 16;
    }
    if (num > 9)
        buffer[index] = num + 48 + 7;
    else
        buffer[index] = num + 48;
    buffer[index + 1] = '\0';
    return my_revstr(buffer);
}

static int my_len_long(long num)
{
    int len = 0;

    if (num < 0)
        num *= -1;
    for (; num > 0; len++) {
        num /= 10;
    }
    return len;
}

int add_exp_ten(char *buff, int *exp_ten, long *num_long)
{
    if (*num_long < 0) {
        *num_long *= -1;
        buff[my_len_int(*num_long) + 5] = '-';
    }
    if (*exp_ten > 9) {
        buff[0] = (*exp_ten % 10) + '0';
        buff[1] = (*exp_ten / 10) + '0';
    } else {
        buff[0] = *exp_ten + '0';
        buff[1] = '0';
    }
}

char *e_type(va_list valist)
{
    double num = va_arg(valist, double);
    int exp_ten = my_len_long((long)num) - 1;
    long num_long = (long)(num * (1000000.0 /
        (my_compute_power_rec(10, exp_ten))));
    char *buff = malloc(sizeof(char) * (my_len_int(num_long) + 6));

    add_exp_ten(buff, &exp_ten, &num_long);
    buff[2] = '+';
    buff[3] = 'e';
    for (int i = 4; num_long > 0; i++) {
        if (i == 10) {
            buff[i] = '.';
        } else {
            buff[i] = num_long % 10 + '0';
            num_long /= 10;
        }
    }
    return my_revstr(buff);
}

char *e_uppercase_type(va_list valist)
{
    double num = va_arg(valist, double);
    int exp_ten = my_len_long((long)num) - 1;
    long num_long = (long)(num * (1000000.0 /
        (my_compute_power_rec(10, exp_ten))));
    char *buff = malloc(sizeof(char) * (my_len_int(num_long) + 6));

    add_exp_ten(buff, &exp_ten, &num_long);
    buff[2] = '+';
    buff[3] = 'E';
    for (int i = 4; num_long > 0; i++) {
        if (i == 10) {
            buff[i] = '.';
        } else {
            buff[i] = num_long % 10 + '0';
            num_long /= 10;
        }
    }
    return my_revstr(buff);
}
