/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday05-theophile.riffe
** File description:
** find_prime_sup
*/

#include "my.h"

int my_find_prime_sup(int n)
{
    for (int i = n; i < INT_MAX; i++)
        if (my_is_prime(i))
            return i;
    return 0;
}
