/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** unsetenv
*/

/**
 * @file unsetenv.c
 * @brief Functions to handle the `unsetenv` builtin command.
 *
 * This file contains all the functions needed to execute the
 * `unsetenv` builtin command, which removes environment variables
 * from the shell's environment.
 */

#include "builtins.h"

/**
 * @brief Gets the length of an environment array.
 *
 * This function calculates the number of elements in the given
 * environment array.
 *
 * @param array The environment array.
 * @return int The number of elements in the array.
 */
static int get_array_len(char **array)
{
    int len = 0;

    for (; array && array[len]; len++);
    return len;
}

/**
 * @brief Deletes a variable from the environment array.
 *
 * This function removes the element at the given index from the
 * environment array. A new array (without that element) is created,
 * the old array is freed, and the pointer is updated.
 *
 * @param env Pointer to the environment array.
 * @param index Index of the variable to delete.
 * @return int Returns 1 if a variable was deleted, or 0 if the index
 * is invalid.
 */
static int delete_variable(char ***env, int index)
{
    int len = get_array_len(*env);
    char **tmp_env = index < len ? calloc(len, sizeof(char *)) : NULL;

    if (!tmp_env)
        return 1;
    for (int i = 0; i < len && (*env)[i]; i++)
        if (i == index)
            free((*env)[i]);
        else
            tmp_env[i - (i > index)] = (*env)[i];
    free(*env);
    *env = tmp_env;
    return 0;
}

/**
 * @brief Searches the environment array for a variable to delete.
 *
 * This function iterates over the environment array looking for a
 * variable that matches the specified name in @p to_delete. If a
 * matching variable is found (by comparing the name before '='), it
 * deletes the variable.
 *
 * @param env Pointer to the environment array.
 * @param to_delete Name of the variable to remove.
 * @return int Returns 1 if the variable was found and deleted,
 * otherwise 0.
 */
static int search_to_delete(char ***env, char *to_delete)
{
    size_t len = strlen(to_delete);

    for (int i = 0; (*env)[i]; i++) {
        if (!strncmp((*env)[i], to_delete, len) &&
            (*env)[i][len] == '=')
            return delete_variable(env, i);
    }
    return 0;
}

/**
 * @brief Unsets environment variables.
 *
 * This function implements the `unsetenv` builtin. It removes each
 * environment variable provided in the command arguments. If no
 * variable is given, it writes an error message and sets the shell's
 * exit status.
 *
 * @param sh Pointer to the shell structure.
 * @param command Array of command arguments.
 * @param local Non-zero for the local environment, zero for global.
 * @return int Returns 1 if an error occurred, otherwise 0.
 */
int my_unsetenv(shell_t *sh, char **command, int local)
{
    int result = 0;
    char ***actual_env = (local) ? &(sh->env->local) :
        &(sh->env->global);

    sh->exit_status = 0;
    if (command && command[0] && !command[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return 1;
    }
    for (int i = 1; command && command[i]; i++)
        if (search_to_delete(actual_env, command[i]))
            result = 1;
    return result;
}

/**
 * @brief Adds a new element to the environment array.
 *
 * This function appends a new environment variable to the given
 * environment array.
 *
 * @param array Pointer to the environment array.
 * @param elt The environment variable to add.
 * @return int Returns 0 on success, or 1 on failure.
 */
int add_elt(char ***array, char *elt)
{
    int len_array = 0;
    char **array_tmp = NULL;

    if (!elt)
        return 1;
    len_array = get_array_len(*array);
    array_tmp = malloc(sizeof(char *) * (len_array + 2));
    if (!array_tmp)
        return 1;
    for (int i = 0; (*array)[i]; i++)
        array_tmp[i] = (*array)[i];
    array_tmp[len_array] = elt;
    array_tmp[len_array + 1] = NULL;
    free(*array);
    *array = array_tmp;
    return 0;
}
