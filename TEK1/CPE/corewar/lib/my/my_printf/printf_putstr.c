/*
** EPITECH PROJECT, 2024
** my_libc
** File description:
** my_putstr
*/

#include "../my.h"

void printf_putstr(char const *str, buffer_t *buff, format_t *flags)
{
    for (int i = 0; i < flags->width - my_strlen(str); i++)
        printf_putchar(' ', buff);
    if (str == NULL)
        return;
    for (int i = 0; str[i] != '\0'; i++) {
        printf_putchar(str[i], buff);
    }
}
