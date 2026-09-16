/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** filtering
*/

#include "dataframe.h"

static void set_data(dataframe_t *dataframe,
    data_t *current, data_t **new_data, dataframe_t *new)
{
    void **new_array = malloc(sizeof(void *) * dataframe->nb_columns);

    if (!new_array)
        return;
    for (int i = 0; i < dataframe->nb_columns; i++)
        new_array[i] = current->array[i];
    add_data(new_data, new_array);
    new->nb_rows++;
}

dataframe_t *df_filter(dataframe_t *dataframe,
    const char *column, bool (*filter_func)(void *value))
{
    dataframe_t *new = malloc(sizeof(dataframe_t));
    data_t *current = dataframe->data;
    data_t *new_data = NULL;
    int index_column = 0;

    if (!new || !dataframe)
        return NULL;
    new->column_names = dataframe->column_names;
    new->column_types = dataframe->column_types;
    new->nb_columns = dataframe->nb_columns;
    new->separator = dataframe->separator;
    new->nb_rows = 0;
    index_column = get_column_index(dataframe, column);
    if (index_column == -1)
        return NULL;
    for (; current != NULL; current = current->next)
        if (filter_func(current->array[index_column]))
            set_data(dataframe, current, &new_data, new);
    new->data = new_data;
    return new;
}
