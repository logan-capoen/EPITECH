/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** manage_exec_data.c
*/

/**
 * @file manage_exec_data.c
 * @brief Manages the initialization, cleanup, and handling of execution data.
 *
 * This file contains functions to initialize and free the execution data
 * structure, manage pipes, and restore saved file descriptors.
 */

#include "exec.h"

static int init_pipe(exec_data_t *exec_data)
{
    if (exec_data->nb_elt < 2) {
        exec_data->pipe = NULL;
        return 0;
    }
    exec_data->pipe = malloc(sizeof(int[2]) * (exec_data->nb_elt - 1));
    if (!exec_data->pipe)
        return 1;
    for (int i = 0; i < exec_data->nb_elt - 1; i++)
        exec_data->pipe[i] = NULL;
    for (int i = 0; i < exec_data->nb_elt - 1; i++) {
        exec_data->pipe[i] = malloc(sizeof(int) * 2);
        if (!exec_data->pipe[i] || pipe(exec_data->pipe[i]) == -1)
            return 1;
    }
    return 0;
}

/**
 * @brief Initializes the execution data structure.
 *
 * Allocates and initializes the necessary fields in the execution data
 * structure, including pipes, process IDs, statuses, and command types.
 *
 * @param cmds Array of commands to execute.
 * @param exec_data Pointer to the execution data structure.
 * @return 0 on success, 1 on failure.
 */
int init_exec_data(commands_t **cmds, exec_data_t *exec_data)
{
    for (; cmds && cmds[exec_data->nb_elt]; exec_data->nb_elt++);
    if (init_pipe(exec_data))
        return 1;
    exec_data->pid = malloc(sizeof(int) * exec_data->nb_elt);
    if (!exec_data->pid)
        return 1;
    for (int i = 0; i < exec_data->nb_elt; i++)
        exec_data->pid[i] = -1;
    exec_data->status = malloc(sizeof(int) * exec_data->nb_elt);
    if (!exec_data->status)
        return 1;
    for (int i = 0; i < exec_data->nb_elt; i++)
        exec_data->status[i] = 0;
    exec_data->cmd_type = malloc(sizeof(int) * exec_data->nb_elt);
    if (!exec_data->cmd_type)
        return 1;
    for (int i = 0; i < exec_data->nb_elt; i++)
        exec_data->cmd_type[i] = get_cmd_type(cmds[i]);
    return 0;
}

/**
 * @brief Frees the memory allocated for the execution data structure.
 *
 * Cleans up all dynamically allocated memory in the execution data structure,
 * including pipes, process IDs, statuses, and command types.
 *
 * @param exec_data Pointer to the execution data structure.
 */
void free_exec_data(exec_data_t *exec_data)
{
    for (int i = 0; exec_data->pipe && i < exec_data->nb_elt - 1
        && exec_data->pipe[i]
        ; i++)
        free(exec_data->pipe[i]);
    if (exec_data->pipe)
        free(exec_data->pipe);
    if (exec_data->pid)
        free(exec_data->pid);
    if (exec_data->status)
        free(exec_data->status);
    if (exec_data->cmd_type)
        free(exec_data->cmd_type);
}

/**
 * @brief Restores the saved file descriptors for standard input and output.
 *
 * Restores the original file descriptors for `STDIN_FILENO` and
 * `STDOUT_FILENO` and closes the saved file descriptors.
 *
 * @param saved Array containing the saved file descriptors for
 * stdin and stdout.
 */
void manage_saved_fd(int saved[2])
{
    dup2(saved[0], STDIN_FILENO);
    dup2(saved[1], STDOUT_FILENO);
    close(saved[0]);
    close(saved[1]);
}
