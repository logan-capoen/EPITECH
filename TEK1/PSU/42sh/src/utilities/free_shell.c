/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** free_shell.c
*/

/**
 * @file free_shell.c
 * @brief Functions to free memory allocated for the shell structure.
 *
 * This file contains functions to free all dynamically allocated memory
 * associated with the `shell_t` structure, including commands, environment
 * variables, aliases, and history.
 */

#include "utilities.h"

/**
 * @brief Frees memory allocated for an array of commands.
 *
 * This function iterates through an array of `commands_t` structures and
 * frees all associated memory, including file descriptors, heredoc strings,
 * paths, commands, and subcommands.
 *
 * @param cmds Double pointer to the array of commands to free.
 */
void free_commands(commands_t **cmds)
{
    if (!cmds)
        return;
    for (int i = 0; cmds[i]; i++) {
        if (cmds[i]->fd_input != STDIN_FILENO)
            close(cmds[i]->fd_input);
        if (cmds[i]->fd_output != STDOUT_FILENO)
            close(cmds[i]->fd_output);
        if (cmds[i]->heredoc)
            free(cmds[i]->heredoc);
        if (cmds[i]->path)
            free(cmds[i]->path);
        if (cmds[i]->command)
            free_array(cmds[i]->command);
        if (cmds[i]->subcommands)
            free_commands(cmds[i]->subcommands);
        if (cmds[i])
            free(cmds[i]);
    }
    free(cmds);
}

/**
 * @brief Frees memory allocated for the shell's environment variables.
 *
 * This function frees both global and local environment variable arrays,
 * as well as the `env_t` structure itself.
 *
 * @param shell Pointer to the shell structure containing the environment.
 */
static void free_env(shell_t *shell)
{
    if (shell->env) {
        if (shell->env->global)
            free_array(shell->env->global);
        if (shell->env->local)
            free_array(shell->env->local);
        free(shell->env);
    }
}

/**
 * @brief Frees memory allocated for the shell's aliases.
 *
 * This function iterates through the linked list of aliases and frees
 * each alias structure, including the original and new name strings.
 *
 * @param shell Pointer to the shell structure containing the aliases.
 */
void free_aliases(shell_t *shell)
{
    aliases_t *current = NULL;
    aliases_t *next = NULL;

    current = *shell->aliases;
    while (current) {
        next = current->next;
        free(current->original);
        free(current->new_name);
        free(current);
        current = next;
    }
    free(shell->aliases);
}

/**
 * @brief Frees all memory allocated for the shell structure.
 *
 * This function frees all dynamically allocated memory associated with the
 * `shell_t` structure, including commands, environment variables, aliases,
 * history, and the old working directory.
 *
 * @param shell Pointer to the shell structure to free.
 */
void free_shell(shell_t *shell)
{
    if (!shell)
        return;
    free_commands(shell->commands);
    free_env(shell);
    if (shell->aliases)
        free_aliases(shell);
    if (shell->history)
        free_array(shell->history);
    if (shell->owd)
        free(shell->owd);
    free(shell);
}
