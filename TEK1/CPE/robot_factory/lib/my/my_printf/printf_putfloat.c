/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** printf_putfloat
*/

#include "../my.h"

int manage_int(double nb, buffer_t *buff, format_t *flags)
{
    if ((int)(nb * 10) == 0) {
        printf_putchar('0', buff);
        printf_putchar('.', buff);
        for (int i = 0; i < flags->precision; i++)
            printf_putchar('0', buff);
        return 1;
    }
    return 0;
}

void printf_putfloat(double nb, buffer_t *buff, format_t *flags)
{
    int int_part = (int)nb;
    long full = 0;
    double rounding = 0.5;

    if (flags->precision == -1)
        flags->precision = 6;
    if (manage_int(nb, buff, flags))
        return;
    rounding = 0.5 / my_compute_power_rec(10, flags->precision);
    nb += rounding;
    full = nb * my_compute_power_rec(10, flags->precision);
    full = full - int_part * my_compute_power_rec(10, flags->precision);
    if (full < 0)
        full = -full;
    flags->width = 0;
    flags->precision = -1;
    printf_putnbr(int_part, buff, flags);
    printf_putchar('.', buff);
    printf_putnbr(full, buff, flags);
}
