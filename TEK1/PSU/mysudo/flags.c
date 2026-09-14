/*
** EPITECH PROJECT, 2025
** glags.c
** File description:
** flags
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "functions_sudo.h"

int display_flag_h(void)
{
    write(1, "usage: ./my_sudo -h\nusage: ./my_sudo"
        " [-ugEs] [command [args ...]]\n", 67);
    return 0;
}

static char *verify_user(char *user)
{
    char line[256];
    char username[30];
    char *uid = malloc(sizeof(char) * 30);
    FILE *file = fopen("/etc/passwd", "r");

    if (!file)
        return "";
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]:%*[^:]:%[^:]:", username, uid) != 2)
            continue;
        if (strcmp(user, username) == 0) {
            fclose(file);
            return uid;
        }
    }
    fclose(file);
    return "";
}

int handle_flag_u(char *user)
{
    char *uid = verify_user(user);
    int uid_int = atoi(uid);

    if (uid == "") {
        dprintf(2, "my_sudo: unknown user %s\n", user);
        exit(84);
    }
    //setuid(uid_int);
    return 2;
}

static char *verify_group(const char *group)
{
    char line[256];
    char group_name[30];
    char *gid = malloc(30);
    FILE *file = fopen("/etc/group", "r");

    if (file == NULL)
        return "";
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]:%*[^:]:%[^:]:", group_name, gid) != 2)
            continue;
        if (strcmp(group, group_name) == 0) {
            fclose(file);
            return gid;
        }
    }
    fclose(file);
    free(gid);
    return "";
}

int handle_flag_g(const char *group_name)
{
    char *gid = verify_group(group_name);

    if (gid == "") {
        dprintf(2, "my_sudo: unknown group %s\n", group_name);
        exit(84);
    }
    //setgid(atoi(uid));
    return 2;
}

int handle_flag_s(void)
{
    struct passwd *pw;
    char *shell = getenv("SHELL");

    if (!shell)
        shell = "/bin/sh";
    for (int i = 0; i < 3; i++) {
        if (check_password(find_hash()) == 1) {
            execl(shell, shell, "-i", (char *)NULL);
            break;
        }
        displaying(i);
    }
    return 1;
}
