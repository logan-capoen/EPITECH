/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday03-theophile.riffe
** File description:
** Task04
*/

#include "my.h"

int my_isneg(int n)
{
    if (n < 0)
        my_putchar('N');
    else
        my_putchar('P');
    return 0;
}
