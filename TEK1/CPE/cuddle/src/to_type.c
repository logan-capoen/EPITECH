/*
** EPITECH PROJECT, 2025
** to_type
** File description:
** to_type function for cuddle library
*/

#include "dataframe.h"

static int is_valid_column_type(column_type_t type)
{
    if (!type || type == UNDEFINED)
        return 0;
    switch (type) {
        case INT:
        case FLOAT:
        case STRING:
        case UINT:
        case BOOL:
            return 1;
        default:
            return 0;
    }
}

static int init_dataframe(dataframe_t *new, dataframe_t *dataframe, int index,
    column_type_t downcast)
{
    if (!dataframe || index == -1 || !is_valid_column_type(downcast))
        return 84;
    new->column_names = dataframe->column_names;
    new->column_types = dataframe->column_types;
    new->column_types[index] = downcast;
    new->nb_columns = dataframe->nb_columns;
    new->nb_rows = 0;
    new->separator = dataframe->separator;
    new->data = NULL;
    return 0;
}

static
int check_able_to_conv(void *value, column_type_t downcast, int i, int index)
{
    column_type_t type = found_type((char *)value);

    if (i != index)
        return index;
    if (downcast == INT)
        if (type == UINT)
            return index;
    if (downcast == STRING)
        return index;
    if (downcast != found_type((char *)value))
        return -1;
    return index;
}

dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
    column_type_t downcast)
{
    int index = get_column_index(dataframe, column);
    data_t *current = dataframe->data;
    void **new_array;
    dataframe_t *new = malloc(sizeof(dataframe_t));

    if (!new || init_dataframe(new, dataframe, index, downcast) == 84)
        return NULL;
    for (; current != NULL; current = current->next) {
        new_array = malloc(sizeof(void *) * dataframe->nb_columns);
        for (int i = 0; i < dataframe->nb_columns; i++) {
            index = check_able_to_conv(current->array[i], downcast, i, index);
            new_array[i] = (i == index) ? convert_type
                ((char *)current->array[i], i, new) : current->array[i];
        }
        if (index == -1)
            return NULL;
        add_data(&new->data, new_array);
        new->nb_rows++;
    }
    return new;
}
