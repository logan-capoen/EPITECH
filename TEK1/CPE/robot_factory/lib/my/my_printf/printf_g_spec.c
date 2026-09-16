/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** printf_g_spec
*/

#include "../my.h"

void printf_g_spec(double nb, buffer_t *buffer, format_t *flags, int up)
{
    int int_part = (int)nb;
    int int_len = 0;

    while (int_part != 0) {
        int_part /= 10;
        int_len++;
    }
    if (flags->precision == -1)
        flags->precision = 6;
    if (int_len > flags->precision){
        flags->precision -= 1;
        printf_scientific(nb, buffer, flags, up);
    } else {
        if (flags->precision <= int_len){
            printf_putnbr((int)nb, buffer, flags);
        } else {
            flags->precision -= int_len;
            printf_putfloat(nb, buffer, flags);
        }
    }
}
