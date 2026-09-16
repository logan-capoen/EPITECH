/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** display_cat
*/

#include "builtins.h"
#include "cat.h"

int display_cat(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local)
{
    shell = shell;
    command = command;
    for (int i = 0; i < ROWS; i++) {
        printf("%s", meowsh[i]);
    }
    return 0;
}
