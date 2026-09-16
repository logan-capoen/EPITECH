/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_getenv
*/

/**
 * @file my_getenv.c
 * @brief Retrieves the value of an environment variable.
 *
 * This file contains the implementation of a function to search for a specific
 * key in the environment variables and return its value.
 */

#include "builtins.h"

/**
 * @brief Retrieves the value associated with a given key in the environment.
 *
 * This function iterates through the environment variables to find a key that
 * matches the specified key and returns its value.
 *
 * @param key The key to search for in the environment variables.
 * @param env The array of environment variables.
 * @return A pointer to the value associated with the key, or NULL if the key
 *         is not found.
 */
char *get_value_key(char *key, char **env)
{
    size_t len_cmd = 0;

    if (!key || !env)
        return NULL;
    len_cmd = strlen(key);
    for (int i = 0; env[i]; i++)
        if (len_cmd < strlen(env[i]) && !strncmp(env[i], key, len_cmd) &&
            env[i][len_cmd] == '=')
            return strdup(&(env[i][len_cmd + 1]));
    return NULL;
}
