/*
** EPITECH PROJECT, 2024
** struct_printf.h
** File description:
** all the structure
*/

#ifndef STRUCT
    #define STRUCT
    #include <stdarg.h>
    #include "./printf.h"
    #include <stddef.h>

static const flag_struct_t flags_tab[6] =
    {{.flag = '-', .function = &dash_flag},
    {.flag = '0', .function = &zero_flag},
    {.flag = ' ', .function = &space_flag},
    {.flag = '+', .function = &plus_flag},
    {.flag = '#', .function = &sharp_flag},
    {.flag = '\0', .function = NULL}};

static const arg_type_t arg_types_tab[21] =
    {{.letter = 'd', .function = &i_d_type},
    {.letter = 'i', .function = &i_d_type},
    {.letter = 'o', .function = &o_type},
    {.letter = 'u', .function = &u_type},
    {.letter = 'x', .function = &x_type},
    {.letter = 'X', .function = &x_uppercase_type},
    {.letter = 'e', .function = &e_type},
    {.letter = 'E', .function = &e_uppercase_type},
    {.letter = 'f', .function = &f_type},
    {.letter = 'F', .function = &f_type},
    {.letter = 'g', .function = &g_type},
    {.letter = 'G', .function = &g_uppercase_type},
    {.letter = 'a', .function = &a_type},
    {.letter = 'A', .function = &a_uppercase_type},
    {.letter = 'c', .function = &c_type},
    {.letter = 's', .function = &s_type},
    {.letter = 'p', .function = &p_type},
    {.letter = 'n', .function = &n_type},
    {.letter = 'm', .function = &m_type},
    {.letter = '%', .function = &pourcent_type},
    {.letter = '\0', .function = NULL}};

#endif
