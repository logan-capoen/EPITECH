/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** get_input.c
*/

/**
 * @file get_input.c
 * @brief Implementation of the input handling for the Meowsh shell.
 *
 * This file contains functions to handle user input in raw mode, including
 * cursor movement, character insertion, deletion, and line display.
 */

#include "input.h"
#include "builtins.h"

/**
 * @brief Configures the terminal in raw mode.
 *
 * This function sets up the terminal to operate in raw mode, disabling
 * canonical input processing and echoing.
 *
 * @param original Pointer to the original terminal settings(to restore later).
 * @param raw Pointer to the terminal settings to configure for raw mode.
 * @return 0 on success, 1 on failure.
 */
static int setup_termios_struct(struct termios *original, struct termios *raw)
{
    if (tcgetattr(STDIN_FILENO, original) == -1) {
        perror("tcgetattr");
        return 1;
    }
    *raw = *original;
    raw->c_lflag &= ~(ECHO | ICANON | ISIG);
    raw->c_iflag &= ~(IXON | INLCR);
    raw->c_cc[VMIN] = 1;
    raw->c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, raw) == -1) {
        perror("tcsetattr");
        return 1;
    }
    return 0;
}

/**
 * @brief Checks if the input character signals the end of input.
 *
 * This function checks if the input character is one of the end-of-input
 * characters (Ctrl+D, Enter, or newline).
 *
 * @param char_input The character to check.
 * @return 1 if the input signals the end of input, 0 otherwise.
 */
static int check_end_input(char char_input)
{
    if (char_input == 4 || char_input == '\r' || char_input == '\n') {
        write(STDOUT_FILENO, "\n", 1);
        return 1;
    }
    return 0;
}

/**
 * @brief Writes the pwd in color before getting input
 *
 * If the pwd doesn't exist in the env, just displays the basic input
 *
 * @param shell The struct containing all the data about the shell
 */
static void write_pwd(shell_t *shell)
{
    char *pwd = get_value_key("PWD", shell->env->global);

    if (pwd) {
        write(STDOUT_FILENO, PURPLE, 12);
        write(STDOUT_FILENO, pwd, strlen(pwd));
        write(STDOUT_FILENO, RESET, 4);
        write(STDOUT_FILENO, " $> ", 4);
        free(pwd);
    } else {
        write(STDOUT_FILENO, "$> ", 3);
    }
}

/**
 * @brief Displays the current input line in the terminal.
 *
 * This function clears the current line in the terminal, writes the input
 * string, and repositions the cursor to the correct position.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @param shell The struct containing all the data about the shell
 * @return 0 on success.
 */
int display_line(input_t *input, shell_t *shell)
{
    write(STDOUT_FILENO, "\033[2K\r", 5);
    write_pwd(shell);
    if (input->str_input)
        write(STDOUT_FILENO, input->str_input, input->input_len);
    for (size_t i = 0; i < input->input_len - input->cursor_pos; i++)
        write(STDOUT_FILENO, "\033[D", 3);
    return 0;
}

/**
 * @brief Processes the input loop.
 *
 * This function handles the main input loop, reading characters from the user,
 * managing the input, and updating the display.
 *
 * @param input Pointer to the input structure containing the current input
 *              string, its length, and the cursor position.
 * @param shell The struct containing all the data about the shell
 * @return 0 on success, 1 on error.
 */
static int make_loop_input(input_t *input, shell_t *shell)
{
    while (read(STDIN_FILENO, &(input->char_input), 1) == 1) {
        if (check_end_input(input->char_input))
            break;
        check_shortcut(input);
        if (manage_input(input, shell)) {
            free_input(input);
            return 1;
        }
        display_line(input, shell);
    }
    return 0;
}

/**
 * @brief Reads and processes user input in raw mode.
 *
 * This function reads user input character by character, processes special
 * keys, and updates the input string and cursor position accordingly.
 *
 * @param shell Pointer to the shell structure (not used in this function but
 *              kept for consistency with the shell's architecture).
 * @return A dynamically allocated string containing the user input, or NULL
 *         on error.
 */
char *get_input(shell_t *shell)
{
    input_t *input = NULL;
    struct termios original = {0};
    struct termios raw = {0};
    char *final_str = NULL;

    if (setup_termios_struct(&original, &raw))
        return NULL;
    if (init_input(&input, shell))
        return NULL;
    write_pwd(shell);
    if (make_loop_input(input, shell))
        return NULL;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original)) {
        free_input(input);
        return NULL;
    }
    if (input->str_input)
        final_str = strdup(input->str_input);
    free_input(input);
    return final_str;
}
