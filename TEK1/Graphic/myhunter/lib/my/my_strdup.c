/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** function that allocates memory and copies the string
*/
#include "../../include/my.h"
#include <stdlib.h>

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *str = malloc((len + 1)* sizeof(char));

    my_strcpy(str, src);
    return str;
}
