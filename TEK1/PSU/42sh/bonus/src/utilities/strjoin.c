/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** strjoin.c
*/

/**
 * @file strjoin.c
 * @brief Function to concatenate two strings.
 *
 * This file contains the implementation of the `strjoin` function, which
 * concatenates two strings into a newly allocated string.
 */

#include "utilities.h"

/**
 * @brief Concatenate two strings into a new string.
 *
 * This function takes two input strings, allocates memory for a new string
 * that contains the concatenation of the two, and returns the new string.
 *
 * @param str1 The first string to concatenate.
 * @param str2 The second string to concatenate.
 * @return A dynamically allocated string containing
 * the concatenation of `str1` and `str2`,
 *         or `NULL` if memory allocation fails.
 */
char *strjoin(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *new_str = malloc(sizeof(char) * (len1 + len2 + 1));

    if (!new_str)
        return NULL;
    for (int i = 0; i < len1; i++)
        new_str[i] = str1[i];
    for (int i = 0; i < len2; i++)
        new_str[len1 + i] = str2[i];
    new_str[len1 + len2] = '\0';
    return new_str;
}
