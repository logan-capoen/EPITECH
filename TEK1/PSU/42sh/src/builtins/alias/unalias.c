/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** unalias
*/

/**
 * @file unalias.c
 * @brief Functions to handle the deletion of aliases in the shell.
 *
 * This file contains all the functions required to delete aliases from
 * the shell's alias list. It includes functionality to browse and remove
 * specific aliases based on user input.
 */

#include "builtins.h"

/**
 * @brief Remove a specific alias from the linked list.
 *
 * This function searches for an alias in the linked list by its name
 * (`to_delete`) and removes it if found. The memory associated with the alias
 * is freed.
 *
 * @param aliases Pointer to the head of the aliases linked list.
 * @param to_delete The name of the alias to delete.
 */
static void remove_alias(aliases_t **aliases, char *to_delete)
{
    aliases_t *current = *aliases;
    aliases_t *previous = current;

    while (current) {
        if (strcmp(current->original, to_delete) == 0) {
            delete_node(aliases, current, previous);
            return;
        }
        previous = current;
        current = current->next;
    }
}

/**
 * @brief Browse and delete multiple aliases.
 *
 * This function iterates through the list of aliases provided in the `command`
 * array and deletes each alias from the linked list.
 *
 * @param aliases Pointer to the head of the aliases linked list.
 * @param command Array of strings containing the aliases to delete.
 */
static void browse_to_unalias(aliases_t **aliases, char **command)
{
    for (int i = 1; command[i]; i++) {
        remove_alias(aliases, command[i]);
    }
}

/**
 * @brief Interpret the `unalias` command.
 *
 * This function processes the `unalias` command entered by the user. It checks
 * if the command has enough arguments and deletes the specified aliases from
 * the shell's alias list. If no arguments are provided, an error message is
 * displayed.
 *
 * @param shell Pointer to the shell structure containing the alias list.
 * @param command Array of strings representing the `unalias` command and
 *  its arguments.
 * @param local Unused parameter for compatibility with other builtins.
 * @return Exit code: 0 on success, 1 on failure (e.g., too few arguments).
 */
int interpret_unalias(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local)
{
    int len = 0;

    for (; command[len]; len++);
    switch (len) {
        case 1:
            dprintf(2, "unalias: Too few arguments.\n");
            return 1;
        default:
            browse_to_unalias(shell->aliases, command);
            return 0;
    }
}
