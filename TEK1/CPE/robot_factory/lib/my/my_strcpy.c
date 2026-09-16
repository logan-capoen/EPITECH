/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday06-theophile.riffe
** File description:
** my_strcpy
*/

#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (src == NULL)
        return NULL;
    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
