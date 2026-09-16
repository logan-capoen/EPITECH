/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** is_built_command.c
*/

#include "exec.h"

/**
 * @brief Determines if a command is a built-in command.
 *
 * This function checks if the given command matches any of the built-in
 * commands defined in the shell. If the command is a built-in, it returns 1.
 * If the command is NULL, it returns 2. Otherwise, it returns 0.
 *
 * @param cmd The command to check.
 * @return int
 * - 1 if the command is a built-in command.
 * - 2 if the command is NULL.
 * - 0 if the command is not a built-in command.
 */
int is_built_command(char *cmd)
{
    if (!cmd)
        return SUBCMD;
    for (int i = 0; i < NB_BUILT_IN; i++)
        if (!strcmp(tab[i].command, cmd))
            return BUILT_CMD;
    return CMD;
}
