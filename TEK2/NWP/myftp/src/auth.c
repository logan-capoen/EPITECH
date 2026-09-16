/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** auth
*/

#include "myftp.h"

void handle_user(client_t *client, char *arg)
{
    if (!(arg == NULL || strcmp(arg, "Anonymous") != 0))
        client->state = STATE_USER_OK;
    else
        client->state = STATE_NOT_ANONYMOUS;
    send_response(client->control_fd,
        "331 User name okay, need password.\r\n");
}

void handle_pass(client_t *client, char *arg)
{
    if (arg != NULL && strlen(arg) > 0 || client->state == STATE_NOT_ANONYMOUS) {
        send_response(client->control_fd,
            "530 Wrong password.\r\n");
        client->state = STATE_CONNECTED;
        return;
    }
    if (client->state != STATE_USER_OK) {
        send_response(client->control_fd,
            "503 Use USER before.\r\n");
        return;
    }
    client->state = STATE_LOGGED_IN;
    send_response(client->control_fd,
        "230 User logged in, proceed.\r\n");
}
