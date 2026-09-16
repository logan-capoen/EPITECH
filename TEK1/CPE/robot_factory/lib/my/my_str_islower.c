/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday06-theophile.riffe
** File description:
** str_isalpha
*/

#include "my.h"

static int my_islower(char c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    return 0;
}

int my_str_islower(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!my_islower(str[i]))
            return 0;
    return 1;
}
