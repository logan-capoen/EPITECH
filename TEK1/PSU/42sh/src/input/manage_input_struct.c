/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** manage_input_struct.c
*/

/**
 * @file manage_input_struct.c
 * @brief Functions to initialize and free the input structure.
 *
 * This file contains functions to manage the lifecycle of the `input_t`
 * structure, including initialization and memory cleanup.
 */

#include "input.h"

/**
 * @brief Initializes the input structure.
 *
 * This function allocates memory for the `input_t` structure and initializes
 * its fields to default values.
 *
 * @param input Double pointer to the input structure to initialize.
 * @param shell Pointer to the shell structure containing environment variables
 *              and other shell-related data.
 * @return 0 on success, 1 on memory allocation failure.
 */
int init_input(input_t **input, shell_t *shell)
{
    *input = malloc(sizeof(input_t));
    if (!*input)
        return 1;
    (*input)->char_input = '\0';
    (*input)->cursor_pos = 0;
    (*input)->input_len = 0;
    (*input)->str_input = NULL;
    (*input)->history_pos = shell->history_size;
    (*input)->stock_history = NULL;
    return 0;
}

/**
 * @brief Frees the memory allocated for the input structure.
 *
 * This function frees the memory allocated for the `input_t` structure,
 * including the dynamically allocated input string.
 *
 * @param input Pointer to the input structure to free.
 */
void free_input(input_t *input)
{
    if (input) {
        if (input->str_input)
            free(input->str_input);
        if (input->stock_history)
            free(input->stock_history);
        free(input);
    }
}
