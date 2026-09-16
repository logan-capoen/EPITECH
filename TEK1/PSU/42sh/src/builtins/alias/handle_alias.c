/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_alias
*/

/**
 * @file handle_alias.c
 * @brief Functions to manage aliases in the shell.
 *
 * This file contains functions to handle the creation, addition, and deletion
 * of aliases in the shell. Aliases allow users to define shortcuts
 * for commands.
 */

#include "builtins.h"

/**
 * @brief Add a new alias to the aliases linked list.
 *
 * This function adds a new alias node to the linked list of aliases. The list
 * is maintained in lexicographical order based on the alias name.
 *
 * @param aliases Pointer to the head of the aliases linked list.
 * @param new_node Pointer to the new alias node to add.
 */
void add_node(aliases_t **aliases, aliases_t *new_node)
{
    aliases_t *current = *aliases;
    aliases_t *previous = NULL;

    if (!*aliases || strcmp(new_node->original, current->original) < 0) {
        new_node->next = *aliases;
        *aliases = new_node;
        return;
    }
    while (current && strcmp(new_node->original, current->original) > 0) {
        previous = current;
        current = current->next;
    }
    new_node->next = current;
    previous->next = new_node;
}

/**
 * @brief Free memory allocated for an alias node.
 *
 * This function frees the memory allocated for a single alias node,
 * including its `original` and `new_name` strings.
 *
 * @param node Pointer to the alias node to free.
 */
void free_node(aliases_t *node)
{
    if (node && node->original)
        free(node->original);
    if (node && node->new_name)
        free(node->new_name);
    if (node)
        free(node);
}

/**
 * @brief Delete an alias from the aliases linked list.
 *
 * This function removes an alias node from the linked list of aliases and
 * frees its memory. If the alias to delete is the head of the list, the head
 * pointer is updated.
 *
 * @param aliases Pointer to the head of the aliases linked list.
 * @param current Pointer to the alias node to delete.
 * @param previous Pointer to the alias node preceding the one to delete.
 */
void delete_node(aliases_t **aliases, aliases_t *current, aliases_t *previous)
{
    aliases_t *tmp = NULL;

    if (current == *aliases) {
        tmp = current;
        *aliases = current->next;
        free_node(tmp);
        return;
    }
    tmp = current;
    previous->next = current->next;
    free_node(tmp);
}
