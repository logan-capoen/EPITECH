/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** navigation.c
*/
#include "myftp.h"

void handle_pwd(client_t *client)
{
    char response[BUFFER_SIZE + 10];

    if (!check_logged(client))
        return;
    snprintf(response, sizeof(response), "257 \"%s\"\r\n", client->cwd);
    send_response(client->control_fd, response);
}

static void create_new_path(client_t *client, char *path,
    char *new_path, size_t size)
{
    char tmp[BUFFER_SIZE];
    char *resolved;

    if (path[0] == '/')
        snprintf(tmp, sizeof(tmp), "%s", path);
    else
        snprintf(tmp, sizeof(tmp), "%s/%s", client->cwd, path);
    resolved = realpath(tmp, new_path);
    if (resolved == NULL)
        snprintf(new_path, size, "%s", tmp);
}

void handle_cwd(client_t *client, char *arg)
{
    char new_path[BUFFER_SIZE];
    struct stat st;

    if (!check_logged(client))
        return;
    if (arg == NULL) {
        send_response(client->control_fd,
            "501 Syntax error in parameters.\r\n");
        return;
    }
    create_new_path(client, arg, new_path, sizeof(new_path));
    if (stat(new_path, &st) < 0 || !S_ISDIR(st.st_mode)) {
        send_response(client->control_fd,
            "550 No such file or directory.\r\n");
        return;
    }
    strncpy(client->cwd, new_path, sizeof(client->cwd));
    send_response(client->control_fd,
        "250 Requested file action okay, completed.\r\n");
}

void handle_cdup(client_t *client)
{
    char *last_slash = NULL;

    if (!check_logged(client))
        return;
    last_slash = strrchr(client->cwd, '/');
    if (last_slash == NULL || last_slash == client->cwd) {
        strcpy(client->cwd, "/");
    } else {
        *last_slash = '\0';
    }
    send_response(client->control_fd, "200 Command okay.\r\n");
}
