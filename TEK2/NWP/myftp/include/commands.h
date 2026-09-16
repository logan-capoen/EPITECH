/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** commands
*/
#ifndef COMMANDS_H_
    #define COMMANDS_H_

typedef struct {
    const char *name;
    void (*handler)(client_t *, char *);
} command_t;

void wrap_quit(client_t *client, char *arg);
void wrap_pwd(client_t *client, char *arg);
void wrap_cdup(client_t *client, char *arg);
void wrap_pasv(client_t *client, char *arg);
void wrap_help(client_t *client, char *arg);
void wrap_noop(client_t *client, char *arg);

static const command_t commands[] = {
    {"USER", handle_user},
    {"PASS", handle_pass},
    {"QUIT", wrap_quit},
    {"PWD", wrap_pwd},
    {"CWD", handle_cwd},
    {"CDUP", wrap_cdup},
    {"PASV", wrap_pasv},
    {"PORT", handle_port},
    {"RETR", handle_retr},
    {"STOR", handle_stor},
    {"LIST", handle_list},
    {"DELE", handle_dele},
    {"HELP", wrap_help},
    {"NOOP", wrap_noop},
    {NULL, NULL}
};

#endif
