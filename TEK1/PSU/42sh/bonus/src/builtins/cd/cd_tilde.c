/*
** EPITECH PROJECT, 2025
** cd_functions
** File description:
** cd tilde
*/

/**
 * @file cd_tilde.c
 * @brief Functions to handle the tilde (~) for the `cd` command.
 *
 * This file contains all the necessary functions to expand and handle
 * the tilde (~) in the `cd` command.
 */

#include "builtins.h"

/**
 * @brief Expands a user's home directory and appends a relative path.
 *
 * This function checks if the given user home directory exists and is valid.
 * If valid, it concatenates the home directory with the relative path.
 *
 * @param user_home The home directory of the user.
 * @param relative_path The relative path to append to the home directory.
 * @return A newly allocated string containing the expanded path, or NULL
 *         on error.
 */
static char *get_expanded_path(char *user_home, char *relative_path)
{
    struct stat sb = {0};
    char *expanded = NULL;

    if (stat(user_home, &sb) != 0 || !S_ISDIR(sb.st_mode)) {
        dprintf(2, "Unknown user: %s.\n", user_home);
        return NULL;
    }
    expanded = malloc(strlen(user_home) + strlen(relative_path) + 2);
    if (!expanded)
        return NULL;
    strcpy(expanded, user_home);
    if (*relative_path != '\0') {
        strcat(expanded, "/");
        strcat(expanded, relative_path);
    }
    return expanded;
}

/**
 * @brief Checks if a user exists and retrieves their home directory.
 *
 * This function extracts the username from the given directory string,
 * retrieves the user's home directory, and constructs the full path
 * including any relative path provided.
 *
 * @param directory The directory string starting with `~username`.
 * @return A newly allocated string containing the full path, or NULL if
 *         the user does not exist.
 */
static char *does_user_exist(char *directory)
{
    char *slash = strchr(directory + 1, '/');
    char *user_home = NULL;
    char *full_path = NULL;
    char *relative_path = NULL;

    if (slash) {
        *slash = '\0';
        relative_path = slash + 1;
    } else
        relative_path = "";
    user_home = get_root_home(directory + 1);
    if (!user_home) {
        dprintf(2, "Unknown user: %s.\n", directory + 1);
        return NULL;
    }
    full_path = get_expanded_path(user_home, relative_path);
    return full_path;
}

/**
 * @brief Expands the tilde (~) in a directory string.
 *
 * This function handles different cases of tilde expansion:
 * - `~` expands to the current user's home directory.
 * - `~/` expands to the current user's home directory with a relative path.
 * - `~username` expands to the specified user's home directory.
 *
 * @param directory The directory string starting with `~`.
 * @param env The environment variables array.
 * @return A newly allocated string containing the expanded directory, or
 *         NULL on error.
 */
static char *expand_tilde(char *directory, char **env)
{
    char *home = get_value_key("HOME", env);
    char *expanded = NULL;

    if (!home)
        return NULL;
    if (directory[1] == '\0')
        return home;
    if (directory[1] == '/') {
        expanded = malloc(strlen(home) + strlen(directory));
        if (!expanded)
            return NULL;
        strcpy(expanded, home);
        free(home);
        strcat(expanded, directory + 1);
        return expanded;
    }
    free(home);
    directory = does_user_exist(directory);
    return directory;
}

/**
 * @brief Handles tilde (~) and other special cases for the `cd` command.
 *
 * This function processes the input directory string and handles:
 * - `~` for the current user's home directory.
 * - `~username` for another user's home directory.
 *
 * @param directory The input directory string.
 * @param env The environment variables array.
 * @param previous_dir The previous directory string.
 * @return A newly allocated string containing the processed directory.
 */
char *handle_tilde(char *directory, char **env, char *previous_dir)
{
    char *home_value = NULL;

    if (!directory || strcmp(directory, "~") == 0) {
        home_value = get_value_key("HOME", env);
        return home_value;
    }
    if (directory[0] == '~')
        return expand_tilde(directory, env);
    if (strcmp(directory, "-") == 0) {
        return strdup(previous_dir);
    }
    return strdup(directory);
}
