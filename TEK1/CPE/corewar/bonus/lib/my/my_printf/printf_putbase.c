/*
** EPITECH PROJECT, 2024
** printf_putbase
** File description:
** base conversions
*/

#include "../my.h"

char hex_char(long entier)
{
    if (entier >= 0 && entier <= 9)
        return '0' + entier;
    else {
        entier = entier - 10;
        return 'a' + entier;
    }
}

char *convert_hex(long nb)
{
    char *hexadecimal = malloc(50);
    long quotient = nb;
    long remainder = 0;
    int index_hex = 0;

    if (nb == 0) {
        hexadecimal[0] = '0';
        hexadecimal[1] = 0;
        return hexadecimal;
    }
    while (quotient != 0) {
        remainder = quotient % 16;
        quotient = quotient / 16;
        hexadecimal[index_hex] = hex_char(remainder);
        index_hex++;
    }
    hexadecimal[index_hex] = '\0';
    return my_revstr(hexadecimal);
}

char *convert_oct(long nb)
{
    char *octal = malloc(50);
    long quotient = nb;
    long remainder = 0;
    int index = 0;

    if (nb == 0) {
        octal[0] = '0';
        octal[1] = 0;
        return octal;
    }
    while (quotient != 0) {
        remainder = quotient % 8;
        quotient = quotient / 8;
        octal[index] = '0' + remainder;
        index++;
    }
    octal[index] = '\0';
    return my_revstr(octal);
}

char *printf_pointer(void *adress)
{
    char *pointer = malloc(30 * sizeof(char));
    int i = 0;
    char *hex_adress = NULL;

    pointer[0] = '0';
    pointer[1] = 'x';
    hex_adress = convert_hex((uintptr_t)adress);
    for (; hex_adress[i] != 0; i++) {
        pointer[i + 2] = hex_adress[i];
    }
    pointer[i + 2] = 0;
    return pointer;
}

static int printf_putunsigned(unsigned int n, buffer_t *buff, format_t *flags)
{
    for (int i = 0; i < flags->width - number_len(n); i++)
        printf_putchar(' ', buff);
    for (int i = 0; i < flags->precision - number_len(n); i++)
        printf_putchar('0', buff);
    flags->width = 0;
    flags->precision = -1;
    if (n >= 10)
        printf_putnbr(n / 10, buff, flags);
    printf_putchar(n % 10 + '0', buff);
    return 0;
}

void printf_decimal(int nbr, buffer_t *buff, format_t *flags)
{
    if (nbr < 0) {
        printf_putunsigned(UINT_MAX + 1 + nbr, buff, flags);
    } else {
        printf_putunsigned(nbr, buff, flags);
    }
}
