/*
** EPITECH PROJECT, 2025
** redirections
** File description:
** open the file descriptors for the inputs and outputs
*/

/**
 * @file open_fd_redirections.c
 * @brief Creates the fd for input and output based off redirections.
 */

#include "parser.h"

/**
 * @brief Opens the input file descriptor for a command.
 *
 * @param cmd Pointer to the command structure (commands_t).
 * @param filename The path to the file to open as input.
 * @return The new input file descriptor, or -1 on failure.
 */
int open_input_fd(commands_t *cmd, char *filename)
{
    int fd_in = 0;

    if (cmd->fd_input != -1 && cmd->fd_input != STDIN_FILENO)
        close(cmd->fd_input);
    fd_in = open(filename, O_RDONLY);
    return fd_in;
}

/**
 * @brief Opens the output file descriptor for a command.
 *
 * @param cmd Pointer to the command structure (commands_t).
 * @param truncate If true, the file is truncated; if false, data is appended.
 * @param filename The path to the file to open as output.
 * @return The new output file descriptor, or -1 on failure.
 */
int open_output_fd(commands_t *cmd, bool truncate, char *filename)
{
    int flags = 0;
    int fd_out = 0;

    if (cmd->fd_output != -1 && cmd->fd_output != STDOUT_FILENO)
        close(cmd->fd_output);
    flags = O_WRONLY | O_CREAT | (truncate ? O_TRUNC : O_APPEND);
    fd_out = open(filename, flags, 0644);
    return fd_out;
}
