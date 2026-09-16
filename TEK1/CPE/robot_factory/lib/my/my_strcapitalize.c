/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday06-theophile.riffe
** File description:
** my_strcapitalize
*/

#include "my.h"

static int my_isalpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return 1;
    return 0;
}

int my_isalnum(char c)
{
    if (my_isalpha(c) || (c >= '0' && c <= '9'))
        return 1;
    return 0;
}

static char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        c -= 32;
    return c;
}

static char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        c += 32;
    return c;
}

char *my_strcapitalize(char *str)
{
    int new_word = 1;

    if (str == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++){
        if (!my_isalnum(str[i])) {
            new_word = 1;
            continue;
        }
        if (new_word == 1)
            str[i] = to_upper(str[i]);
        else
            str[i] = to_lower(str[i]);
        new_word = 0;
    }
    return str;
}
