/*
** EPITECH PROJECT, 2024
** fifth_arg_type
** File description:
** fifth definition of arg type fonctions
*/

#include <stdlib.h>
#include <stdarg.h>
#include "../../include/my.h"
#include "../../include/printf.h"


static int my_len_long_int(long int num)
{
    int len = 0;

    if (num < 0)
        num *= -1;
    for (; num > 0; len++) {
        num /= 10;
    }
    return len;
}

char *p_type(va_list valist)
{
    long int num = va_arg(valist, long int);
    char *buffer = malloc(sizeof(char) * (my_len_long_int(num) + 3));
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
    buffer[index + 1] = 'x';
    buffer[index + 2] = '0';
    buffer[index + 3] = '\0';
    return my_revstr(buffer);
}

char *n_type(va_list valist)
{
    return 0;
}

char *m_type(va_list valist)
{
    return 0;
}

char *pourcent_type(va_list valist)
{
    char *buff = malloc(sizeof(char) * 2);

    buff[0] = '%';
    buff[1] = '\0';
    return buff;
}
