/*
** EPITECH PROJECT, 2024
** tools_functions
** File description:
** like len, is etc
*/

#include "../../include/printf.h"
#include "../../include/my.h"
#include "../../include/struct_printf.h"

int flag_len(char *format)
{
    int len = 0;

    while (is_flag(format[len]) != -1)
        len++;
    return len;
}

int is_flag(char chara)
{
    for (int i = 0; flags_tab[i].flag != '\0'; i++) {
        if (chara == flags_tab[i].flag)
            return i;
    }
    return -1;
}

int index_flag(char chara, specifiers_t spec)
{
    for (int i = 0; spec.flags[i] != '\0'; i++) {
        if (chara == spec.flags[i])
            return i;
    }
    return -1;
}

int is_arg_type(char chara, const arg_type_t *arg_types_tab)
{
    for (int i = 0; arg_types_tab[i].letter != '\0'; i++) {
        if (chara == arg_types_tab[i].letter)
            return i;
    }
    return -1;
}

int my_len_int(int num)
{
    int len = 0;

    if (num < 0)
        num *= -1;
    for (; num > 0; len++) {
        num /= 10;
    }
    if (len == 0)
        return 1;
    return len;
}
