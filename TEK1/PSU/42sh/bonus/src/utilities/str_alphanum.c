/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** str_alphanum
*/

/**
 * @file str_alphanum.c
 * @brief Utility function to check if a string is alphanumeric.
 *
 * This file contains the implementation of the `str_isalphanum` function,
 * which verifies if a given string contains only alphanumeric characters.
 */

#include "builtins.h"

/**
 * @brief Checks if a string is alphanumeric.
 *
 * This function iterates through the input string and checks if all characters
 * are alphanumeric (letters or digits). If any character is not alphanumeric,
 * the function returns `0`. Otherwise, it returns `1`.
 *
 * @param str The input string to check.
 * @return 1 if the string is alphanumeric, 0 otherwise.
 */
int str_isalphanum(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (!isalnum(str[i]))
            return 0;
    }
    return 1;
}
