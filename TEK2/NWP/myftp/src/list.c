/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** list.c
*/
#include "myftp.h"

static void format_permissions(mode_t mode, char *perm)
{
    perm[0] = S_ISDIR(mode) ? 'd' : '-';
    perm[1] = (mode & S_IRUSR) ? 'r' : '-';
    perm[2] = (mode & S_IWUSR) ? 'w' : '-';
    perm[3] = (mode & S_IXUSR) ? 'x' : '-';
    perm[4] = (mode & S_IRGRP) ? 'r' : '-';
    perm[5] = (mode & S_IWGRP) ? 'w' : '-';
    perm[6] = (mode & S_IXGRP) ? 'x' : '-';
    perm[7] = (mode & S_IROTH) ? 'r' : '-';
    perm[8] = (mode & S_IWOTH) ? 'w' : '-';
    perm[9] = (mode & S_IXOTH) ? 'x' : '-';
    perm[10] = '\0';
}

static void build_list_path(client_t *client, char *arg, char *path)
{
    if (arg == NULL || strlen(arg) == 0)
        snprintf(path, BUFFER_SIZE, "%s", client->cwd);
    else if (arg[0] == '/')
        snprintf(path, BUFFER_SIZE, "%s", arg);
    else
        snprintf(path, BUFFER_SIZE, "%s/%s", client->cwd, arg);
}

static void format_entry(struct stat *st, char *name, char *line)
{
    char perm[11];
    char date[20];
    struct tm *tm_info = localtime(&st->st_mtime);
    struct passwd *pw = getpwuid(st->st_uid);
    struct group *gr = getgrgid(st->st_gid);

    format_permissions(st->st_mode, perm);
    strftime(date, sizeof(date), "%b %d %H:%M", tm_info);
    snprintf(line, 1024, "%s %3ld %-8s %-8s %8ld %s %s\r\n",
        perm, (long)st->st_nlink,
        pw ? pw->pw_name : "unknown",
        gr ? gr->gr_name : "unknown",
        (long)st->st_size, date, name);
}

static void send_entry(int data_fd, char *path, char *name)
{
    char filepath[BUFFER_SIZE];
    char line[1024];
    struct stat st;

    snprintf(filepath, sizeof(filepath), "%s/%s", path, name);
    if (stat(filepath, &st) < 0)
        return;
    format_entry(&st, name, line);
    write(data_fd, line, strlen(line));
}

static void list_directory(DIR *dir, int data_fd, char *path)
{
    struct dirent *entry = readdir(dir);

    while (entry != NULL) {
        if (strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0)
            send_entry(data_fd, path, entry->d_name);
        entry = readdir(dir);
    }
}

static int open_list_data(client_t *client, DIR *dir)
{
    int data_fd = open_data_connection(client);

    if (data_fd >= 0)
        return data_fd;
    send_response(client->control_fd, "425 Can't open data connection.\r\n");
    closedir(dir);
    return -1;
}

void handle_list(client_t *client, char *arg)
{
    char path[BUFFER_SIZE];
    int data_fd;
    DIR *dir = NULL;

    if (!check_logged(client))
        return;
    build_list_path(client, arg, path);
    dir = opendir(path);
    if (dir == NULL)
        return send_response(client->control_fd,
            "550 No such file or directory.\r\n");
    send_response(client->control_fd,
        "150 File status okay; about to open data connection.\r\n");
    data_fd = open_list_data(client, dir);
    if (data_fd < 0)
        return;
    list_directory(dir, data_fd, path);
    closedir(dir);
    close_data(client, data_fd);
    send_response(client->control_fd, "226 Closing data connection.\r\n");
}
