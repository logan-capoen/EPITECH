/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday06-theophile.riffe
** File description:
** my_strncpy
*/

#include "my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (src == NULL || dest == NULL || n < 1)
        return NULL;
    for (; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}
