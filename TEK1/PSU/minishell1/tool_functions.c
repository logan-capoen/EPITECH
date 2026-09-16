/*
** EPITECH PROJECT, 2025
** tool_functions
** File description:
** tool_functions
*/

#include <unistd.h>
#include "minishell1.h"
#include "my.h"

/**
 * @brief Checks if a token is NULL and duplicates it if not.
 *
 * @param token The token to check.
 * @return A duplicated string if the token is not NULL, otherwise NULL.
 */
char *is_null(char *token)
{
    if (token != NULL)
        return my_strdup(token);
    return NULL;
}

/**
 * @brief Checks if the input has the correct number of arguments.
 *
 * @param input The input string.
 * @param n The expected number of arguments.
 * @return 1 if the number of arguments matches, otherwise 0.
 */
int check_parsing(char *input, int n)
{
    char **arr = my_str_to_word_array(input, ' ');
    int len = 0;

    for (; arr[len] != NULL; len++);
    free_arr(arr);
    return len == n;
}

int is_letter(char chara)
{
    if (chara >= 'a' && chara <= 'z')
        return 1;
    if (chara >= 'A' && chara <= 'Z')
        return 1;
    if (chara == '_' || chara == '.')
        return 1;
    return 0;
}

int is_alpha(char chara)
{
    if (is_letter(chara))
        return 1;
    if (chara >= '0' && chara <= '9')
        return 1;
    return 0;
}
