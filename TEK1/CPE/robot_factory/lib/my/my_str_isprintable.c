/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday06-theophile.riffe
** File description:
** str_isalpha
*/

#include "my.h"

static int my_isprintable(char c)
{
    if (c > 31 && c < 127)
        return 1;
    return 0;
}

int my_str_isprintable(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!my_isprintable(str[i]))
            return 0;
    return 1;
}
