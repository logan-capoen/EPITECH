/*
** EPITECH PROJECT, 2025
** free functions
** File description:
** all function for free
*/

/**
 * @file free_functionsc
 * @brief All function for free.
 *
 * This file contains all the functions
 * that can be used to free malloc.
 */
#include "include/minishell1.h"
#include <stdlib.h>

/**
 * @brief Frees the memory allocated for a single node in the environment list.
 *
 * @param env_list Pointer to the node to be freed.
 */
void free_node(env_t *env_list)
{
    free(env_list->key);
    free(env_list->value);
    free(env_list);
}

/**
 * @brief Frees the memory allocated for an array of strings.
 *
 * @param arr Pointer to the array of strings to be freed.
 */
void free_arr(char **arr)
{
    if (!arr)
        return;
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
}

/**
 * @brief Frees the memory allocated for the entire environment list.
 *
 * @param env_list Pointer to the head of the environment list to be freed.
 */
void free_list(env_t *env_list)
{
    env_t *prev = env_list;
    env_t *current = env_list;

    while (current != NULL) {
        prev = current;
        current = current->next;
        free(prev->key);
        free(prev->value);
        free(prev);
    }
}
