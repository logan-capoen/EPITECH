/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "minishell2.h"
#include <unistd.h>
#include <errno.h>
#include <linux/limits.h>

int parsing_input(char *input, env_t *env_list, char **lwd)
{
    if (my_strncmp(input, "env", 3) == 0)
        return display_env(env_list, input);
    if (my_strncmp(input, "setenv", 6) == 0)
        return set_env(&env_list, input);
    if (my_strncmp(input, "unsetenv", 8) == 0)
        return unset_env(&env_list, input);
    if (my_strncmp(input, "cd", 2) == 0)
        return my_cd(input, env_list, lwd);
    return handle_execve(env_list, input);
}

static int check_line(char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return 1;
    }
    return 0;
}

static int check_exit(char *line)
{
    if (line == NULL || my_strcmp(line, "exit") == 0) {
        free(line);
        return 1;
    }
    return 0;
}

static int execute_input(char *line, env_t *env_list, char **lwd)
{
    input_t *inputs = get_input(line);
    int status = 0;

    if (inputs == NULL)
        return 1;
    for (int i = 0; inputs->lines[i] != NULL; i++) {
        inputs->index = i;
        line[my_strlen(inputs->lines[i]) - 1] = '\0';
        if (check_exit(inputs->lines[i]))
            exit(status);
        if (my_strlen(line) != 0 && check_line(start_line(inputs->lines[i]))
            && inputs->pipes[i] == NULL)
            status = check_params(inputs, env_list, lwd, 0);
        if (my_strlen(line) != 0 && check_line(start_line(inputs->lines[i]))
            && inputs->pipes[i] != NULL)
            status = check_params(inputs, env_list, lwd, 1);
    }
    free_input(inputs);
    return status;
}

static int minishell(env_t *env_list, char **lwd)
{
    size_t len = 0;
    char *line = NULL;
    int status = 0;

    while (1) {
        if (isatty(0))
            my_putstr("$> ");
        if (getline(&line, &len, stdin) == -1) {
            free(line);
            return status;
        }
        line[my_strlen(line) - 1] = '\0';
        if (check_exit(line))
            return status;
        status = execute_input(line, env_list, lwd);
        if (!isatty(0) && status != 0)
            return status;
    }
    return status;
}

int main(int argc, char **argv, char **env)
{
    env_t *env_list = get_env(env);
    char *last_work_directory = malloc(sizeof(char) * PATH_MAX);
    int status = 0;

    for (int i = 0; i < PATH_MAX; i++)
        last_work_directory[i] = 0;
    if (argc != 1)
        return 84;
    status = minishell(env_list, &last_work_directory);
    free_list(env_list);
    free(last_work_directory);
    return status;
}
