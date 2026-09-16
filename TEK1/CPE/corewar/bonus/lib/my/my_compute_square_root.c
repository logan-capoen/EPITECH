/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday05-theophile.riffe
** File description:
** square_root
*/

#include "my.h"

int my_compute_square_root(int nb)
{
    int result = 1;

    if (nb < 0)
        return 0;
    while (result * result < nb)
        result++;
    if (result * result != nb)
        return 0;
    return result;
}
