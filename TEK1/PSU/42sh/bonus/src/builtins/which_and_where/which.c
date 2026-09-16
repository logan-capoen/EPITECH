/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** which
*/

/**
 * @file which.c
 * @brief Implementation of the `which` builtin command.
 *
 * This file contains the implementation of the `which` command, which
 * identifies the location of executables or aliases in the shell.
 */

#include "builtins.h"
#include "utilities.h"
#include "exec.h"

/**
 * @brief Check if a command is a shell built-in for which.
 *
 * This function loops through the `tab` of built-in commands and checks
 * if the given command matches any of the built-ins. If it is a built-in,
 * it prints a message indicating that it is a shell built-in command.
 *
 * @param command The command to check.
 * @return 1 if the command is a built-in, 0 otherwise.
 */
int is_a_builtin_command_which(char *command)
{
    for (int i = 0; i < NB_BUILT_IN; i++) {
        if (strcmp(tab[i].command, command) == 0) {
            printf("%s: shell built-in command.\n", command);
            return 1;
        }
    }
    if (strcmp(command, "echo") == 0) {
        printf("%s: shell built-in command.\n", command);
        return 1;
    }
    return 0;
}

/**
 * @brief Search for an alias in the shell's alias list.
 *
 * This function searches the shell's alias list for a given string. If
 * the alias is found, it prints the alias and its corresponding command.
 *
 * @param shell Pointer to the shell structure containing the alias list.
 * @param str The string to search for in the alias list.
 * @return 1 if the alias is found, 0 otherwise.
 */
static int search_alias(shell_t *shell, char *str)
{
    aliases_t *current = *(shell->aliases);

    for (; current; current = current->next) {
        if (strcmp(current->original, str) == 0) {
            printf("%s:\taliased to %s\n",
                current->original, current->new_name);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Search for a command in the system's PATH.
 *
 * This function searches for a given command in the directories listed
 * in the shell's `PATH` environment variable. If the command is found,
 * its full path is printed.
 *
 * @param shell Pointer to the shell structure containing the environment.
 * @param str The command to search for in the `PATH`.
 * @return 1 if the command is found, 0 otherwise.
 */
static int search_path(shell_t *shell, char *str)
{
    char *path = get_cmd_path(str, shell->env->global);

    if (is_a_builtin_command_which(str)) {
        if (path)
            free(path);
        return 1;
    }
    if (!path) {
        dprintf(2, "%s: Command not found.\n", str);
        return 0;
    }
    printf("%s\n", path);
    free(path);
    return 1;
}

/**
 * @brief Handle the `which` command.
 *
 * This function processes the `which` command, which identifies the
 * location of executables or aliases. It checks if the provided arguments
 * are aliases or commands in the `PATH` and prints their locations.
 *
 * @param shell Pointer to the shell structure containing aliases
 * and environment variables.
 * @param command Array of strings representing the `which`
 * command and its arguments.
 * @param local Unused parameter for compatibility with other builtins.
 * @return 0 on success, 1 on failure (e.g., too few arguments).
 */
int interpret_which(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local)
{
    int array_len = 0;

    for (; command[array_len]; array_len++);
    if (array_len < 2) {
        dprintf(2, "which: Too few arguments\n");
        return 1;
    }
    for (int i = 1; i < array_len; i++) {
        if (!search_alias(shell, command[i]))
            search_path(shell, command[i]);
    }
    return 0;
}
