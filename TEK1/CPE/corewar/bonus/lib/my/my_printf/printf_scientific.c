/*
** EPITECH PROJECT, 2024
** printf_scientific
** File description:
** Manage 'e' printf specifier
*/

#include "../my.h"

void manage_neg_exp(double nb, buffer_t *buff, format_t *flags, int up)
{
    double scientific = nb;
    int i = 0;

    for (; scientific < 1 && scientific > -1; i++)
        scientific *= 10;
    printf_putfloat(scientific, buff, flags);
    if (up == 1)
        printf_putstr("E-", buff, flags);
    else
        printf_putstr("e-", buff, flags);
    flags->precision = 2;
    printf_putnbr(i, buff, flags);
}

void printf_scientific(double nb, buffer_t *buff, format_t *flags, int up)
{
    double scientific = nb;
    int i = 0;

    if (nb < 1 && nb > -1) {
        manage_neg_exp(nb, buff, flags, up);
        return;
    }
    for (; scientific >= 10 || scientific <= -10; i++)
        scientific /= 10;
    printf_putfloat(scientific, buff, flags);
    if (up == 1)
        printf_putstr("E+", buff, flags);
    else
        printf_putstr("e+", buff, flags);
    flags->precision = 2;
    printf_putnbr(i, buff, flags);
}
