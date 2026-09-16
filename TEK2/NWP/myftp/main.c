/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** main.c
*/

#include "myftp.h"

static void remove_client(server_t *server, int i)
{
    printf("Client déconnecté: fd %d\n", server->poll_fds[i].fd);
    close(server->poll_fds[i].fd);
    if (server->clients[i].data_fd >= 0)
        close(server->clients[i].data_fd);
    server->poll_fds[i] = server->poll_fds[server->nb_clients - 1];
    server->clients[i] = server->clients[server->nb_clients - 1];
    server->nb_clients--;
}

static void init_client(server_t *server, int new_fd)
{
    int i = server->nb_clients;

    server->poll_fds[i].fd = new_fd;
    server->poll_fds[i].events = POLLIN;
    server->clients[i].control_fd = new_fd;
    server->clients[i].data_fd = -1;
    server->clients[i].state = STATE_CONNECTED;
    server->clients[i].passive_mode = 1;
    strcpy(server->clients[i].cwd, server->clients[0].cwd);
    memset(&server->clients[i].port_addr, 0,
        sizeof(server->clients[i].port_addr));
    send_response(new_fd, "220 Service ready for new user.\r\n");
    server->nb_clients++;
}

static void handle_new_connection(server_t *server, int server_socket)
{
    struct sockaddr_in client_addr;
    socklen_t client_len;
    int new_fd;

    client_len = sizeof(client_addr);
    new_fd = accept(server_socket,
        (struct sockaddr *)&client_addr, &client_len);
    if (new_fd < 0 || server->nb_clients >= MAX_CLIENTS)
        return;
    printf("Nouvelle connexion: %s:%d (fd=%d)\n",
        inet_ntoa(client_addr.sin_addr),
        ntohs(client_addr.sin_port), new_fd);
    init_client(server, new_fd);
}

static void handle_client_data(server_t *server, int i)
{
    char buffer[BUFFER_SIZE];
    int n;

    n = read(server->poll_fds[i].fd, buffer, sizeof(buffer) - 1);
    if (n <= 0) {
        remove_client(server, i);
        return;
    }
    buffer[n] = '\0';
    handle_command(&server->clients[i], buffer);
    if (server->clients[i].control_fd == -1) {
        server->poll_fds[i] = server->poll_fds[server->nb_clients - 1];
        server->clients[i] = server->clients[server->nb_clients - 1];
        server->nb_clients--;
    }
}

static void handle_clients(server_t *server)
{
    for (int i = 1; i < server->nb_clients; i++) {
        if (server->poll_fds[i].revents & (POLLERR | POLLHUP)) {
            remove_client(server, i);
            i--;
            continue;
        }
        if (server->poll_fds[i].revents & POLLIN) {
            handle_client_data(server, i);
            i--;
        }
    }
}

static int init_server_socket(int port)
{
    struct sockaddr_in addr = {AF_INET, htons(port), {INADDR_ANY}, {}};
    int server_socket;
    int opt = 1;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
        return -1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return -1;
    if (listen(server_socket, 10) < 0)
        return -1;
    return server_socket;
}

static void run_server(server_t *server, int server_socket)
{
    while (1) {
        poll(server->poll_fds, server->nb_clients, -1);
        if (server->poll_fds[0].revents & POLLIN)
            handle_new_connection(server, server_socket);
        handle_clients(server);
    }
}

int main(int argc, char **argv)
{
    static server_t server;
    int server_socket;
    struct stat st;

    if (argc != 3)
        return 84;
    server_socket = init_server_socket(atoi(argv[1]));
    if (server_socket < 0)
        return 84;
    server.nb_clients = 1;
    server.poll_fds[0].fd = server_socket;
    server.poll_fds[0].events = POLLIN;
    if (!realpath(argv[2], &(server.clients[0].cwd)) || stat(server.clients[0].cwd, &st) < 0 || !S_ISDIR(st.st_mode))
        return 84;
    printf("Serveur FTP démarré sur le port %s\n", argv[1]);
    run_server(&server, server_socket);
    close(server_socket);
    return 0;
}
