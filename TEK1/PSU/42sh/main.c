/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** main
*/

/**
 * @file main.c
 * @brief Entry point and main loop for the 42sh shell.
 *
 * This file contains the main function, the shell's main loop, and helper
 * functions to handle input, process commands,
 * and manage the shell's lifecycle.
 */

#include "meowsh.h"
#include "input.h"
#include "builtins.h"
#include "parser.h"
#include "exec.h"
#include "format.h"

/**
 * @brief Checks if a string contains only printable characters.
 *
 * This function verifies if the given string contains only printable
 * characters (ASCII values between 32 and 126), newlines, tabs, or null
 * terminators.
 *
 * @param str The string to check.
 * @return 1 if the string is printable, 0 otherwise.
 */
static int is_printable(char *str)
{
    size_t len = 0;

    if (!str)
        return 0;
    len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if ((str[i] < 32 || str[i] > 126) && str[i] != '\n' &&
            str[i] != '\t' && str[i] != '\0') {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Handles user input for the shell.
 *
 * This function retrieves input from the user, checks if it is printable,
 * adds it to the shell's history, and formats it for execution.
 *
 * @param shell Pointer to the shell structure.
 * @param input Pointer to the input string to be updated.
 * @return 0 on success, 1 on failure.
 */
static int handle_input(shell_t *shell, char **input)
{
    char *tmp = get_input(shell);

    if (!is_printable(tmp))
        return 0;
    if (tmp) {
        add_to_history(tmp, shell);
        *input = format_input(tmp, shell);
        free(tmp);
        if (!(*input))
            return 1;
    }
    return 0;
}

/**
 * @brief Reads a line of input from the user or standard input.
 *
 * This function reads a line of input from the user in interactive mode
 * or from standard input in non-interactive mode.
 *
 * @param input Pointer to the input string to be updated.
 * @param shell Pointer to the shell structure.
 * @return 1 on success, 0 on failure.
 */
int read_line(char **input, shell_t *shell)
{
    size_t len_read = 0;

    if (!isatty(0)) {
        if (getline(input, &len_read, stdin) == -1)
            return 0;
    } else {
        if (handle_input(shell, input))
            return 1;
    }
    return 1;
}

/**
 * @brief Main loop of the shell.
 *
 * This function implements the main loop of the shell, which continuously
 * reads input, parses it into commands, and executes them until the shell
 * is terminated.
 *
 * @param shell Pointer to the shell structure.
 * @return 0 on success, or an error code on failure.
 */
static int make_loop(shell_t *shell)
{
    char *input = NULL;

    while (shell->run) {
        if (!read_line(&input, shell))
            return 0;
        if (!input)
            continue;
        shell->commands = malloc(sizeof(commands_t) * 2);
        if (!shell->commands)
            continue;
        shell->commands[0] = parse_line(input);
        shell->commands[1] = NULL;
        if (shell->commands[0])
            exec_cmd(shell, shell->commands, 0);
        free(input);
        input = NULL;
        free_commands(shell->commands);
        shell->commands = NULL;
    }
    return 0;
}

/**
 * @brief Entry point of the 42sh shell.
 *
 * This function initializes the shell, loads the history, and starts the
 * main loop. It also handles cleanup and returns the shell's exit status.
 *
 * @param ac The number of command-line arguments.
 * @param av The array of command-line arguments.
 * @param envp The environment variables passed to the shell.
 * @return The shell's exit status.
 */
int main(int ac, __attribute_maybe_unused__ char **av, char **envp)
{
    shell_t *shell = NULL;
    int exit_status = 0;

    if (ac != 1) {
        fprintf(stderr, "Error: Too many arguments\n");
        return 84;
    }
    shell = init_struct(shell, envp);
    get_history(shell);
    if (!shell) {
        fprintf(stderr, "Error: Failed to initialize shell.\n");
        return 84;
    }
    make_loop(shell);
    exit_status = shell->exit_status;
    free_shell(shell);
    return exit_status;
}
