/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** format header
*/

#ifndef FORMAT
    #define FORMAT
    #include "meowsh.h"
    #include <stdint.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #define NB_EXCEPTIONS 4
    #define MAX_NBR 11

static const char *exceptions[NB_EXCEPTIONS] __attribute__((unused)) = {
    "alias",
    "unalias",
    "which",
    "where"
};

char *add_spaces_around_operators(char *input);
char *format_input(char *input, shell_t *shell);
int handle_skipping(char **array, char **new_array,
    int i, int *skip_until_separator);
int handle_exceptions_and_quotes(char **array,
    char **new_array, int i, int *skip_after_separator);
int check_quote(char **array, char **new_array, int i);

#endif
