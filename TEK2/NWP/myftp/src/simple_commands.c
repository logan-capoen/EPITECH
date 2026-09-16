/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** commands.c
*/
#include "myftp.h"

void handle_dele(client_t *client, char *arg)
{
    char filepath[BUFFER_SIZE];

    if (!check_logged(client))
        return;
    if (arg == NULL) {
        send_response(client->control_fd,
            "501 Syntax error in parameters.\r\n");
        return;
    }
    if (arg[0] == '/')
        snprintf(filepath, sizeof(filepath), "%s", arg);
    else
        snprintf(filepath, sizeof(filepath), "%s/%s", client->cwd, arg);
    if (unlink(filepath) < 0) {
        send_response(client->control_fd, "550 File not found.\r\n");
        return;
    }
    send_response(client->control_fd,
        "250 Requested file action okay, completed.\r\n");
}

void handle_quit(client_t *client)
{
    send_response(client->control_fd,
        "221 Service closing control connection.\r\n");
    close(client->control_fd);
    if (client->data_fd >= 0)
        close(client->data_fd);
    client->control_fd = -1;
}

void handle_noop(client_t *client)
{
    send_response(client->control_fd, "200 Command okay.\r\n");
}

void handle_help(client_t *client)
{
    send_response(client->control_fd,
        "214 Available commands: "
        "USER PASS CWD CDUP QUIT DELE PWD "
        "PASV PORT RETR STOR LIST HELP NOOP\r\n");
}
