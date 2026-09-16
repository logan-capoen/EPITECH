/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** format
*/

/**
 * @file format.c
 * @brief Functions to format and process shell input.
 *
 * This file contains functions to handle aliases, environment variables,
 * globbing, and history expansion for shell input. It processes user input
 * to prepare it for execution in the shell.
 */

#include "globbings.h"
#include "meowsh.h"
#include "builtins.h"
#include "parser.h"
#include "exec.h"
#include "format.h"

/**
 * @brief Checks if the given argument matches an alias.
 *
 * Searches the shell's alias list to see if the given argument matches
 * an alias. If a match is found, the alias is recursively resolved.
 *
 * @param arg The argument to check.
 * @param shell The shell structure containing the alias list.
 * @return 0 if no alias loop is detected, 1 otherwise.
 */
static char *check_aliases(char *arg, shell_t *shell)
{
    aliases_t *tmp = NULL;

    if (!shell->aliases)
        return NULL;
    tmp = *(shell->aliases);
    for (; tmp != NULL; tmp = tmp->next) {
        if (strcmp(arg, tmp->original) == 0 && tmp->browsed == false) {
            tmp->browsed = true;
            return check_aliases(tmp->new_name, shell);
        }
        if (strcmp(arg, tmp->original) == 0 && tmp->browsed == true) {
            dprintf(2, "Alias loop\n");
            return NULL;
        }
    }
    tmp = *(shell->aliases);
    for (; tmp != NULL; tmp = tmp->next)
        tmp->browsed = false;
    return arg;
}

/**
 * @brief Retrieves the value of an environment variable.
 *
 * This function extracts the name of an environment variable from the given
 * argument and searches for its value in the shell's global environment.
 *
 * @param arg The argument containing the environment variable (e.g., `$HOME`).
 * @param shell The shell structure containing the global environment
 * variables.
 * @param begin_index The starting index in the argument where the
 * variable name begins.
 * @return A dynamically allocated string containing the value of the
 * environment variable, or NULL if the variable is not found
 * or on memory allocation failure.
 */
static char *get_env_value(char *arg, shell_t *shell, int begin_index)
{
    char *to_analyze = NULL;
    char *to_return = NULL;

    to_analyze = strndup(arg + 1 + begin_index, strlen(arg + begin_index) -1);
    if (!to_analyze)
        return NULL;
    to_return = get_value_key(to_analyze, shell->env->global);
    free(to_analyze);
    return to_return;
}

/**
 * @brief Processes a single argument for formatting.
 *
 * Checks the given argument for aliases, environment variables, globbing
 * patterns, or history expansion and returns the processed result.
 *
 * @param arg The argument to process.
 * @param shell The shell structure containing aliases, environment variables,
 *              and history.
 * @return The processed argument, or NULL on error.
 */
static char *check_arg(char *arg, shell_t *shell)
{
    int begin_index = (arg[0] == '"');
    char *alias = check_aliases(arg, shell);

    if (!alias || strcmp(arg, alias))
        return alias ? strdup(alias) : NULL;
    if (arg[begin_index] == '$') {
        if (strcmp("$?", arg) == 0)
            return int_to_str(shell->exit_status);
        return get_env_value(arg, shell, begin_index);
    }
    if (is_gobbling(arg))
        return get_globbings(arg);
    if (arg[begin_index] == '!')
        return exec_history(shell, arg);
    return strdup(arg);
}

/**
 * @brief Checks for quotes in an argument and processes them.
 *
 * If the argument is enclosed in single quotes, it removes the quotes and
 * returns the processed string.
 *
 * @param array The original array of arguments.
 * @param new_array The array to store processed arguments.
 * @param i The index of the current argument.
 * @return 0 if successful, 1 on error, or -1 if no quotes are found.
 */
