/*
** EPITECH PROJECT, 2024
** tools_flags
** File description:
** tools for flags
*/

#include "../../include/my.h"
#include "../../include/printf.h"
#include "../../include/struct_printf.h"

char *exe_ptr_on_fct(char c, char *buff_width)
{
    for (int i = 0; i < 6; i++) {
        if (c == flags_tab[i].flag)
            return (*(flags_tab[i].function))(buff_width);
    }
    return buff_width;
}

int special_flags_case(specifiers_t *spec)
{
    if ((spec->arg_type == 's' || spec->arg_type == 'c'
        || spec->arg_type == '%' || spec->arg_type == 'x'
        || spec->arg_type == 'X')
        && is_flag('0') != -1)
        (*spec).flags[index_flag('0', (*spec))] = '?';
    if ((spec->arg_type == 'x' || spec->arg_type == 'X'
        || spec->arg_type == 'o' || spec->arg_type == 'u'
        || spec->arg_type == 's' || spec->arg_type == 'c'
        || spec->arg_type == '%')
        && is_flag('+') != -1)
        (*spec).flags[index_flag('+', (*spec))] = '?';
    if ((spec->arg_type == 'x' || spec->arg_type == 'X'
        || spec->arg_type == 'o' || spec->arg_type == 's'
        || spec->arg_type == 'c' || spec->arg_type == 'u'
        || spec->arg_type == 'p' || spec->arg_type == '%')
        && is_flag(' ') != -1)
        (*spec).flags[index_flag(' ', (*spec))] = '?';
    return 0;
}

static int subdiv_sort_flags(int i, int dec, specifiers_t *spec, int *find)
{
    char temp = 0;
    char *sort = "+-0 \0";

    for (int j = 0; j < my_strlen((*spec).flags); j++) {
        if (sort[i] == (*spec).flags[j]) {
            temp = (*spec).flags[i + dec];
            (*spec).flags[i + dec] = (*spec).flags[j];
            (*spec).flags[j] = temp;
            *find += 1;
        }
    }
    return 0;
}

int sort_flags(specifiers_t *spec)
{
    char *sort = "+-0 \0";
    int dec = 0;
    int find = -1;
    char temp;

    for (int i = 0; sort[i] != '\0'; i++) {
        subdiv_sort_flags(i, dec, spec, &find);
        if (find != i) {
            dec--;
            find++;
        }
    }
    return 0;
}
