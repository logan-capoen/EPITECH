/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday06-theophile.riffe
** File description:
** my_strupcase.c
*/

#include "my.h"

char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    return str;
}
