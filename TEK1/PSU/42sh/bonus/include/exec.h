/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** exec.h
*/

#ifndef EXEC_H
    #define EXEC_H

    #include "meowsh.h"
    #include "builtins.h"
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <fcntl.h>
    #include <string.h>
    #include <dirent.h>

    #define CMD 0
    #define BUILT_CMD 1
    #define SUBCMD 2
    #define NOTHING 3

static const tab_builtins_t tab[NB_BUILT_IN] = {
    {"cd", &my_cd, 0},
    {"setenv", &my_setenv, 0},
    {"env", &my_env, 0},
    {"unsetenv", &my_unsetenv, 0},
    {"history", &display_history, 0},
    {"alias", &interpret_alias, 0},
    {"unalias", &interpret_unalias, 0},
    {"exit", &my_exit, 0},
    {"set", &my_setenv, 1},
    {"unset", &my_unsetenv, 1},
    {"which", &interpret_which, 0},
    {"where", &interpret_where, 0},
    {"meowsh", &display_cat, 0}
};

typedef struct exec_data_s {
    int nb_elt;
    int **pipe;
    int *pid;
    int *status;
    int *cmd_type;
    int prev_depth;
} exec_data_t;

void exec_cmd(shell_t *shell, commands_t **cmds, int prev_depth);
void check_signal(shell_t *shell, exec_data_t *exec_data, int i);
char *get_cmd_path(char *command, char **env);
int get_cmd_type(commands_t *cmd);
char **get_paths(char **env);
int check_path(char *command, char *path);
int init_exec_data(commands_t **cmds, exec_data_t *exec_data);
void free_exec_data(exec_data_t *exec_data);
void manage_saved_fd(int saved[2]);

#endif /*EXEC_H*/
