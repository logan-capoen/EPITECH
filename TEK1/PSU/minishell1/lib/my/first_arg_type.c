/*
** EPITECH PROJECT, 2024
** first_arg_type
** File description:
** first definition of arg_type fonction
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../../include/printf.h"
#include "../../include/my.h"

int int_to_str(int num, char *buff)
{
    for (int i = 0; num > 0; i++) {
        buff[i] = num % 10 + '0';
        num /= 10;
    }
    return 0;
}

char *i_d_type(va_list valist)
{
    int num = va_arg(valist, int);
    char *buff = malloc(sizeof(char) * (my_len_int(num) + 2));

    buff[my_len_int(num) + 1] = '\0';
    if (num == 0)
        return "0";
    if (num < 0) {
        num *= -1;
        buff[my_len_int(num)] = '-';
    }
    for (int i = 0; num > 0; i++) {
        buff[i] = num % 10 + '0';
        num /= 10;
    }
    return my_revstr(buff);
}

char *o_type(va_list valist)
{
    unsigned int num = va_arg(valist, unsigned int);
    int add = 0;
    int result = 0;
    char *buff = malloc(sizeof(char) * (my_len_int(num) * 2 + 1));

    if (num == 0)
        return "0";
    for (int i = 0; num > 0; i++) {
        add = num % 8;
        if (add >= 8) {
            add += 2;
            int_to_str(add, buff);
            i++;
        } else
            buff[i] = add + '0';
        num /= 8;
    }
    return my_revstr(buff);
}

char *u_type(va_list valist)
{
    unsigned int num = va_arg(valist, int);
    char *buff = malloc(sizeof(char) * (my_len_int(num) + 1));

    if (num < 0) {
        num *= -1;
        buff[my_len_int(num)] = '-';
    }
    for (int i = 0; num > 0; i++) {
        buff[i] = num % 10 + '0';
        num /= 10;
    }
    return my_revstr(buff);
}
