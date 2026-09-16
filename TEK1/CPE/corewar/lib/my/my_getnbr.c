/*
** EPITECH PROJECT, 2024
** my_lib
** File description:
** my_getnbr
*/

#include "my.h"

int convert_number(int *found_number, char c, int sign, long *result)
{
    int digit = 0;

    *found_number = 1;
    digit = c - '0';
    if (sign == 1 && (*result > (INT_MAX - digit) / 10))
        return -1;
    if (sign == -1 && (-(*result) < (INT_MIN + digit) / 10))
        return -1;
    *result = *result * 10 + digit;
    return 0;
}

int run_loop(char c, int *found_number, int *sign, long *result)
{
    if (c == '-' || c == '+') {
        if (*found_number)
            return 0;
        *sign = (c == '-') ? -1 : 1;
        return 1;
    }
    if (c >= '0' && c <= '9') {
        convert_number(found_number, c, *sign, result);
        return 1;
    }
    if (*found_number) {
        return 0;
    }
    return 0;
}

int my_getnbr(char const *str)
{
    long result = 0;
    int sign = 1;
    int i = 0;
    int found_number = 0;
    int error = 0;

    for (; str[i] != '\0'; i++) {
        error += run_loop(str[i], &found_number, &sign, &result);
    }
    if (error == 0)
        return -789456;
    return (int)(result * sign);
}
