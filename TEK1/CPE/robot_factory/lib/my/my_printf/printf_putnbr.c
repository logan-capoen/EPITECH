/*
** EPITECH PROJECT, 2024
** my_lib
** File description:
** my_put_nbr
*/

#include "../my.h"

int number_len(int n)
{
    int len = 0;

    if (n == 0)
        return 1;
    if (n < 0)
        n = -n;
    while (n > 0) {
        n /= 10;
        len++;
    }
    return len;
}

int printf_putnbr(int n, buffer_t *buff, format_t *flags)
{
    for (int i = 0; i < flags->width - number_len(n); i++)
        printf_putchar(' ', buff);
    for (int i = 0; i < flags->precision - number_len(n); i++)
        printf_putchar('0', buff);
    flags->width = 0;
    flags->precision = -1;
    if (n == INT_MIN) {
        printf_putchar('-', buff);
        printf_putchar('2', buff);
        n = 147483648;
    } else if (n < 0) {
        printf_putchar('-', buff);
        n = -n;
    }
    if (n >= 10)
        printf_putnbr(n / 10, buff, flags);
    printf_putchar(n % 10 + '0', buff);
    return 0;
}
