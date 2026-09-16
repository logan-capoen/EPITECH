/*
** EPITECH PROJECT, 2025
** fork
** File description:
** fork
*/

/**
 * @file forkc
 * @brief All function for fork and execve.
 *
 * This file contains all the functions
 * to handle the execution of funxtion execve.
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell1.h"
#include "my.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

/**
 * @brief Retrieves all paths from the environment variable PATH.
 *
 * @param env The environment variables.
 * @return An array of paths if PATH is found, otherwise NULL.
 */
static char **get_all_paths(char **env)
{
    char *path = NULL;
    char **paths = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "PATH", 4) == 0) {
            path = my_strdup(env[i] + 5);
            break;
        }
    }
    if (!path)
        return NULL;
    paths = my_str_to_word_array(path, ':');
    free(path);
    if (!paths)
        return NULL;
    return paths;
}

/**
 * @brief Checks the given paths for the existence of the command.
 *
 * @param env The environment variables.
 * @param argv The command arguments.
 * @return The full path to the command if found, otherwise NULL.
 */
char *check_paths(char **env, char **argv)
{
    char *tmp = NULL;
    char **paths = get_all_paths(env);

    for (int i = 0; paths[i] != NULL; i++) {
        tmp = malloc(my_strlen(paths[i]) + my_strlen(argv[0]) + 2);
        if (!tmp)
            continue;
        my_strcpy(tmp, paths[i]);
        my_strcat(tmp, "/");
        my_strcat(tmp, argv[0]);
        if (access(tmp, F_OK) == 0) {
            free_arr(paths);
            return tmp;
        }
        free(tmp);
    }
    free_arr(paths);
    return NULL;
}

static void display_error(int status)
{
    if (WIFSIGNALED(status)) {
        if (status == 136) {
            my_putstr("Floating exception (core dump)\n");
            return;
        }
        if (status == 139 && WCOREDUMP(status)) {
            my_putstr("Segmentation fault (core dump)\n");
            return;
        }
        my_putstr(strsignal(WTERMSIG(status)));
        my_putchar('\n');
    }
}

/**
 * @brief Forks a new process and executes the command.
 *
 * @param argv The command arguments.
 * @param env The environment variables.
 * @param status The status of the child process.
 * @param path The path to the command.
 */
void my_fork(char **argv, char **env, int *value, char *path)
{
    int pid = fork();

    switch (pid) {
    case -1:
        perror("fork");
        break;
    case 0:
        execve(path, argv, env);
        kill(getpid(), WTERMSIG(*value));
        break;
    default:
        waitpid(pid, value, 0);
        display_error(*value);
        if (*value != 0)
            *value = 2;
        break;
    }
}

/**
 * @brief Converts an environment list to a single line string.
 *
 * @param env_list The environment list.
 * @return A string representing the environment variable.
 */
static char *put_in_line(env_t *env_list)
{
    char *line = NULL;
    int len_line = my_strlen(env_list->key) + 2;

    if (env_list->value != NULL)
        len_line += my_strlen(env_list->value);
    line = malloc(sizeof(char) * len_line);
    if (!line) {
        perror("malloc");
        return NULL;
    }
    my_strcpy(line, env_list->key);
    my_strcat(line, "=");
    if (env_list->value != NULL)
        my_strcat(line, env_list->value);
    return line;
}

/**
 * @brief Transforms an environment list to an array of strings.
 *
 * @param env_list The environment list.
 * @return An array of strings representing the environment variables.
 */
char **transform_list_to_arr(env_t *env_list)
{
    char **arr = NULL;
    int lines = 0;
    env_t *current = env_list;

    for (; current != NULL; current = current->next)
        lines++;
    arr = malloc(sizeof(char *) * (lines + 1));
    if (!arr)
        return NULL;
    for (int i = 0; i <= lines; i++) {
        arr[i] = NULL;
    }
    current = env_list;
    for (int i = 0; i < lines; i++) {
        arr[i] = put_in_line(current);
        current = current->next;
    }
    return arr;
}

static int check_local_function(char **path, char *input)
{
    if (*path == NULL) {
        if (access(input, F_OK) == 0) {
            *path = my_strdup(input);
            return 0;
        } else {
            my_putstr(input);
            my_putstr(": Command not found.\n");
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Handles the execution of a command using execve.
 *
 * @param env_list The environment list.
 * @param input The input command.
 * @return 0 on success, 84 on failure.
 */
int handle_execve(env_t *env_list, char *input)
{
    char *copy = my_strdup(input);
    char **args = my_str_to_word_array(input, ' ');
    int value = 0;
    char **env_arr = transform_list_to_arr(env_list);
    char *path = check_paths(env_arr, args);

    if (!env_arr) {
        free(copy);
        free_arr(args);
        return 84;
    }
    if (check_local_function(&path, input))
        return 1;
    my_fork(args, env_arr, &value, path);
    free(copy);
    free_arr(args);
    free_arr(env_arr);
    free(path);
    return value;
}
