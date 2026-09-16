/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** main.h
*/
#ifndef MYFTP_H
    #define MYFTP_H

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <poll.h>
    #include <string.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <time.h>
    #include <pwd.h>
    #include <grp.h>

    #define MAX_CLIENTS 5000
    #define BUFFER_SIZE 4096

typedef enum {
    STATE_CONNECTED,
    STATE_USER_OK,
    STATE_NOT_ANONYMOUS,
    STATE_LOGGED_IN
} state_t;

typedef struct {
    int control_fd;
    int data_fd;
    char cwd[BUFFER_SIZE];
    state_t state;
    int passive_mode;
    struct sockaddr_in port_addr;
} client_t;

typedef struct {
    struct pollfd poll_fds[MAX_CLIENTS];
    client_t clients[MAX_CLIENTS];
    int nb_clients;
} server_t;

void handle_command(client_t *client, char *buffer);
void handle_user(client_t *client, char *arg);
void handle_pass(client_t *client, char *arg);
void handle_quit(client_t *client);
void handle_pwd(client_t *client);
void handle_cwd(client_t *client, char *arg);
void handle_cdup(client_t *client);
void handle_pasv(client_t *client);
void handle_port(client_t *client, char *arg);
void handle_retr(client_t *client, char *arg);
void handle_stor(client_t *client, char *arg);
void handle_list(client_t *client, char *arg);
void handle_dele(client_t *client, char *arg);
void handle_help(client_t *client);
void handle_noop(client_t *client);
int open_data_connection(client_t *client);
int create_data_socket(int *port);
void send_response(int fd, const char *msg);
int check_logged(client_t *client);
void close_data(client_t *client, int data_fd);
#endif
