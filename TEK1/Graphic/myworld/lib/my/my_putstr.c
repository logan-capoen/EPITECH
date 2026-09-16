/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** a function that displays, one-by-one, the characters of a string.
*/

#include "../../include/my.h"

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return 0;
}
