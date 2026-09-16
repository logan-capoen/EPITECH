/*
** EPITECH PROJECT, 2025
** cd_function
** File description:
** cd_function
*/

/**
 * @file cd_function.c
 * @brief Implementation of the `my_cd`
 * function for changing directories in a shell.
 *
 * This file contains the implementation of the `my_cd` function, which is used
 * to change the current working directory in a custom shell program.
 */
#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "include/my.h"
#include "include/minishell1.h"
#include <stdlib.h>
#include <errno.h>

char *get_home(env_t *env_list)
{
    for (; env_list != NULL; env_list = env_list->next) {
        if (my_strcmp(env_list->key, "HOME") == 0)
            return env_list->value;
    }
    return ".";
}

static void execute_chdir(char *path, char *input)
{
    if (chdir(path) != 0) {
        my_putstr(input);
        my_putstr(": ");
        my_putstr(strerror(errno));
        my_putstr(".\n");
    }
}

static int handle_cd_cases(char *input, env_t *env_list,
    char **args, char *path_flag)
{
    if (check_parsing(input, 1)) {
        execute_chdir(get_home(env_list), args[1]);
        free_arr(args);
        return 1;
    }
    if (check_parsing(input, 2)) {
        if (my_strncmp(args[1], "/", 1) == 0) {
            chdir(args[1]);
            return 1;
        }
        if (my_strcmp(args[1], "-") == 0) {
            chdir(path_flag);
            free(path_flag);
            return 1;
        }
    }
    return 0;
}

static void execute_cd(char *cwd, char *input, char **args)
{
    char *path = NULL;
    int len_path = 0;

    len_path = strlen(cwd) + strlen(input) + 2;
    path = malloc(sizeof(char) * len_path);
    my_strcpy(path, cwd);
    my_strcat(path, "/");
    my_strcat(path, args[1]);
    execute_chdir(path, args[1]);
    free_arr(args);
    free(path);
}

/**
 * @brief Changes the current working directory based on the input command.
 *
 * This function takes a command input string, parses it to extract the target
 * directory, and changes the current working directory to the specified path.
 *
 * @param input The input command string containing the target directory.
 * @return Returns 0 on success, or 84 on failure.
 */
int my_cd(char *input, env_t *env_list, char **lwd)
{
    char cwd[PATH_MAX];
    char **args = my_str_to_word_array(input, ' ');
    char *path_flag = NULL;

    path_flag = my_strdup(*lwd);
    getcwd(*lwd, PATH_MAX);
    if (handle_cd_cases(input, env_list, args, path_flag))
        return 0;
    if (!check_parsing(input, 2) || !getcwd(cwd, sizeof(cwd))) {
        free_arr(args);
        return 84;
    }
    execute_cd(cwd, input, args);
    return 0;
}
