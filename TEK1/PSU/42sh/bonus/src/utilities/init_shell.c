/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** init_shell.c
*/

/**
 * @file init_shell.c
 * @brief Initialization functions for the shell program.
 *
 * This file contains the implementation of functions responsible for
 * initializing the shell structure and its components, including commands,
 * environment variables, aliases, and command history.
 *
 * The primary function in this file is `init_struct`, which allocates memory
 * for the shell structure and initializes its fields based on the provided
 * environment variables.
 */

#include "utilities.h"
#include "builtins.h"

/**
 * @brief Initialize shell structure default values.
 *
 * This function sets the initial values for several members of the
 * shell_t structure: it initializes the commands and aliases pointers,
 * duplicates the global environment, allocates memory for the local
 * environment, sets the history size to 0, retrieves the current working
 * directory, and sets the exit status and run flag.
 *
 * @param shell A pointer to the shell structure.
 * @param envp  An array of environment variable strings.
 */
static void init_defaults(shell_t *shell, char **envp)
{
    *(shell->aliases) = NULL;
    shell->env->global = dup_array(envp);
    shell->env->local = calloc(1, sizeof(env_t *));
    if (!shell->env->global || !shell->env->local)
        return;
    shell->history_size = 0;
    shell->owd = malloc(sizeof(char) * 512);
    if (!shell->owd)
        return;
    getcwd(shell->owd, 512);
    shell->exit_status = 0;
    shell->run = true;
}

/**
 * @brief Initializes a shell structure.
 *
 * This function allocates memory for a shell_t structure and its associated
 * components, including commands, environment variables, aliases, and history.
 * It also initializes the shell's working directory and exit status.
 *
 * @param shell A pointer to a shell_t structure. If NULL, a new structure
 *              will be allocated and initialized.
 * @param envp An array of environment variable strings. This will be used
 *              to populate the global environment variables in the shell.
 *
 * @return A pointer to the initialized shell_t structure on success, or
 *         NULL if memory allocation fails or if any of the components
 *         cannot be initialized.
 *
 * @note The caller is responsible for freeing the allocated memory for the
 *       shell_t structure and its components when they are no longer needed.
 */
shell_t *init_struct(shell_t *shell, char **envp)
{
    shell = malloc(sizeof(shell_t));
    if (!shell)
        return NULL;
    shell->commands = NULL;
    shell->history = NULL;
    shell->env = malloc(sizeof(env_t));
    shell->aliases = malloc(sizeof(aliases_t *));
    if (!shell->aliases || !shell->env)
        return NULL;
    init_defaults(shell, envp);
    return shell;
}