int check_quote(char **array, char **new_array, int i)
{
    if (array[i][0] == '\'' && array[i][strlen(array[i]) - 1] == '\'') {
        new_array[i] = strndup(array[i] + 1, strlen(array[i]) - 2);
        if (!new_array[i])
            return 1;
        return 0;
    }
    return -1;
}

/**
 * @brief Applies formatting to each element of the arguments array.
 *
 * Iterates over the arguments array and processes each element by applying
 * alias replacement, environment variable expansion, globbing, or history
 * expansion as required. If an exception is encountered, skips processing
 * until the next separator or redirection.
 *
 * @param shell The shell structure for command context.
 * @param new_array The array to store formatted arguments.
 * @param array The original array of arguments.
 * @return 0 on success, or 1 if an error occurs.
 */
static int loop_format(shell_t *shell, char **new_array, char **array)
{
    char *tmp = NULL;
    int result = 0;
    int skip_until_separator = 0;

    for (int i = 0; array[i] != NULL; i++) {
        if (handle_skipping(array, new_array, i, &skip_until_separator))
            continue;
        result = handle_exceptions_and_quotes(array, new_array,
            i, &skip_until_separator);
        if (result == 1)
            return 1;
        if (result == -1)
            continue;
        tmp = check_arg(array[i], shell);
        if (!tmp)
            return 1;
        new_array[i] = tmp;
    }
    return 0;
}

/**
 * @brief Formats an array of arguments.
 *
 * Processes each argument in the given array, applying alias replacement,
 * environment variable expansion, globbing, and history expansion as needed.
 *
 * @param array The array of arguments to format.
 * @param shell The shell structure containing aliases, environment variables,
 *              and history.
 * @param len_array The length of the array.
 * @param to_format An array of flags indicating whether each argument should
 *                  be formatted.
 * @return A newly allocated array of formatted arguments, or NULL on error.
 */
static char **get_formated_input(char **array, shell_t *shell, int len_array)
{
    char **new_array = malloc((len_array + 1) * sizeof(char *));

    if (!new_array)
        return NULL;
    for (int i = 0; i < len_array + 1; i++)
        new_array[i] = NULL;
    if (loop_format(shell, new_array, array) == 1) {
        free_array(new_array);
        return NULL;
    }
    return new_array;
}

/**
 * @brief Creates a formatted input string from an array of arguments.
 *
 * Processes the array of arguments, applies formatting, and concatenates
 * the results into a single formatted string.
 *
 * @param array_space The array of arguments split by spaces.
 * @param shell The shell structure containing aliases, environment variables,
 *              and history.
 * @param len_array The length of the array.
 * @param to_format An array of flags indicating whether each argument should
 *                  be formatted.
 * @return A newly allocated formatted string, or NULL on error.
 */
static char *create_formated_input(char **array_space, shell_t *shell,
    int len_array)
{
    char **new_array = get_formated_input(array_space, shell, len_array);
    char *formated_input = NULL;

    if (!new_array) {
        free_array(array_space);
        return NULL;
    }
    formated_input = create_concat_array(new_array);
    free_array(array_space);
    free_array(new_array);
    return formated_input;
}

/**
 * @brief Formats the input string for the shell.
 *
 * Splits the input string into arguments, processes each argument for aliases,
 * environment variables, globbing, and history expansion, and concatenates
 * the results into a single formatted string.
 *
 * @param input The input string to format.
 * @param shell The shell structure containing aliases, environment variables,
 *              and history.
 * @return A newly allocated string containing the formatted input, or NULL
 *         on error.
 */
char *format_input(char *input, shell_t *shell)
{
    char **array_space = NULL;
    int len_array = 0;
    char *new_str = NULL;

    if (!input)
        return NULL;
    new_str = add_spaces_around_operators(input);
    if (!new_str)
        return NULL;
    array_space = my_str_to_word_array(new_str, " ");
    free(new_str);
    if (!array_space)
        return NULL;
    for (; array_space[len_array] != NULL; len_array++);
    return create_formated_input(array_space, shell, len_array);
}
