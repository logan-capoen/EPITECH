/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias
*/

/**
 * @file alias.c
 * @brief All functions to handle the adding of aliases.
 *
 * This file contains all the functions
 * to add an alias
 */
#include "builtins.h"
#include "globbings.h"

/**
 * @brief Get the history from the file.
 *
 * @param aliases The linked list containing all the aliases
 * @return Exit code
 */
static int display_aliases(aliases_t **aliases)
{
    aliases_t *current = *aliases;
    int need_parenthesis = 0;

    for (; current; current = current->next) {
        for (int i = 0; current->new_name[i] && !need_parenthesis; i++)
            need_parenthesis += (current->new_name[i] == ' ');
        if (need_parenthesis)
            printf("%s\t(%s)\n", current->original, current->new_name);
        else
            printf("%s\t%s\n", current->original, current->new_name);
        need_parenthesis = 0;
    }
    return 0;
}

/**
 * @brief Check if the alias already exists
 *
 * @param aliases The linked list containing all the aliases
 * @param command The whole command to execute
 * @return Exit code to say if the alias exists
 */
static int alias_exists(aliases_t **aliases, char **command)
{
    aliases_t *current = *aliases;
    int to_return = 0;

    for (; current; current = current->next) {
        if (strcmp(current->original, command[1]) == 0) {
            free(current->new_name);
            current->new_name = strdup(create_concat_array(&(command[2])));
            to_return = 1;
            break;
        }
    }
    if (to_return && !current->new_name)
        to_return = 2;
    return to_return;
}

/**
 * @brief Add an alias into the main storage
 *
 * @param aliases The linked list containing all the aliases
 * @param command The whole command to execute
 * @return Exit code
 */
static int add_alias(aliases_t **aliases, char **command)
{
    aliases_t *new_node = malloc(sizeof(aliases_t));
    int exist = 0;

    if (!new_node) {
        dprintf(2, "Allocation error for new_node\n");
        return 1;
    }
    exist = alias_exists(aliases, command);
    if (exist) {
        free(new_node);
        return exist == 2;
    }
    *new_node = (aliases_t){strdup(command[1]),
        create_concat_array(&(command[2])), 0, NULL};
    if (!new_node->original || !new_node->new_name) {
        free_node(new_node);
        return 1;
    }
    add_node(aliases, new_node);
    return 0;
}

/**
 * @brief Handles the `alias` command in the shell.
 *
 * This function interprets the `alias` command based on the number of
 * arguments provided:
 * - If no arguments are provided, it displays all existing aliases.
 * - If one argument is provided, it does nothing (reserved for future use).
 * - If two or more arguments are provided, it adds a new alias to the list.
 *
 * @param shell The shell structure containing the alias list.
 * @param command The array of arguments passed to the `alias` command.
 * @param local Unused parameter (reserved for future use).
 * @return 0 on success, 1 on failure.
 */
int interpret_alias(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local)
{
    int len = 0;

    for (; command[len]; len++);
    switch (len) {
        case 1:
            return display_aliases(shell->aliases);
        case 2:
            return 0;
        default:
            return add_alias(shell->aliases, command);
    }
    return 1;
}
