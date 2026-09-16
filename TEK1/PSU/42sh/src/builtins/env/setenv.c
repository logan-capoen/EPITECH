/*
** EPITECH PROJECT, 2025
** 42shell
** File description:
** setenv
*/

/**
 * @file setenv.c
 * @brief Implementation of the `setenv` builtin command.
 *
 * This file contains all the functions required to handle the `setenv`
 * command, which is used to set or modify environment variables in the shell.
 */


#include "builtins.h"

/**
 * @brief Checks if a variable name is valid.
 *
 * This function verifies that the variable name starts with a letter
 * or an underscore and contains only alphanumeric characters, underscores,
 * or dots.
 *
 * @param var The variable name to check.
 * @return 1 if the variable name is valid, 0 otherwise.
 */
int is_a_good_var(char *var)
{
    if (!var || !var[0])
        return 0;
    for (int i = 0; var && var[i]; i++) {
        if (var[i] && i == 0 && (var[i] < 65 || var[i] > 90)
            && (var[i] < 97 || var[i] > 122) && var[i] != '_') {
            write(2, "setenv: Variable name must begin with a letter.\n", 48);
            return 0;
        }
        if (var[i] && i != 0 && (var[i] < 65 || var[i] > 90)
            && (var[i] < 97 || var[i] > 122) && (var[i] < 48 || var[i] > 57)
            && var[i] != '_' && var[i] != '.') {
            write(2, "setenv: Variable name must contain "
            "alphanumeric characters.\n", 60);
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Constructs an environment variable assignment string.
 *
 * This function creates a string in the format `VAR=VALUE` based on the
 * provided command arguments.
 *
 * @param command The command arguments, where `command[1]` is the variable
 *                name and `command[2]` is the value (optional).
 * @return A dynamically allocated string containing the assignment, or NULL
 *         if memory allocation fails.
 */
char *get_line_env(char **command)
{
    size_t len1 = strlen(command[1]);
    size_t len2 = command[2] ? strlen(command[2]) : 0;
    char *line = calloc(len1 + len2 + 2, sizeof(char));

    if (!line)
        return NULL;
    strcpy(line, command[1]);
    strcat(line, "=");
    if (command[2])
        strcat(line, command[2]);
    return line;
}

/**
 * @brief Adds a new environment variable to the environment.
 *
 * This function appends a new variable to the environment array.
 *
 * @param env A pointer to the environment array.
 * @param set The variable assignment string to add (e.g., `VAR=VALUE`).
 * @return 0 on success, 1 on failure.
 */
int add_env(char ***env, char *set)
{
    if (!env)
        return 1;
    if (add_elt(env, set))
        return 1;
    return 0;
}

/**
 * @brief Modifies an existing environment variable or adds a new one.
 *
 * This function searches for an existing variable in the environment and
 * updates its value. If the variable does not exist, it adds a new one.
 *
 * @param env A pointer to the environment array.
 * @param command The command arguments, where `command[1]` is the variable
 *                name and `command[2]` is the value (optional).
 * @return 0 on success, 1 on failure.
 */
int change_env(char ***env, char **command)
{
    char *line = get_line_env(command);

    if (!line)
        return 1;
    for (int i = 0; *env && (*env)[i]; i++) {
        if (!strncmp((*env)[i], command[1],
            strlen(command[1])) &&
            (*env)[i][strlen(command[1])] == '=') {
            free((*env)[i]);
            (*env)[i] = line;
            return 0;
        }
    }
    return add_env(env, line);
}

/**
 * @brief Handles the `setenv` builtin command.
 *
 * This function implements the logic for the `setenv` command, which sets or
 * modifies environment variables. It validates the input, checks for errors,
 * and updates the appropriate environment (local or global).
 *
 * @param shell The shell structure containing the environment.
 * @param command The command arguments, where `command[1]` is the variable
 *                name and `command[2]` is the value (optional).
 * @param local A flag indicating whether to modify the local or global
 *              environment.
 * @return The correct exit status.
 */
int my_setenv(shell_t *shell, char **command, int local)
{
    char ***actual_env = (local) ? &(shell->env->local) :
        &(shell->env->global);

    if (!shell || !command)
        return 1;
    if (command[1] == NULL)
        return my_env(shell, command, local);
    if (command[2] != NULL && command[3] != NULL) {
        write(2, "setenv: Too many arguments.\n", 28);
        return 1;
    }
    if (!is_a_good_var(command[1]))
        return 1;
    else if (change_env(actual_env, command))
        return 1;
    return 0;
}
