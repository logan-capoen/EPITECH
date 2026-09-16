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
 * This file contains functions to handle exceptions in case
 * of alias, unalias, which and where.
 */

#include "meowsh.h"
#include "format.h"

/**
 * @brief Checks for exceptions in an argument and ignores them.
 *
 * If the argument is among which, where, alias or unalias, skip it
 *
 * @param array The original array of arguments.
 * @param new_array The array to store processed arguments.
 * @param i The index of the current argument.
 * @param skip_after_sep A pointer to the skip parameter.
 * @return 1 if successful, -1 on error, or 0 if no exceptions are found.
 */
int is_an_exception(char **array, char **new_array, int i, int *skip_after_sep)
{
    int is_exception = 0;
    char *tmp = NULL;

    for (int j = 0; j < NB_EXCEPTIONS; j++) {
        if (strcmp(exceptions[j], array[i]) == 0) {
            is_exception = 1;
            break;
        }
    }
    if (is_exception) {
        (*skip_after_sep) = 1;
        tmp = strdup(array[i]);
        if (!tmp)
            return -1;
        new_array[i] = tmp;
    }
    return is_exception;
}

/**
 * @brief Handles exceptions and quotes for a single argument.
 *
 * This function checks if the argument is an exception or contains quotes
 * and processes it accordingly.
 *
 * @param array The original array of arguments.
 * @param new_array The array to store processed arguments.
 * @param i The index of the current argument.
 * @return 1 on error, 0 if the argument was processed, or -1 if skipped.
 */
int handle_exceptions_and_quotes(char **array,
    char **new_array, int i, int *skip_after_separator)
{
    int exception = is_an_exception(array, new_array, i, skip_after_separator);
    int quote = check_quote(array, new_array, i);

    if (exception == -1)
        return 1;
    if (exception == 1)
        return -1;
    if (quote == 1)
        return 1;
    if (!quote)
        return -1;
    return 0;
}

/**
 * @brief Checks if the argument is a separator or redirection.
 *
 * This function determines if the given argument is one of the recognized
 * separators or redirection operators.
 *
 * @param arg The argument to check.
 * @return 1 if the argument is a separator or redirection, 0 otherwise.
 */
int is_separator_or_redirection(const char *arg)
{
    const char *separators[] = {"&&", "||", "|", ";", ">", ">>", "<", "<<"};

    for (int i = 0; i < 8; i++) {
        if (strcmp(arg, separators[i]) == 0)
            return 1;
    }
    return 0;
}

/**
 * @brief Handles skipping logic for exceptions and separators.
 *
 * This function checks if the current argument should be skipped due to
 * an exception or until the next separator or redirection.
 *
 * @param array The original array of arguments.
 * @param new_array The array to store formatted arguments.
 * @param i The index of the current argument.
 * @param skip_until_separator Pointer to the skip flag.
 * @return 1 if skipping, 0 otherwise.
 */
int handle_skipping(char **array, char **new_array,
    int i, int *skip_until_separator)
{
    if (*skip_until_separator && is_separator_or_redirection(array[i])) {
        *skip_until_separator = 0;
    }
    if (*skip_until_separator) {
        new_array[i] = strdup(array[i]);
        if (!new_array[i])
            return 1;
        return 1;
    }
    return 0;
}
