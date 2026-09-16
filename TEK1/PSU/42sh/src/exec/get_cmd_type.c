/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** get_cmd_type.c
*/

/**
 * @file get_cmd_type.c
 * @brief Determines the type of a command in the 42sh shell.
 *
 * This file contains the implementation of the `get_cmd_type` function,
 * which identifies whether a command is a built-in command, a subcommand,
 * or an external command. It also handles cases where no command is present.
 */

#include "exec.h"

/**
 * @brief Determines the type of a given command.
 *
 * @param cmd Pointer to the command structure to analyze.
 * @return An integer representing the type of the command:
 * - `NOTHING` if the command is NULL or empty.
 * - `SUBCMD` if the command contains subcommands.
 * - `BUILT_CMD` if the command is a built-in command.
 * - `CMD` if the command is an external command.
 *
 */
int get_cmd_type(commands_t *cmd)
{
    if (!cmd || (!cmd->command && !cmd->subcommands))
        return NOTHING;
    if (!cmd->command)
        return SUBCMD;
    if (!cmd->command[0])
        return NOTHING;
    for (int i = 0; i < NB_BUILT_IN; i++)
        if (!strcmp(tab[i].command, cmd->command[0]))
            return BUILT_CMD;
    return CMD;
}
