/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** utils.c
*/
#include "myftp.h"

void send_response(int fd, const char *msg)
{
    write(fd, msg, strlen(msg));
}

int create_data_socket(int *port)
{
    struct sockaddr_in addr = {AF_INET, htons(0), {INADDR_ANY}, {}};
    socklen_t len;
    int fd;

    len = sizeof(addr);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        return -1;
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return -1;
    if (listen(fd, 1) < 0)
        return -1;
    getsockname(fd, (struct sockaddr *)&addr, &len);
    *port = ntohs(addr.sin_port);
    return fd;
}

int open_data_connection(client_t *client)
{
    int fd = 0;

    if (client->passive_mode) {
        return accept(client->data_fd, NULL, NULL);
    } else {
        fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd < 0)
            return -1;
        if (connect(fd, (struct sockaddr *)&client->port_addr,
            sizeof(client->port_addr)) < 0) {
            close(fd);
            return -1;
        }
        return fd;
    }
}

int check_logged(client_t *client)
{
    if (client->state != STATE_LOGGED_IN) {
        send_response(client->control_fd,
            "530 Please login with USER and PASS.\r\n");
        return 0;
    }
    return 1;
}
