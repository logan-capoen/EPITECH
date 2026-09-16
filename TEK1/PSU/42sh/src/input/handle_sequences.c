/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** handle_sequences.c
*/

/**
 * @file handle_sequences.c
 * @brief Implementation that handles user input sequences.
 *
 * This file contains functions to handle user input sequences, such as
 * cursor movement, history navigation, and special key handling.
 */

#include "input.h"

/**
 * @brief Resets the input string to its original state.
 *
 * This function restores the input string to its original state before
 * history navigation if the user exits history navigation.
 *
 * @param input Pointer to the input structure.
 * @param shell Pointer to the shell structure containing the history.
 * @param type Boolean indicating the direction of navigation (true for up,
 *             false for down).
 * @return 1 if the input was reset, 0 otherwise.
 */
static int reset_str_input_to_base(input_t *input, shell_t *shell, bool type)
{
    if (input->history_pos == shell->history_size && !type) {
        if (input->str_input)
            free(input->str_input);
        input->str_input = input->stock_history;
        input->stock_history = NULL;
        return 1;
    }
    return 0;
}

/**
 * @brief Changes the input string based on history navigation.
 *
 * Updates the input string to match the selected history entry or restores
 * the current input when exiting history navigation.
 *
 * @param input Pointer to the input structure.
 * @param shell Pointer to the shell structure containing the history.
 * @param type Boolean indicating the direction of navigation (true for up,
 *             false for down).
 * @return 0 on success, 1 on failure (e.g., memory allocation failure).
 */
static int change_input(input_t *input, shell_t *shell, bool type)
{
    if (input->history_pos < shell->history_size && type) {
        if (input->history_pos == shell->history_size - 1)
            input->stock_history = input->str_input;
        else
            free(input->str_input);
        input->str_input = strdup(shell->history[input->history_pos]);
        if (!input->str_input)
            return -1;
        return 1;
    }
    if (input->history_pos < shell->history_size && !type) {
        if (input->str_input)
            free(input->str_input);
        input->str_input = strdup(shell->history[input->history_pos]);
        if (!input->str_input)
            return -1;
        return 1;
    }
    return reset_str_input_to_base(input, shell, type);
}

/**
 * @brief Handles history navigation for arrow keys.
 *
 * Navigates through the history when the up or down arrow keys are pressed.
 *
 * @param input Pointer to the input structure.
 * @param seq Array containing the sequence.
 * @param shell Pointer to the shell structure containing the history.
 * @return 1 if the sequence was handled, 0 otherwise.
 */
static int handle_history(input_t *input, char seq[], shell_t *shell)
{
    if (seq[0] == '[' && seq[1] == 'A' && input->history_pos > 0) {
        input->history_pos -= 1;
        return change_input(input, shell, true);
    }
    if (seq[0] == '[' && seq[1] == 'B' &&
        input->history_pos < shell->history_size) {
        input->history_pos += 1;
        return change_input(input, shell, false);
    }
    return 0;
}

/**
 * @brief Handles cursor movement for arrow keys.
 *
 * Moves the cursor left or right based on the arrow key sequence.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @param seq Array containing the sequence.
 * @return 1 if the sequence was handled, 0 otherwise.
 */
static int handle_cursor(input_t *input, char seq[])
{
    if (seq[0] == '[' && seq[1] == 'C' &&
        input->cursor_pos < input->input_len) {
        input->cursor_pos += 1;
        write(STDOUT_FILENO, "\033[C", 3);
        return 1;
    }
    if (seq[0] == '[' && seq[1] == 'D' && input->cursor_pos > 0) {
        input->cursor_pos -= 1;
        write(STDOUT_FILENO, "\033[D", 3);
        return 1;
    }
    return 0;
}

/**
 * @brief Handles the sequences of the arrow keys.
 *
 * This function processes arrow key sequences for both cursor movement
 * and history navigation.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @param seq Array of characters containing the sequence.
 * @param shell Pointer to the shell structure containing the history.
 * @return 1 if an arrow key sequence is detected and handled, 0 otherwise.
 */
static int handle_arrows(input_t *input, char seq[], shell_t *shell)
{
    int res = 0;

    if (handle_cursor(input, seq))
        return 1;
    res = handle_history(input, seq, shell);
    if (res) {
        if (res == -1) {
            write(1, "\n", 1);
            return -1;
        }
        if (input->str_input)
            input->input_len = strlen(input->str_input);
        else
            input->input_len = 0;
        input->cursor_pos = input->input_len;
        return 1;
    }
    return 0;
}

/**
 * @brief Handles the escape sequence for the Delete key.
 *
 * This function checks whether the given escape sequence corresponds
 * to the Delete key (`\e[3~`). If the sequence matches and the cursor
 * is not at the end of the input, it removes the character at the current
 * cursor position by shifting the remaining characters one position to the
 * left.
 *
 * @param seq Array containing the first two characters of the escape sequence.
 * @param tilde Character that should be `~` to complete the Delete sequence.
 * @param input Pointer to the input_t structure holding the current input
 * state.
 */
static void handle_suppr(char seq[3], char tilde, input_t *input)
{
    if (seq[0] == '[' && seq[1] == '3' &&
        read(STDIN_FILENO, &tilde, 1) == 1 &&
        tilde == '~' && input->cursor_pos < input->input_len) {
        memmove(&(input->str_input)[input->cursor_pos],
            &(input->str_input)[input->cursor_pos + 1],
            input->input_len - input->cursor_pos);
        (input->input_len)--;
        (input->str_input)[input->input_len] = '\0';
    }
}

/**
 * @brief Handles and redirects all sequences found in the user input.
 *
 * This function detects if a sequence is found, reads the sequence,
 * and redirects arrow key sequences to another function. It also handles
 * the Suppr (Delete) key sequence directly.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @param shell Pointer to the shell structure.
 * @return 1 if a sequence is detected and handled, 0 otherwise.
 */
int handle_sequences(input_t *input, shell_t *shell)
{
    char seq[3] = {'\0', '\0', '\0'};
    char tilde = '\0';
    int res = 0;

    if (input->char_input == '\033') {
        if (read(STDIN_FILENO, &seq[0], 2) != 2)
            return 0;
        res = handle_arrows(input, seq, shell);
        if (res)
            return res;
        handle_suppr(seq, tilde, input);
        return 1;
    }
    return 0;
}
