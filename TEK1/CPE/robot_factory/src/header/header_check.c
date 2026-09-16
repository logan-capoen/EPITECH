/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** header_check
*/

#include "op.h"

static char **extract_header(char **arr)
{
    int arr_size = 0;
    char **header = NULL;

    while (arr[arr_size] != NULL)
        arr_size++;
    header = malloc(sizeof(char *) * (arr_size + 1));
    if (header == NULL)
        return NULL;
    for (int i = 0; i < arr_size; i++)
        header[i] = NULL;
    for (int i = 0; arr[i] != NULL && check_label(arr[i]) == 0 &&
        check_instruction(arr[i]) == -1; i++) {
        header[i] = my_strdup(arr[i]);
    }
    return header;
}

char *clean_str_quote(char *str)
{
    char *new = str + 1;

    str[my_strlen(str) - 1] = '\0';
    return new;
}

static int analyze_header(char **header, int len)
{
    if (len == 2) {
        if (my_strcmp(header[0], NAME_CMD_STRING) == 0 &&
            my_strlen(header[1]) <= PROG_NAME_LENGTH)
            return 1;
    }
    if (len == 4) {
        if ((my_strcmp(header[0], NAME_CMD_STRING) == 0 &&
            my_strlen(header[1]) <= PROG_NAME_LENGTH) &&
            (my_strcmp(header[2], COMMENT_CMD_STRING) == 0 &&
            my_strlen(header[3]) <= COMMENT_LENGTH))
            return 1;
    }
    return 0;
}

char **check_header(char **arr)
{
    char **header = extract_header(arr);
    int len = 0;
    int passed = 0;

    for (; header[len] != NULL; len++);
    if (len != 2 && len != 4)
        return NULL;
    passed = analyze_header(header, len);
    if (passed) {
        header[1] = clean_str_quote(header[1]);
        if (len == 4)
            header[3] = clean_str_quote(header[3]);
        return header;
    }
    return NULL;
}
