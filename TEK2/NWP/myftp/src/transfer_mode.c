/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** transfer_mode.c
*/
#include "myftp.h"

static void get_server_ip(client_t *client, struct sockaddr_in *addr)
{
    socklen_t len = sizeof(*addr);

    getsockname(client->control_fd, (struct sockaddr *)addr, &len);
}

static void send_pasv_response(client_t *client, int port)
{
    struct sockaddr_in addr;
    unsigned char *ip;
    char response[128];

    get_server_ip(client, &addr);
    ip = (unsigned char *)&addr.sin_addr.s_addr;
    snprintf(response, sizeof(response),
        "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
        ip[0], ip[1], ip[2], ip[3], port / 256, port % 256);
    send_response(client->control_fd, response);
}

static int create_and_store_data_socket(client_t *client)
{
    int port;
    int data_fd;

    port = 0;
    data_fd = create_data_socket(&port);
    if (data_fd < 0)
        return -1;
    client->data_fd = data_fd;
    client->passive_mode = 1;
    send_pasv_response(client, port);
    return 0;
}

void handle_pasv(client_t *client)
{
    if (!check_logged(client))
        return;
    if (client->data_fd >= 0) {
        close(client->data_fd);
        client->data_fd = -1;
    }
    if (create_and_store_data_socket(client) < 0)
        send_response(client->control_fd,
            "425 Can't open data connection.\r\n");
}

static int parse_and_fill_port(client_t *client, char *arg)
{
    int values[6];

    if (sscanf(arg, "%d,%d,%d,%d,%d,%d",
        &values[0], &values[1], &values[2],
        &values[3], &values[4], &values[5]) != 6)
        return -1;
    memset(&client->port_addr, 0, sizeof(client->port_addr));
    client->port_addr.sin_family = AF_INET;
    client->port_addr.sin_addr.s_addr = htonl((values[0] << 24) |
        (values[1] << 16) | (values[2] << 8) | values[3]);
    client->port_addr.sin_port = htons((values[4] << 8) | values[5]);
    client->passive_mode = 0;
    return 0;
}

void handle_port(client_t *client, char *arg)
{
    if (!check_logged(client))
        return;
    if (arg == NULL)
        return send_response(client->control_fd,
            "501 Syntax error in parameters.\r\n");
    if (parse_and_fill_port(client, arg) < 0)
        return send_response(client->control_fd,
            "501 Syntax error in parameters.\r\n");
    send_response(client->control_fd, "200 Command okay.\r\n");
}
