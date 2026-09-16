/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** exec_cmd.c
*/

/**
 * @file exec_cmd.c
 * @brief Implementation of command execution for the 42sh shell.
 *
 * This file contains functions to handle the execution of commands, including
 * handling pipes, redirections, and built-in commands.
 */

#include "builtins.h"
#include "exec.h"
#include "error_outputs.h"
#include "input.h"

/**
 * @brief Closes all pipes used during command execution.
 *
 * @param pipes Array of pipes to close.
 * @param nb_pipes Number of pipes in the array.
 * @param i_max Maximum index of pipes to close. If set to -1, all pipes
 * in the array are closed.
 */
static void close_pipes(int **pipes, int nb_pipes, int i_max)
{
    if (!pipes)
        return;
    for (int i = 0; i < nb_pipes && (i_max == -1 || i < i_max); i++) {
        if (pipes[i][0] != -1) {
            close(pipes[i][0]);
            pipes[i][0] = -1;
        }
        if (pipes[i][1] != -1) {
            close(pipes[i][1]);
            pipes[i][1] = -1;
        }
    }
}

/**
 * @brief Reads input for a heredoc redirection.
 *
 * @param shell Pointer to the shell structure.
 * @param cmds Array of commands to execute.
 * @param i Index of the current command in the array.
 * @param heredoc Pipe used to store the heredoc input.
 * @return 1 if the heredoc delimiter is reached or an error occurs,
 * 0 otherwise.
 */
static int get_input_heredoc(shell_t *shell, commands_t **cmds, int i,
    int heredoc[2])
{
    char *input = NULL;
    size_t len_input = 0;

    if (!isatty(0) && getline(&input, &len_input, stdin) == -1)
        return 1;
    if (isatty(0))
        input = get_input(shell);
    if (!input)
        return 0;
    if (!strcmp(input, cmds[i]->heredoc))
        return 1;
    write(heredoc[1], input, strlen(input));
    write(heredoc[1], "\n", 1);
    if (input)
        free(input);
    return 0;
}

/**
 * @brief Handles the "double left redirection" (heredoc) for a command.
 *
 * This function implements the heredoc functionality, where the user provides
 * input until a specific delimiter is encountered. The input is then written
 * to a pipe and redirected to the command's standard input.
 *
 * @param shell Pointer to the shell structure.
 * @param cmds Array of commands to execute.
 * @param i Index of the current command in the array.
 */
static void handle_double_left_redirection(shell_t *shell,
    commands_t **cmds, int i)
{
    int heredoc[2] = {-1, -1};

    if (pipe(heredoc) == -1)
        return;
    while (1)
        if (get_input_heredoc(shell, cmds, i, heredoc))
            break;
    close(heredoc[1]);
    dup2(heredoc[0], STDIN_FILENO);
    close(heredoc[0]);
}

/**
 * @brief Handles input/output redirection for a specific command.
 *
 * Redirects input and output based on the command's
 * file descriptors and pipes.
 *
 * @param shell Pointer to the shell structure.
 * @param cmds Array of commands to execute.
 * @param exec_data Execution data containing pipes and other information.
 * @param i Index of the current command in the array.
 */
static void handle_redirection(shell_t *shell, commands_t **cmds,
    exec_data_t *exec_data, int i)
{
    if (i > 0 && cmds[i] && cmds[i]->separator == PIPE &&
        cmds[i]->fd_input == STDIN_FILENO)
        dup2(exec_data->pipe[i - 1][0], STDIN_FILENO);
    if (cmds[i]->fd_input != STDIN_FILENO) {
        dup2(cmds[i]->fd_input, STDIN_FILENO);
        close(cmds[i]->fd_input);
    } else if (cmds[i]->heredoc)
        handle_double_left_redirection(shell, cmds, i);
    if (cmds[i + 1] && cmds[i + 1]->separator == PIPE &&
        cmds[i]->fd_output == STDOUT_FILENO)
        dup2(exec_data->pipe[i][1], STDOUT_FILENO);
    if (cmds[i]->fd_output != STDOUT_FILENO) {
        dup2(cmds[i]->fd_output, STDOUT_FILENO);
        close(cmds[i]->fd_output);
    }
}

/**
 * @brief Checks if a command is a built-in command and executes it if true.
 *
 * @param shell Pointer to the shell structure.
 * @param cmd Pointer to the command structure.
 * @param is_fork Indicates if the command is executed in a forked process.
 * @param i Index of the built-in command in the built-in commands table.
 * @return 1 if the command is a built-in and was executed, 0 otherwise.
 */
static int check_one_built_in_cmd(shell_t *shell, commands_t *cmd,
    int is_fork, int i)
{
    if (!strcmp(tab[i].command, cmd->command[0])) {
        shell->exit_status = (tab[i].builtin_func)(shell, cmd->command,
            tab[i].local);
        if (is_fork)
            exit(shell->exit_status);
        return 1;
    }
    return 0;
}

