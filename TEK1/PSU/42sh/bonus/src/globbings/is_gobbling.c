/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_gobbling
*/

/**
 * @file is_gobbling.c
 * @brief Function to check for globbing patterns in a string.
 *
 * This file contains the implementation of the `is_gobbling` function,
 * which determines if a given string contains globbing characters such as
 * `*`, `?`, `[`, or `]`.
 */

#include "globbings.h"

/**
 * @brief Checks if a string contains globbing characters.
 *
 * This function iterates through the input string and checks for the presence
 * of globbing characters (`*`, `?`, `[`, `]`). If any of these characters are
 * found, the function returns `1`. Otherwise, it returns `0`.
 *
 * @param str The input string to check for globbing characters.
 * @return 1 if the string contains globbing characters, 0 otherwise.
 */
int is_gobbling(char *str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == ']')
            return 1;
    }
    return 0;
}
