/*
** EPITECH PROJECT, 2024
** my_lib
** File description:
** my_put_nbr
*/

#include "my.h"

int my_put_nbr(int n)
{
    if (n == INT_MIN) {
        my_putchar('-');
        my_putchar('2');
        n = 147483648;
    } else if (n < 0){
        my_putchar('-');
        n = - n;
    }
    if (n >= 10)
        my_put_nbr(n / 10);
    my_putchar(n % 10 + '0');
    return 0;
}
