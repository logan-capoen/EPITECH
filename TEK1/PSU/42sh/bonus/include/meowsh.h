/*
** EPITECH PROJECT, 2025
** meowsh
** File description:
** Main header file
*/

#ifndef MEOWSH_H
    #define MEOWSH_H
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <ctype.h>
    #include <string.h>

typedef enum sep_s {
    NONE,
    PIPE,
    AND,
    OR,
    COLUMN,
    AND_OR
} sep_t;

///////     Environment     ///////
typedef struct env_s {
    char **local;
    char **global;
} env_t;

///////////////////////////////////

//////////     Alias     //////////
typedef struct aliases_s {
    char *original;
    char *new_name;
    bool browsed;
    struct aliases_s *next;
} aliases_t;

///////////////////////////////////

/////     Main structures     /////
typedef struct commands_s {
    sep_t separator;
    int depth;
    int fd_input;
    int fd_output;
    char *heredoc;
    char *path;
    char **command;
    struct commands_s **subcommands;
} commands_t;

typedef struct shell_s {
    commands_t **commands;
    env_t *env;
    aliases_t **aliases;
    char **history;
    int history_size;
    char *owd;
    int exit_status;
    bool run;
} shell_t;

///////////////////////////////////

/////    Builtins execution    ////
typedef struct {
    char *command;
    int (*builtin_func)(shell_t *, char **command, int local);
    int __attribute_maybe_unused__ local;
} tab_builtins_t;

///////////////////////////////////

// Utilities
int str_isalphanum(char *str);

#endif
