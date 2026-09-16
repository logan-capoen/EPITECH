/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** command_router.c
*/
#include "myftp.h"
#include "commands.h"

static char *split_command(char *buffer)
{
    char *space = strchr(buffer, ' ');

    if (space == NULL)
        return NULL;
    *space = '\0';
    return space + 1;
}

void handle_command(client_t *client, char *buffer)
{
    char *arg = NULL;

    buffer[strcspn(buffer, "\r\n")] = '\0';
    if (strlen(buffer) == 0)
        return;
    arg = split_command(buffer);
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(buffer, commands[i].name) == 0) {
            commands[i].handler(client, arg);
            return;
        }
    }
    send_response(client->control_fd, "500 Unknown command.\r\n");
}
