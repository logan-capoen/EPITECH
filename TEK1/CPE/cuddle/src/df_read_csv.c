/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_read_csv
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdbool.h>

static int is_empty(const char *file)
{
    struct stat fileStat;

    if (!file)
        return 0;
    if (stat(file, &fileStat) != 0)
        return 0;
    if (fileStat.st_size == 0)
        return 0;
    return 1;
}

static int extract_info(dataframe_t *head, char *line, char separator)
{
    int i = 0;

    head->separator = separator;
    head->column_names = my_str_to_word_array(line, separator);
    for (; head->column_names[i] != NULL; i++);
    head->nb_columns = i;
    return 0;
}

int add_data(data_t **data, void **array)
{
    data_t *node = malloc(sizeof(data_t));
    data_t *current = *data;

    if (!node)
        return -1;
    node->array = array;
    node->next = NULL;
    if (current == NULL) {
        *data = node;
        return 0;
    }
    for (; current->next != NULL; current = current->next);
    current->next = node;
    return 0;
}

static void initialize_type(dataframe_t *head)
{
    head->column_types = malloc(sizeof(column_type_t) * head->nb_columns);
    if (!head->column_types)
        return;
    for (int i = 0; i < head->nb_columns; i++)
        head->column_types[i] = UNDEFINED;
}

static int set_type(FILE *fd, data_t **data, dataframe_t *head, char separator)
{
    int read = 0;
    int nb_rows = 0;
    char *line = NULL;
    size_t len = 0;

    read = getline(&line, &len, fd);
    for (; read != -1; nb_rows++) {
        define_type(head, line, separator);
        add_data(data, (void **)my_str_to_word_array(line, separator));
        read = getline(&line, &len, fd);
    }
    free(line);
    return nb_rows;
}

static int handle_error(const char *filename)
{
    if (!is_empty(filename))
        return 84;
    if (strcmp(".csv", filename + strlen(filename) - 4) != 0)
        return 84;
    return 0;
}

void *convert_type(char *value, int column, dataframe_t *data)
{
    int *int_value;
    unsigned int *uint_value;
    float *float_value;

    if (data->column_types[column] == INT) {
        int_value = malloc(sizeof(int));
        *int_value = atoi(value);
        return int_value;
    }
    if (data->column_types[column] == UINT) {
        uint_value = malloc(sizeof(unsigned int));
        *uint_value = (unsigned int)strtoul(value, NULL, 10);
        return uint_value;
    }
    if (data->column_types[column] == FLOAT) {
        float_value = malloc(sizeof(float));
        *float_value = atof(value);
        return float_value;
    }
    return value;
}

static void browse_data(dataframe_t *data)
{
    data_t *current = data->data;

    for (; current != NULL; current = current->next) {
        for (int i = 0; i < data->nb_columns; i++) {
            current->array[i] =
                convert_type((char *)current->array[i], i, data);
        }
    }
}

static char init_new_separator(const char *separator)
{
    char new_separator = ',';

    if (separator == NULL)
        return new_separator;
    return separator[0];
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    dataframe_t *head = malloc(sizeof(dataframe_t));
    data_t *data = NULL;
    char new_separator = init_new_separator(separator);

    if (!head || handle_error(filename) == 84)
        return NULL;
    read = getline(&line, &len, file);
    if (read == -1)
        return NULL;
    extract_info(head, line, new_separator);
    initialize_type(head);
    head->nb_rows = set_type(file, &data, head, new_separator);
    head->data = data;
    browse_data(head);
    fclose(file);
    return head;
}
