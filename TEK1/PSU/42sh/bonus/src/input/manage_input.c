/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** manage_input.c
*/

/**
 * @file manage_input.c
 * @brief Implementation of the input management.
 *
 * This file contains functions that manage user input character by character,
 * including handling special keys (e.g., Backspace, Delete) and inserting
 * printable characters into the input string.
 */

#include "input.h"

/**
 * @brief Handles the behavior when the Backspace key is pressed.
 *
 * This function deletes the character before the cursor if the Backspace
 * key (ASCII 127) is pressed. It shifts the remaining characters to the left
 * and updates the input length and cursor position.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @return 1 if the Backspace key was handled, 0 otherwise.
 */
static int handle_backspace(input_t *input)
{
    if (input->char_input == 127 && input->cursor_pos > 0) {
        memmove(&input->str_input[input->cursor_pos - 1],
            &input->str_input[input->cursor_pos],
            input->input_len - input->cursor_pos);
        (input->input_len)--;
        (input->cursor_pos)--;
        (input->str_input)[input->input_len] = '\0';
        return 1;
    }
    return 0;
}

/**
 * @brief Moves memory to insert a character at the cursor position.
 *
 * This function shifts all characters after the cursor one position to the
 * right and inserts the given character at the cursor position.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @return 0 on success.
 */
static int make_memmove(input_t *input)
{
    memmove(&input->str_input[input->cursor_pos + 1],
        &input->str_input[input->cursor_pos],
        input->input_len - input->cursor_pos);
    input->str_input[input->cursor_pos] = input->char_input;
    return 0;
}

/**
 * @brief Allocates memory for the input string.
 *
 * This function allocates or reallocates memory for the input string
 * depending on its current state. If the input string is `NULL`, it allocates
 * memory for a new string. Otherwise, it reallocates memory to expand the
 * string.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @return 1 on memory allocation failure, 0 on success.
 */
static int allocate_str_input(input_t *input)
{
    if (input->str_input == NULL) {
        input->str_input = (char *)malloc(2 * sizeof(char));
        if (!input->str_input) {
            perror("malloc");
            return 1;
        }
        (input->str_input)[0] = '\0';
    }
    input->str_input = realloc(input->str_input,
        (input->input_len + 2) * sizeof(char));
    if (!input->str_input) {
        perror("realloc");
        return 1;
    }
    return 0;
}

/**
 * @brief Manages user input by handling special keys and printable characters.
 *
 * This function processes user input character by character. It handles
 * special keys (e.g., Backspace, Delete) and inserts printable characters
 * into the input string. It also updates the input length and cursor position
 * accordingly.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @param shell Pointer to the shell structure containing environment variables
 *              and other shell-related data.
 * @return 0 on success, 1 on memory allocation failure.
 */
int manage_input(input_t *input, shell_t *shell)
{
    int res = handle_sequences(input, shell);

    if (res)
        return res == 1 ? 0 : 1;
    if (input->char_input == '\t')
        return autocomplete_tabs(input, shell);
    if (handle_backspace(input))
        return 0;
    if (allocate_str_input(input))
        return 1;
    if (input->input_len == input->cursor_pos && isprint(input->char_input)) {
        input->str_input[input->cursor_pos] = input->char_input;
        input->str_input[input->cursor_pos + 1] = '\0';
    } else if (isprint(input->char_input))
        make_memmove(input);
    else
        return 0;
    input->input_len += 1;
    input->cursor_pos += 1;
    return 0;
}
