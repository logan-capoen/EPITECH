/*
** EPITECH PROJECT, 2024
** fourth_arg_type
** File description:
** fourth definition of arg type fonctions
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char *a_type(va_list valist)
{
    return 0;
}

char *a_uppercase_type(va_list valist)
{
    return 0;
}

char *c_type(va_list valist)
{
    char *buff = malloc(sizeof(char) * 2);

    buff[0] = va_arg(valist, int);
    buff[1] = '\0';
    return buff;
}

char *s_type(va_list valist)
{
    char *str = va_arg(valist, char *);

    if (str == NULL)
        return "(null)";
    return str;
}
