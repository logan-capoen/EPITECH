/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtins header
*/

#ifndef BUILTINS
    #define BUILTINS
    #include "meowsh.h"
    #include "utilities.h"
    #include <errno.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #define NB_BUILT_IN 12
    #define BUFFER_SIZE 65536


// Alias
int interpret_alias(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local);
int interpret_unalias(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local);
void add_node(aliases_t **aliases, aliases_t *new_node);
void delete_node(aliases_t **aliases, aliases_t *node, aliases_t *previous);
void free_node(aliases_t *node);

// History
void get_history(shell_t *shell);
void add_to_history(char *command, shell_t *shell);
void free_history(char **history, int count);
int display_history(shell_t *shell, __attribute_maybe_unused__ char **command,
    __attribute_maybe_unused__ int local);
char *exec_history(shell_t *shell, char *command);

// Environment
int my_unsetenv(shell_t *sh, char **command, int local);
int my_env(shell_t *sh, char **command, int local);
int my_setenv(shell_t *sh, char **command, int local);
int add_elt(char ***array, char *elt);

// Cd
char *handle_tilde(char *directory, char **env, char *previous_dir);
char *get_root_home(char *user);
int my_cd(shell_t *shell, char **command_args,
    __attribute_maybe_unused__ int local);
char *get_value_key(char *key, char **env);

// Which and where
int interpret_which(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local);
int interpret_where(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local);
int is_a_builtin_command_where(char *command);
int is_a_builtin_command_which(char *command);

// Exit
int my_exit(shell_t *shell, char **command,
    __attribute_maybe_unused__ int local);

#endif
