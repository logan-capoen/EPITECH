/*
** EPITECH PROJECT, 2025
** handle env
** File description:
** handle_env
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell1.h"
#include "my.h"

static int add_node(env_t **env_list, char **env, int i)
{
    env_t *node = malloc(sizeof(env_t));
    env_t *tmp = *env_list;

    if (!node)
        return 84;
    node->key = my_strdup(strtok(env[i], "="));
    node->value = is_null(strtok(NULL, ""));
    node->next = NULL;
    if (tmp == NULL) {
        *env_list = node;
        return 0;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
    return 0;
}

env_t *get_env(char **env)
{
    env_t *env_list = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        add_node(&env_list, env, i);
    }
    return env_list;
}

int display_env(env_t *env_list, char *input)
{
    if (!check_parsing(input, 1))
        return 1;
    while (env_list != NULL) {
        my_putstr(env_list->key);
        my_putchar('=');
        if (env_list->value != NULL)
            my_putstr(env_list->value);
        my_putchar('\n');
        env_list = env_list->next;
    }
    return 0;
}

static void add_value(env_t **env_list, char **args)
{
    int nb_args = 0;

    for (; args[nb_args] != NULL; nb_args++);
    if (nb_args == 3) {
        (*env_list)->value = my_strdup(args[2]);
        return;
    }
    (*env_list)->value = NULL;
}

static int already_exist(env_t *env_list, char *input)
{
    env_t *tmp = env_list;
    char *key = NULL;

    strtok(input, " ");
    key = my_strdup(strtok(NULL, " "));
    while (tmp != NULL) {
        if (my_strcmp(key, tmp->key) == 0) {
            free(tmp->value);
            add_value(&tmp, my_str_to_word_array(input, ' '));
            free(input);
            free(key);
            return 1;
        }
        tmp = tmp->next;
    }
    free(input);
    free(key);
    return 0;
}

static int check_alpha_numeric(char **arr)
{
    if (!is_letter(arr[1][0])) {
        my_putstr("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    for (int i = 0; arr[1][i] != '\0'; i++) {
        if (!is_alpha(arr[1][i])) {
            my_putstr("setenv: Variable name must contain "
                "alphanumeric characters.\n");
            return 1;
        }
    }
    return 0;
}

static int handle_args_setenv(char *input, env_t **env_list, char **arr)
{
    if (check_parsing(input, 1)) {
        display_env(*env_list, input);
        return 0;
    }
    if (check_alpha_numeric(arr))
        return 1;
    if (check_parsing(input, 2))
        return 2;
    if (check_parsing(input, 3) != 1) {
        my_putstr("setenv: Too many arguments.\n");
        return 1;
    }
    return 2;
}

int set_env(env_t **env_list, char *input)
{
    env_t *new = malloc(sizeof(env_t));
    env_t *tmp = *env_list;
    char *copy = my_strdup(input);
    int status = 0;
    char **arr = my_str_to_word_array(input, ' ');

    status = handle_args_setenv(input, env_list, arr);
    if (status != 2)
        return status;
    if (already_exist(*env_list, copy)) {
        return 0;
    }
    new->key = my_strdup(arr[1]);
    add_value(&new, arr);
    new->next = NULL;
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    free_arr(arr);
    return 0;
}

static int delete_env(env_t **env_list, char *todel)
{
    env_t *tmp = *env_list;
    env_t *prev = NULL;

    if (my_strcmp(tmp->key, todel) == 0) {
        *env_list = tmp->next;
        free_node(tmp);
        return 0;
    }
    while (tmp != NULL) {
        if (my_strcmp(tmp->key, todel) == 0) {
            prev->next = tmp->next;
            free_node(tmp);
            return 0;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return 1;
}

int unset_env(env_t **env_list, char *input)
{
    char **arr = my_str_to_word_array(input, ' ');

    if (!arr)
        return 84;
    if (check_parsing(input, 1)) {
        my_putstr("unsetenv: Too few arguments.\n");
        free_arr(arr);
        return 1;
    }
    for (int i = 1; arr[i] != NULL; i++)
        delete_env(env_list, arr[i]);
    free_arr(arr);
    return 0;
}
