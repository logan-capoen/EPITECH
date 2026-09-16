/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** check_type
*/

#include "dataframe.h"

static int is_integer(const char *str)
{
    if (atoi(str) < 0)
        return 1;
    return 0;
}

static int is_float(const char *str)
{
    int dot_seen = 0;

    if (str[0] == '-' || str[0] == '+')
        str++;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.')
            dot_seen++;
        if (dot_seen > 1)
            return 0;
        if (!isdigit(str[i]) && str[i] != '.')
            return 0;
    }
    return dot_seen;
}

static int is_bool(const char *str)
{
    return (strcmp(str, "true") == 0 || strcmp(str, "false") == 0 ||
            strcmp(str, "TRUE") == 0 || strcmp(str, "FALSE") == 0);
}

static int is_unsigned_int(const char *str)
{
    int result = atoi(str);

    if (result < 0)
        return 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
            return 0;
    return 1;
}

column_type_t found_type(char *str)
{
    if (is_bool(str)) {
        return BOOL;
    }
    if (is_unsigned_int(str)) {
        return UINT;
    }
    if (is_float(str)) {
        return FLOAT;
    }
    if (is_integer(str)) {
        return INT;
    }
    return STRING;
}

int define_type(dataframe_t *head, char *line, char separator)
{
    char **tmp = my_str_to_word_array(line, separator);

    for (int i = 0; i < head->nb_columns; i++) {
        if (head->column_types[i] == UNDEFINED)
            head->column_types[i] = found_type(tmp[i]);
        if ((head->column_types[i] == UINT && found_type(tmp[i]) == INT))
            head->column_types[i] = INT;
        if ((head->column_types[i] == INT && found_type(tmp[i]) == UINT))
            continue;
        if (head->column_types[i] != found_type(tmp[i]))
            head->column_types[i] = STRING;
    }
    return 0;
}

int get_column_index(dataframe_t *dataframe, const char *column)
{
    if (!dataframe || !column)
        return -1;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0)
            return i;
    }
    return -1;
}
