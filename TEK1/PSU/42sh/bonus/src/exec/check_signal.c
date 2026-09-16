/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** check_signal.c
*/

/**
 * @file check_signal.c
 * @brief Functions to handle and display process signals.
 */

#include "exec.h"

/**
 * @brief Displays the signal that caused a process to terminate.
 *
 * This function checks if a process was terminated by a signal. If so, it
 * retrieves the signal number and its corresponding string representation
 * using.
 *
 * @param status The status of the terminated process.
 */
static void display_signal(int status)
{
    int signal_nb = 0;
    char *signal_str = NULL;

    if (WIFSIGNALED(status)) {
        signal_nb = WTERMSIG(status);
        if (signal_nb == 9 || signal_nb == 18 || signal_nb == 19 ||
            signal_nb == 21 || signal_nb == 22)
            return;
        signal_str = strsignal(signal_nb);
        if (!signal_str)
            return;
        if (signal_nb == 8)
            write(2, "Floating exception", 19);
        else
            write(2, signal_str, strlen(signal_str));
        if (WCOREDUMP(status))
            write(2, " (core dumped)", 15);
        write(2, "\n", 1);
    }
}

/**
 * @brief Updates the shell's exit status based on the process termination
 * status.
 *
 * If the process was a built-in command, it directly sets the shell's exit
 * status to the process's exit code. Otherwise, it updates the exit status
 * based on whether the process exited normally or was terminated by a signal.
 *
 * @param shell The shell structure containing the exit status.
 * @param status The status of the terminated process.
 * @param is_built_cmd A boolean indicating if the process was a built-in
 * command.
 */
void check_signal(shell_t *shell, exec_data_t *exec_data, int i)
{
    if (exec_data->cmd_type[i] == BUILT_CMD)
        shell->exit_status = WEXITSTATUS(exec_data->status[i]);
    else {
        if (WIFEXITED(exec_data->status[i]))
            shell->exit_status = WEXITSTATUS(exec_data->status[i]);
        if (WIFSIGNALED(exec_data->status[i]))
            shell->exit_status = 128 + WTERMSIG(exec_data->status[i]);
        display_signal(exec_data->status[i]);
    }
}
