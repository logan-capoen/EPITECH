/*
** EPITECH PROJECT, 2025
** main
** File description:
** main for sudo
*/

#include <unistd.h>
#include <crypt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions_sudo.h"
#include <termios.h>
#include <grp.h>

int check_password(const char *password_hash)
{
    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;

    printf("[my_sudo] password for %s:\n",
        get_username(int_to_str(getuid()), "/etc/passwd"));
    hide_input_mode();
    read = getline(&buffer, &len, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    restore_input_mode();
    if (strcmp(crypt(buffer, password_hash), password_hash) == 0)
        return 1;
    return 0;
}

static int my_exec(char **argv, int index, int env)
{
    if (env == 0)
        return execlp(argv[index], "", argv[index + 1], NULL);
    return execvp(argv[index], &argv[index]);
}

static char *search_username(char *uid, char *username, FILE *file)
{
    char line[256];
    char file_username[30];
    char file_uid[30];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]:%*[^:]:%[^:]:", file_username, file_uid) != 2)
            continue;
        if (strcmp(uid, file_uid) == 0) {
            strncpy(username, file_username, 30);
            username[29] = '\0';
            fclose(file);
            return username;
        }
    }
    fclose(file);
    free(username);
    return "";
}

static char *search_hash(char *username, char *hash, FILE *file)
{
    char line[256];
    char file_username[30];
    char file_hash[400];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]:%[^:]:", file_username, file_hash) != 2)
            continue;
        if (strcmp(username, file_username) == 0) {
            strcpy(hash, file_hash);
            hash[73] = '\0';
            fclose(file);
            return hash;
        }
    }
    fclose(file);
    free(hash);
    return "";
}

char *get_username(char *uid, char *pathfile)
{
    char *username = malloc(sizeof(char) * 400);
    FILE *file = fopen(pathfile, "r");

    if (!uid || uid[0] == '\0')
        return "";
    if (!username)
        return "";
    if (!file) {
        free(username);
        return "";
    }
    if (pathfile[5] == 's'){
        return search_hash(uid, username, file);
    }
    return search_username(uid, username, file);
}

static int handle_main(int argc, int len_av, char **argv, int env)
{
    char *username = get_username(int_to_str(getuid()), "/etc/passwd");

    if (argc == 1)
        display_flag_h();
    if (argc < 2 + len_av)
        return 84;
    if (strcmp(username, "root") == 0) {
        my_exec(argv, len_av + 1, env);
        exit(0);
    }
    return 0;
}

int main(int argc, char **argv)
{
    int uid = getuid();
    int env = 0;
    int len_av = parse_options(argc, argv, &env);

    if (geteuid() != 0) {
        dprintf(2, "permission denied\n");
        return 84;
    }
    if (handle_main(argc, len_av, argv, env) == 84)
        return 84;
    for (int i = 0; i < 3; i++) {
        if (check_password(find_hash()) == 1) {
            setgid(0);
            setgroups(0, NULL);
            setuid(0);
            return my_exec(argv, len_av + 1, env);
        }
        displaying(i);
    }
    return 0;
}
