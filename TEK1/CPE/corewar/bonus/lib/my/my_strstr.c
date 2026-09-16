/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday06-theophile.riffe
** File description:
** my_strstr
*/

#include "my.h"

static int compare(char const *str, char const *to_find)
{
    for (int i = 0; to_find[i] != '\0'; i++)
        if (str[i] != to_find[i])
            return 0;
    return 1;
}

char *my_strstr(char *str, char const *to_find)
{
    if (str == NULL)
        return NULL;
    if (to_find == NULL)
        return str;
    for (int i = 0; str[i] != '\0'; i++)
        if (compare(&str[i], to_find))
            return &str[i];
    return NULL;
}
