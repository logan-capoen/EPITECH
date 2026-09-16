/*
** EPITECH PROJECT, 2024
** my_print_nbr
** File description:
** 00(============)00
*/

#include "../../include/my.h"

int my_put_nbr(int nb)
{
    if (nb == -2147483648) {
        my_putchar('-');
        my_putchar('2');
        my_put_nbr(147483648);
    }
    if (nb != -2147483648) {
        if (nb < 0) {
            my_putchar('-');
            nb *= -1;
        }
        if (nb >= 10) {
            my_put_nbr(nb / 10);
        }
        my_putchar((nb % 10) + 48);
    }
    return 0;
}
