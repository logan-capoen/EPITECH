/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** file_transfer.c
*/
#include "myftp.h"

static char *build_filepath(client_t *client, char *arg, char *filepath)
{
    if (arg[0] == '/')
        snprintf(filepath, BUFFER_SIZE, "%s", arg);
    else
        snprintf(filepath, BUFFER_SIZE, "%s/%s", client->cwd, arg);
    return filepath;
}

static int check_arg(client_t *client, char *arg)
{
    if (arg != NULL)
        return 1;
    send_response(client->control_fd, "501 Syntax error in parameters.\r\n");
    return 0;
}

static void transfer_data(int src_fd, int dest_fd)
{
    char buffer[BUFFER_SIZE];
    int n = read(src_fd, buffer, sizeof(buffer));

    while (n > 0) {
        write(dest_fd, buffer, n);
        n = read(src_fd, buffer, sizeof(buffer));
    }
}

static int open_data_and_check(client_t *client, int file_fd)
{
    int data_fd = open_data_connection(client);

    if (data_fd >= 0)
        return data_fd;
    send_response(client->control_fd, "425 Can't open data connection.\r\n");
    close(file_fd);
    return -1;
}

void close_data(client_t *client, int data_fd)
{
    close(data_fd);
    if (client->data_fd >= 0) {
        close(client->data_fd);
        client->data_fd = -1;
    }
}

void handle_retr(client_t *client, char *arg)
{
    char filepath[BUFFER_SIZE];
    int file_fd;
    int data_fd;

    if (!check_logged(client) || !check_arg(client, arg))
        return;
    build_filepath(client, arg, filepath);
    file_fd = open(filepath, O_RDONLY);
    if (file_fd < 0)
        return send_response(client->control_fd, "550 File not found.\r\n");
    send_response(client->control_fd,
        "150 File status okay; about to open data connection.\r\n");
    data_fd = open_data_and_check(client, file_fd);
    if (data_fd < 0)
        return;
        
    transfer_data(file_fd, data_fd);
    close(file_fd);
    close_data(client, data_fd);
    send_response(client->control_fd, "226 Closing data connection.\r\n");
}

void handle_stor(client_t *client, char *arg)
{
    char filepath[BUFFER_SIZE];
    int file_fd;
    int data_fd;

    if (!check_logged(client) || !check_arg(client, arg))
        return;
    build_filepath(client, arg, filepath);
    file_fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0)
        return send_response(client->control_fd, "550 Permission denied.\r\n");
    send_response(client->control_fd,
        "150 File status okay; about to open data connection.\r\n");
    data_fd = open_data_and_check(client, file_fd);
    if (data_fd < 0)
        return;
    transfer_data(data_fd, file_fd);
    close(file_fd);
    close_data(client, data_fd);
    send_response(client->control_fd, "226 Closing data connection.\r\n");
}
