/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** get_cmd_path.c
*/

/**
 * @file get_cmd_path.c
 * @brief Functions to locate the executable path of a command.
 *
 * This file contains functions to parse the `PATH` environment variable,
 * search for a command in the directories listed in `PATH`, and return
 * the full path to the executable if found.
 */

#include "exec.h"
#include "utilities.h"

/**
 * @brief Count the number of paths in the `PATH` environment variable.
 *
 * This function counts the number of directories listed in the `PATH`
 * environment variable, separated by colons (`:`).
 *
 * @param path_line The `PATH` environment variable string.
 * @return The number of paths in the `PATH` string.
 */
static int count_nb_paths(char *path_line)
{
    int nb_path = 0;

    for (int i = 0; path_line && path_line[i]; i++)
        nb_path += path_line[i] == ':';
    return nb_path + 1;
}

/**
 * @brief Convert the `PATH` string into a list of directories.
 *
 * This function splits the `PATH` environment variable into an array
 * of directory paths, appending a trailing slash (`/`) to each path.
 *
 * @param path_line The `PATH` environment variable string.
 * @return A dynamically allocated array of directory
 * paths, or NULL on failure.
 */
static char **convert_in_list(char *path_line)
{
    int nb_paths = count_nb_paths(path_line);
    char **list_paths = malloc(sizeof(char *) * (nb_paths + 1));
    char *path = NULL;
    char *save_ptr = NULL;

    if (!list_paths)
        return NULL;
    path = strtok_r(path_line, ":", &save_ptr);
    for (int i = 0; path; i++) {
        list_paths[i] = strjoin(path, "/");
        path = strtok_r(NULL, ":", &save_ptr);
    }
    list_paths[nb_paths] = NULL;
    free(path_line);
    return list_paths;
}

/**
 * @brief Retrieve the list of directories from the
 * `PATH` environment variable.
 *
 * This function extracts the `PATH` environment variable from the shell's
 * environment and converts it into a list of directories.
 *
 * @param env The shell's environment variables.
 * @return A dynamically allocated array of
 * directory paths, or NULL on failure.
 */
char **get_paths(char **env)
{
    int i = 0;
    char *tmp_line = NULL;

    if (!env)
        return NULL;
    for (; env[i] && strncmp(env[i], "PATH=", 5); i++);
    if (env[i])
        tmp_line = strdup(&(env[i][5]));
    return (env[i] && tmp_line) ? convert_in_list(tmp_line) : NULL;
}

/**
 * @brief Check if a command exists in a given directory.
 *
 * This function searches for a command in the specified directory by
 * iterating through the directory's contents.
 *
 * @param command The name of the command to search for.
 * @param path The directory path to search in.
 * @return 1 if the command is found, 0 otherwise.
 */
int check_path(char *command, char *path)
{
    DIR *dir = opendir(path);
    struct dirent *elt = NULL;

    if (!dir)
        return 0;
    do {
        elt = readdir(dir);
        if (elt && !strcmp(elt->d_name, command)) {
            closedir(dir);
            return 1;
        }
    } while (elt);
    closedir(dir);
    return 0;
}

/**
 * @brief Get the full path of a command.
 *
 * This function searches for a command in the directories listed in the
 * `PATH` environment variable. If the command is found, its full path
 * is returned. If the command is already an absolute path or relative
 * path, it is returned as is.
 *
 * @param command The name of the command to locate.
 * @param env The shell's environment variables.
 * @return A dynamically allocated string
 * containing the full path to the command,
 *         or NULL if the command is not found.
 */
char *get_cmd_path(char *command, char **env)
{
    int i = 0;
    char **list_path = NULL;
    char *path = NULL;

    if (!access(command, F_OK))
        return strdup(command);
    list_path = get_paths(env);
    if (!list_path)
        return NULL;
    for (; list_path[i] && !check_path(command, list_path[i]); i++);
    path = list_path[i] ? strjoin(list_path[i], command) : NULL;
    for (i = 0; list_path[i]; i++)
        free(list_path[i]);
    free(list_path);
    return path;
}
