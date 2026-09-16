/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday05-theophile.riffe
** File description:
** compute_power_rec
*/

#include "my.h"

static int will_overflow_power(int nb, int result)
{
    if (result == 0)
        return 0;
    if (nb > 0 && nb > INT_MAX / result)
        return 1;
    if (nb < 0) {
        if (result > 0 && nb < INT_MIN / result)
            return 1;
        if (result < 0 && nb < INT_MAX / result)
            return 1;
    }
    return 0;
}

int my_compute_power_rec(int nb, int p)
{
    int result = 1;

    if (p < 0)
        return 0;
    if (p == 0)
        return 1;
    if (p == 1)
        return nb;
    result = my_compute_power_rec(nb, p - 1);
    if (will_overflow_power(nb, result))
        return 0;
    return nb * result;
}
