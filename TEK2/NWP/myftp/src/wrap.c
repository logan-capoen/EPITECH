/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** wrap.c
*/
#include "myftp.h"

void wrap_quit(client_t *client, char *arg)
{
    (void)arg;
    handle_quit(client);
}

void wrap_pwd(client_t *client, char *arg)
{
    (void)arg;
    handle_pwd(client);
}

void wrap_cdup(client_t *client, char *arg)
{
    (void)arg;
    handle_cdup(client);
}
