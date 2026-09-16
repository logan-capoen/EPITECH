/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_exit
*/

/**
 * @file my_exit.c
 * @brief Implementation of the `exit` builtin command.
 *
 * This file contains the implementation of the `exit` command, which
 * terminates the shell and optionally sets an exit code.
 */

#include "builtins.h"

/**
 * @brief Handles the `exit` command.
 *
 * This function processes the `exit` command, which terminates the shell.
 * If an exit code is provided as an argument, it is used as the shell's
 * exit code. Otherwise, the shell's current `exit_status` is used.
 *
 * @param shell Pointer to the shell structure.
 * @param command Array of strings representing the `exit`
 * command and its arguments.
 * @param local Unused parameter for compatibility with other builtins.
 * @return The exit code to terminate the shell with.
 */
int my_exit(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local)
{
    int exit_code = (command[1]) ? atoi(command[1]) : 0;

    shell->run = false;
    printf("exit\n");
    return exit_code;
}
