/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday07-theophile.riffe
** File description:
** my_strcat
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    for (; src[i] != '\0'; i++)
        dest[i + dest_len] = src[i];
    dest[i + dest_len] = '\0';
    return dest;
}
