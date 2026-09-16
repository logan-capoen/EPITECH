/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday07-theophile.riffe
** File description:
** my_strncat
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, int n)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    for (; src[i] != '\0' && i < n; i++)
        dest[i + dest_len] = src[i];
    dest[i + dest_len] = '\0';
    return dest;
}
