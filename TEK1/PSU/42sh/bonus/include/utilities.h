/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** utilities header
*/

#ifndef UTILITIES
    #define UTILITIES

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "meowsh.h"

int del_elt(char ***array, int index);
char **dup_array(char **src);
void free_array(char **array);
void free_shell(shell_t *shell);
shell_t *init_struct(shell_t *shell, char **envp);
void free_commands(commands_t **cmds);
char **my_str_to_word_array(const char *str, const char *spliters);
char *strjoin(char *str1, char *str2);
char *int_to_str(int value);

#endif
