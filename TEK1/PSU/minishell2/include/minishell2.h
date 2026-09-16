/*
** EPITECH PROJECT, 2025
** minishell1 header
** File description:
** minishell2
*/

#ifndef MINISHELL1
    #define MINISHELL1

typedef struct env {
    char *key;
    char *value;
    struct env *next;
} env_t;

typedef struct input_s {
    char **lines;
    char **inputs;
    char **outputs;
    char **pipes;
    int index;
} input_t;

env_t *get_env(char **env);
int display_env(env_t *env_list, char *input);
void free_list(env_t *env_list);
int set_env(env_t **env_list, char *input);
int handle_execve(env_t *env_list, char *input);
void free_arr(char **arr);
int unset_env(env_t **env_list, char *input);
void free_node(env_t *env_list);
int check_parsing(char *input, int n);
int my_cd(char *input, env_t *env_list, char **lwd);
void free_list(env_t *env_list);
char *is_null(char *token);
int is_letter(char chara);
int is_alpha(char chara);
input_t *get_input(char *input);
int check_params(input_t *inputs, env_t *env_list, char **lwd, int i);
char *start_line(char *line);
int parsing_input(char *input, env_t *env_list, char **lwd);
int execute_pipe(input_t *inputs, env_t *env_list, char **lwd);
void free_input(input_t *input_struct);
#endif
