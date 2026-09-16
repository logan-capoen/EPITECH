/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** wrap2.c
*/
#include "myftp.h"

void wrap_pasv(client_t *client, char *arg)
{
    (void)arg;
    handle_pasv(client);
}

void wrap_help(client_t *client, char *arg)
{
    (void)arg;
    handle_help(client);
}

void wrap_noop(client_t *client, char *arg)
{
    (void)arg;
    handle_noop(client);
}
