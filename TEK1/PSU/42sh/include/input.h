/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** input.h
*/

#ifndef INPUT_H
    #define INPUT_H

    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include "meowsh.h"
    #define BLUE "\033[1;34m"
    #define RESET "\033[0m"
    #define PURPLE "\033[0;38;5;56m"

typedef struct input_s {
    char *str_input;
    char char_input;
    size_t input_len;
    size_t cursor_pos;
    int history_pos;
    char *stock_history;
} input_t;

int handle_sequences(input_t *input, shell_t *shell);
int manage_input(input_t *input, shell_t *shell);
char *get_input(shell_t *shell);
int init_input(input_t **input, shell_t *shell);
void free_input(input_t *input);
int check_shortcut(input_t *input);
int display_line(input_t *input, shell_t *shell);
int autocomplete_tabs(input_t *input, shell_t *shell);

#endif
