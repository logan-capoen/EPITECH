/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** env
*/

/**
 * @file env.c
 * @brief Contains the implementation of the `env` command.
 *
 * This file provides the function to display the environment variables
 * stored in the shell structure. It supports both global and local
 * environments and handles error cases such as invalid arguments.
 */

#include "meowsh.h"

/**
 * @brief Display the environment variables.
 *
 * This function prints the environment variables stored in the shell's
 * global or local environment, depending on the `local` parameter. If
 * additional arguments are passed to the `env` command, an error message
 * is displayed, and the shell's exit status is set to `127`.
 *
 * @param sh Pointer to the shell structure containing environment variables.
 * @param command Array of strings representing the `env`
 *  command and its arguments.
 * @param local If set to `1`, displays the local environment;
 *  otherwise, displays the global environment.
 * @return Always returns `0`.
 */
int my_env(shell_t *sh, char **command, int local)
{
    char **actual_env = (local) ? sh->env->local : sh->env->global;

    if (command[1]) {
        fprintf(stderr, "env: %s: No such file or directory\n", command[1]);
        return 127;
    }
    if (sh && sh->env && actual_env)
        for (int i = 0; actual_env[i]; i++)
            printf("%s\n", actual_env[i]);
    return 0;
}
