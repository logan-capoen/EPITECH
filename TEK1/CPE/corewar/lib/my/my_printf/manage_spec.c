/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** manage_spec
*/

#include "../my.h"

const printf_t SPECIFIERS[] = {
    {'c', &print_char},
    {'s', &print_string},
    {'d', &print_int},
    {'i', &print_int},
    {'%', &print_mudulo},
    {'f', &print_float},
    {'p', &print_pointer},
    {'x', &print_puthexmin},
    {'X', &print_puthexmaj},
    {'o', &print_octal},
    {'e', &print_scientific},
    {'n', &print_nspec},
    {'u', &print_decimal},
    {'E', &print_capscientific},
    {'g', &print_g_low},
    {'G', &print_g_up},
    {0, NULL}
};

void manage_specifiers(char c, va_list args, buffer_t *buff, format_t *spec)
{
    for (int i = 0; SPECIFIERS[i].c != '\0'; i++) {
        if (c == SPECIFIERS[i].c) {
            SPECIFIERS[i].func(args, buff, spec);
            return;
        }
    }
    printf_putchar('%', buff);
    printf_putchar(c, buff);
}
