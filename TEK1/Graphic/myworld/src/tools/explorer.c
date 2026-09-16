/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** explorer
*/

#include "myworld.h"

char *file_explorer_load(char *path, size_t path_len)
{
    FILE *fp = popen("zenity --file-selection --title='Select a File' "
        "2>/dev/null", "r");
    size_t len = 0;

    if (fp == NULL) {
        dprintf(2, "Failed to run Zenity\n");
        return NULL;
    }
    if (fgets(path, path_len, fp) != NULL) {
        len = strlen(path);
        if (len > 0 && path[len - 1] == '\n')
            path[len - 1] = '\0';
    } else {
        *path = 0;
        pclose(fp);
        return path;
    }
    if (fp != NULL)
        pclose(fp);
    return path;
}

char *file_explorer_save(char *path, size_t path_len)
{
    FILE *fp = popen("zenity --file-selection --save --title='Save As' "
        "--filename='untitled.legend' 2>/dev/null", "r");
    size_t len = 0;

    if (fp == NULL) {
        dprintf(2, "Failed to run Zenity");
        return NULL;
    }
    if (fgets(path, path_len, fp) != NULL) {
        len = strlen(path);
        if (len > 0 && path[len - 1] == '\n')
            path[len - 1] = '\0';
    } else {
        *path = 0;
        pclose(fp);
        return path;
    }
    pclose(fp);
    return path;
}
