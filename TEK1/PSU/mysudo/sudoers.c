/*
** EPITECH PROJECT, 2025
** sudoers.c
** File description:
** sudoers
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "functions_sudo.h"

static char **get_user_groups(char *username, int *num_groups)
{
    FILE *file = fopen("/etc/group", "r");
    char line[256];
    char group_name[30];
    char *members;
    char **groups = NULL;

    if (file == NULL)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]:%*[^:]:%*[^:]:%[^\n]"
            , group_name, members) < 2)
            continue;
        if (strstr(members, username)) {
            groups = realloc(groups, (*num_groups + 1) * sizeof(char *));
            groups[*num_groups] = strdup(group_name);
            (*num_groups)++;
        }
    }
    fclose(file);
    return groups;
}

static int check_groups(int num_groups, char **groups, char *line, FILE *file)
{
    for (int i = 0; i < num_groups; i++) {
        if (strstr(line, groups[i])) {
            fclose(file);
            return 1;
        }
    }
    return 0;
}

int in_sudoers(char *username)
{
    FILE *file = fopen("/etc/sudoers", "r");
    char line[256];
    int num_groups = 0;
    char **groups = get_user_groups(username, &num_groups);

    if (!file)
        return 84;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, username)) {
            fclose(file);
            return 1;
        }
        if (check_groups(num_groups, groups, line, file))
            return 1;
    }
    fclose(file);
    return 0;
}
