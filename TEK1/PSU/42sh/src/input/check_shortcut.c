/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** check_shortcut.c
*/

/**
 * @file check_shortcut.c
 * @brief Handles keyboard shortcuts for cursor movement and screen clearing.
 *
 * This file contains the implementation of functions that process specific
 * keyboard shortcuts such as `CTRL-A`, `CTRL-E`, `CTRL-B`, `CTRL-F`, `CTRL-T`,
 * and `CTRL-L`. These shortcuts allow the user to navigate within the input
 * line, transpose characters, or clear the screen.
 */

#include "input.h"

/**
 * @brief Moves the cursor backward or forward by one character.
 *
 * This function handles the `CTRL-B` and `CTRL-F` shortcuts:
 * - `CTRL-B` (ASCII 2): Moves the cursor backward by one character.
 * - `CTRL-F` (ASCII 6): Moves the cursor forward by one character.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 */
static void skip_char(input_t *input)
{
    if (input->char_input == 2 && input->cursor_pos > 0)
        input->cursor_pos--;
    if (input->char_input == 6 && input->cursor_pos < input->input_len)
        input->cursor_pos++;
}

/**
 * @brief Transposes the last two characters in the input string.
 *
 * This function handles the `CTRL-T` shortcut:
 * - `CTRL-T` (ASCII 20): Swaps the last two characters in the input string
 *   if the input length is at least 2.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 */
static void transpose(input_t *input)
{
    char transpose = '\0';

    if (input->char_input == 20 && input->cursor_pos + 1 >= 2) {
        if (input->cursor_pos == input->input_len) {
            transpose = input->str_input[input->cursor_pos - 1];
            input->str_input[input->cursor_pos - 1] =
            input->str_input[input->cursor_pos - 2];
            input->str_input[input->cursor_pos - 2] = transpose;
        } else {
            transpose = input->str_input[input->cursor_pos];
            input->str_input[input->cursor_pos] =
            input->str_input[input->cursor_pos - 1];
            input->str_input[input->cursor_pos - 1] = transpose;
        }
        if (input->cursor_pos < input->input_len)
                input->cursor_pos++;
    }
}

/**
 * @brief Moves the cursor to the beginning or end of the input line.
 *
 * This function handles the `CTRL-A` and `CTRL-E` shortcuts:
 * - `CTRL-A` (ASCII 1): Moves the cursor to the beginning of the line.
 * - `CTRL-E` (ASCII 5): Moves the cursor to the end of the line.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 */
static void go_to_end_or_start(input_t *input)
{
    if (input->char_input == 1)
        input->cursor_pos = 0;
    if (input->char_input == 5)
        input->cursor_pos = input->input_len;
}

/**
 * @brief Clears the terminal screen.
 *
 * This function handles the `CTRL-L` shortcut:
 * - `CTRL-L` (ASCII 12): Clears the terminal screen and moves the cursor
 *   to the top-left corner.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 */
static void clear_screen(input_t *input)
{
    if (input->char_input == 12)
        write(STDOUT_FILENO, "\033[2J\033[H", 7);
}

/**
 * @brief Handles keyboard shortcuts for cursor movement and screen clearing.
 *
 * This function checks for specific keyboard shortcuts:
 * - `CTRL-A` (ASCII 1): Moves the cursor to the beginning of the line.
 * - `CTRL-E` (ASCII 5): Moves the cursor to the end of the line.
 * - `CTRL-B` (ASCII 2): Moves the cursor backward by one character.
 * - `CTRL-F` (ASCII 6): Moves the cursor forward by one character.
 * - `CTRL-T` (ASCII 20): Swaps the last two characters in the input string.
 * - `CTRL-L` (ASCII 12): Clears the terminal screen and resets the cursor.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @return Always returns 0.
 */
int check_shortcut(input_t *input)
{
    go_to_end_or_start(input);
    transpose(input);
    skip_char(input);
    clear_screen(input);
    return 0;
}