/**
 * @brief Detects and executes a command (built-in or external).
 *
 * If the command is not found, an error message is printed,
 * and the process exits.
 *
 * @param shell Pointer to the shell structure.
 * @param cmd Pointer to the command structure.
 * @param is_fork Indicates if the command is executed in a forked process.
 */
static void detect_cmd(shell_t *shell, commands_t *cmd, int is_fork)
{
    if (!cmd->command[0])
        return;
    for (int i = 0; i < NB_BUILT_IN; i++)
        if (check_one_built_in_cmd(shell, cmd, is_fork, i))
            return;
    cmd->path = get_cmd_path(cmd->command[0], shell->env->global);
    if (!cmd->path) {
        dprintf(2, "%s: Command not found.\n", cmd->command[0]);
        exit(1);
    }
    execve(cmd->path, cmd->command, shell->env->global);
    for (int i = 0; errno_table[i].errmsg != NULL; i++)
        if (errno == errno_table[i].errnum) {
            dprintf(2, "%s: %s\n", cmd->command[0], errno_table[i].errmsg);
            exit(1);
        }
    exit(1);
}

/**
 * @brief Handles the exit status of all executed commands.
 *
 * Waits for all child processes to finish and checks for signals or errors.
 *
 * @param shell Pointer to the shell structure.
 * @param exec_data Pointer to the execution data structure.
 */
static void handle_exit_status(shell_t *shell, exec_data_t *exec_data)
{
    for (int i = 0; i < exec_data->nb_elt; i++)
        if (exec_data->pid[i] != -1 && exec_data->pid[i] != -2)
            waitpid(exec_data->pid[i], &(exec_data->status[i]), 0);
    for (int i = 0; i < exec_data->nb_elt; i++)
        if (exec_data->pid[i] != -1 && exec_data->pid[i] != -2)
            check_signal(shell, exec_data, i);
    for (int i = 0; i < exec_data->nb_elt; i++)
        exec_data->pid[i] = -1;
}

/**
 * @brief Determines if a command should be executed in a forked process.
 *
 * @param cmds Array of commands to execute.
 * @param exec_data Pointer to the execution data structure.
 * @param i Index of the current command in the array.
 * @return 1 if the command should be forked, 0 otherwise.
 */
static int get_is_fork(commands_t **cmds, exec_data_t *exec_data, int i)
{
    if (exec_data->cmd_type[i] == CMD)
        return 1;
    if ((cmds[i + 1] && cmds[i + 1]->separator == PIPE))
        return 1;
    if (exec_data->prev_depth < cmds[i]->depth &&
        (cmds[i]->command || cmds[i]->subcommands))
        return 1;
    if (!cmds[i]->command && !cmds[i]->subcommands)
        return 0;
    return 0;
}

/**
 * @brief Executes a single subcommand, handling forking and redirection.
 *
 * Determines if the command should be executed in a forked process
 * or directly.
 *
 * @param shell Pointer to the shell structure.
 * @param cmds Array of commands to execute.
 * @param exec_data Pointer to the execution data structure.
 * @param i Index of the current command in the array.
 */
static void exec_subcmd(shell_t *shell, commands_t **cmds,
    exec_data_t *exec_data, int i)
{
    int is_fork = get_is_fork(cmds, exec_data, i);
    int saved[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

    exec_data->pid[i] = is_fork ? fork() : -2;
    if (exec_data->pid[i] == -1)
        return;
    if (exec_data->pid[i] == 0 || exec_data->pid[i] == -2) {
        handle_redirection(shell, cmds, exec_data, i);
        close_pipes(exec_data->pipe, exec_data->nb_elt - 1, i);
        if (cmds[i]->command)
            detect_cmd(shell, cmds[i], is_fork);
        if (cmds[i]->subcommands)
            exec_cmd(shell, cmds[i]->subcommands, cmds[i]->depth);
        if (is_fork)
            exit(shell->exit_status);
    }
    manage_saved_fd(saved);
}

/**
 * @brief Executes a sequence of commands, handling pipes and separators.
 *
 * Initializes execution data, processes each command, and cleans up resources.
 *
 * @param shell Pointer to the shell structure.
 * @param cmds Array of commands to execute.
 * @param prev_depth Depth of the previous command in the command tree.
 */
void exec_cmd(shell_t *shell, commands_t **cmds, int prev_depth)
{
    exec_data_t exec_data = {0, NULL, NULL, NULL, NULL, prev_depth};

    if (init_exec_data(cmds, &exec_data)) {
        free_exec_data(&exec_data);
        return;
    }
    for (int i = 0; cmds[i]; i++) {
        if (i != 0 && cmds[i]->separator != PIPE) {
            close_pipes(exec_data.pipe, exec_data.nb_elt - 1, -1);
            handle_exit_status(shell, &exec_data);
        }
        if ((cmds[i]->separator == AND && shell->exit_status != 0) ||
            (cmds[i]->separator == OR && shell->exit_status == 0))
            break;
        exec_subcmd(shell, cmds, &exec_data, i);
    }
    close_pipes(exec_data.pipe, exec_data.nb_elt - 1, -1);
    handle_exit_status(shell, &exec_data);
    free_exec_data(&exec_data);
}
