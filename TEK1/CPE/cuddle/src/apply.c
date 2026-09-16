/*
** EPITECH PROJECT, 2025
** apply
** File description:
** apply function for cuddle library
*/

#include "dataframe.h"
#include <stdlib.h>

dataframe_t *allocate_and_initialize(dataframe_t *dataframe)
{
    dataframe_t *new = malloc(sizeof(dataframe_t));

    if (!new || !dataframe)
        return NULL;
    new->column_names = dataframe->column_names;
    new->column_types = dataframe->column_types;
    new->nb_columns = dataframe->nb_columns;
    new->nb_rows = 0;
    new->separator = dataframe->separator;
    new->data = NULL;
    return new;
}

void process_rows(dataframe_t *dataframe, dataframe_t *new, int index_column,
    void *(*apply_func)(void *))
{
    void **new_array;

    for (data_t *current = dataframe->data; current != NULL;
    current = current->next) {
        new_array = malloc(sizeof(void *) * dataframe->nb_columns);
        if (!new_array)
            return;
        for (int i = 0; i < dataframe->nb_columns; i++) {
            new_array[i] = (i == index_column) ?
            apply_func(current->array[i]) : current->array[i];
        }
        add_data(&new->data, new_array);
        new->nb_rows++;
    }
}

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value))
{
    dataframe_t *new = allocate_and_initialize(dataframe);
    int index_column = get_column_index(dataframe, column);

    if (!new)
        return NULL;
    process_rows(dataframe, new, index_column, apply_func);
    return new;
}
