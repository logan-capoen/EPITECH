/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday04-theophile.riffe
** File description:
** my_swap
*/

#include "my.h"

void my_swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}
