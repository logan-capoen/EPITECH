/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** where
*/

/**
 * @file where.c
 * @brief Implementation of the `where` builtin command.
 *
 * This file contains the implementation of the `where` command, which
 * identifies all the location of executables or aliases in the shell.
 */

#include "builtins.h"
#include "utilities.h"
#include "exec.h"

/**
 * @brief Check if a command is a shell built-in for where.
 *
 * This function loops through the `tab` of built-in commands and checks
 * if the given command matches any of the built-ins. If it is a built-in,
 * it prints a message indicating that it is a shell built-in command.
 *
 * @param command The command to check.
 * @return 1 if the command is a built-in, 0 otherwise.
 */
int is_a_builtin_command_where(char *command)
{
    for (int i = 0; i < NB_BUILT_IN; i++) {
        if (strcmp(tab[i].command, command) == 0) {
            printf("%s is a shell built-in\n", command);
            return 1;
        }
    }
    if (strcmp(command, "echo") == 0) {
        printf("%s is a shell built-in\n", command);
        return 1;
    }
    return 0;
}

/**
 * @brief Search for all aliases matching the given string.
 *
 * This function searches the shell's alias list for all occurrences of
 * the given string and prints them.
 *
 * @param shell Pointer to the shell structure containing the alias list.
 * @param str The string to search for in the alias list.
 * @return 1 if at least one alias is found, 0 otherwise.
 */
static int search_all_aliases(shell_t *shell, char *str)
{
    aliases_t *current = *(shell->aliases);
    int found = 0;

    for (; current; current = current->next) {
        if (strcmp(current->original, str) == 0) {
            printf("%s is aliased to %s\n",
                current->original, current->new_name);
            found = 1;
        }
    }
    return found;
}

/**
 * @brief Search for all occurrences of a command in the system's PATH.
 *
 * This function searches for all occurrences of a given command in the
 * directories listed in the shell's `PATH` environment variable and prints
 * their full paths.
 *
 * @param shell Pointer to the shell structure containing the environment.
 * @param str The command to search for in the `PATH`.
 * @return 1 if at least one occurrence is found, 0 otherwise.
 */
static int search_all_paths(shell_t *shell, char *str)
{
    char **paths = get_paths(shell->env->global);
    int found = 0;

    if (!paths)
        return 0;
    if (is_a_builtin_command_where(str))
        found = 1;
    for (int i = 0; paths[i]; i++) {
        if (check_path(str, paths[i])) {
            printf("%s%s\n", paths[i], str);
            found = 1;
        }
        free(paths[i]);
    }
    free(paths);
    if (!access(str, F_OK)) {
        found = 1;
        printf("%s\n", str);
    }
    return found;
}

/**
 * @brief Handle the `where` command.
 *
 * This function processes the `where` command, which identifies all
 * locations of executables or aliases. It checks if the provided arguments
 * are aliases or commands in the `PATH` and prints all their locations.
 *
 * @param shell Pointer to the shell structure containing aliases
 * and environment variables.
 * @param command Array of strings representing the `where`
 * command and its arguments.
 * @param local Unused parameter for compatibility with other builtins.
 * @return 0 on success, 1 on failure (e.g., too few arguments).
 */
int interpret_where(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local)
{
    int array_len = 0;
    int is_aliased = 0;
    int exists = 0;

    for (; command[array_len]; array_len++);
    if (array_len < 2) {
        dprintf(2, "where: Too few arguments\n");
        return 1;
    }
    for (int i = 1; i < array_len; i++) {
        is_aliased = search_all_aliases(shell, command[i]);
        exists = search_all_paths(shell, command[i]);
        if (!is_aliased && !exists)
            dprintf(2, "%s: Command not found.\n", command[i]);
    }
    return 0;
}
