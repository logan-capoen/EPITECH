/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday05-theophile.riffe
** File description:
** is_prime
*/

#include "my.h"

int my_is_prime(int nb)
{
    if (nb <= 1)
        return 0;
    for (int i = 2; i <= nb / 2; i++)
        if (nb % i == 0)
            return 0;
    return 1;
}
