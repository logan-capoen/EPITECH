/*
** EPITECH PROJECT, 2025
** env_functions
** File description:
** cd functions
*/

/**
 * @file my_cd.c
 * @brief Implementation of the `cd` command for the shell.
 *
 * This file contains functions to handle the `cd` command, including
 * directory switching, error handling, and tilde expansion.
 */

#include "builtins.h"

/**
 * @brief Checks if the given path is a regular file.
 *
 * This function uses `stat` to determine if the specified path corresponds
 * to a regular file.
 *
 * @param path The path to check.
 * @return 1 if the path is a regular file, 0 otherwise.
 */
static int is_file(const char *path)
{
    struct stat path_stat = {0};

    if (stat(path, &path_stat) == -1)
        return 0;
    return S_ISREG(path_stat.st_mode) ? 1 : 0;
}

/**
 * @brief Switches to the specified directory.
 *
 * This function attempts to change the current working directory to the
 * specified directory. If the operation fails, it prints an appropriate
 * error message. If it succeeds, it updates the `PWD` environment variable
 * in the shell's global environment.
 *
 * @param directory The directory to switch to.
 * @param shell The shell structure containing environment variables and state.
 * @return 0 on success, 1 on failure.
 */
static int switch_to_dir(char *directory, shell_t *shell)
{
    char cwd[512];
    char *args[] = {"setenv", "PWD", NULL, NULL};

    if (chdir(directory) == -1) {
        if (errno == EACCES)
            dprintf(2, "%s: Permission denied.\n", directory);
        else
            dprintf(2, "%s: No such file or directory.\n", directory);
        free(directory);
        return 1;
    }
    getcwd(cwd, sizeof(cwd));
    args[2] = cwd;
    if (my_setenv(shell, args, 0) == 1) {
        free(directory);
        return 1;
    }
    free(directory);
    return 0;
}

/**
 * @brief Handles the `cd` command.
 *
 * This function processes the `cd` command, handling arguments, tilde
 * expansion, and error cases such as too many arguments or invalid paths.
 * It updates the shell's old working directory (`owd`) and switches to the
 * specified directory.
 *
 * @param shell The shell structure containing environment variables and
 *              the old working directory.
 * @param command_args The arguments passed to the `cd` command.
 * @param local Unused parameter for compatibility with other builtins.
 * @return 0 on success, 1 on failure.
 */
int my_cd(shell_t *shell, char **command_args,
    __attribute_maybe_unused__ int local)
{
    char *directory = NULL;

    if (command_args[1] && command_args[2]) {
        dprintf(2, "cd: Too many arguments.\n");
        return 1;
    }
    directory = handle_tilde(command_args[1], shell->env->global, shell->owd);
    if (!directory) {
        return 1;
    }
    if (is_file(directory)) {
        dprintf(2, "%s: Not a directory.\n", directory);
        free(directory);
        return 1;
    }
    getcwd(shell->owd, 512);
    return switch_to_dir(directory, shell);
}
