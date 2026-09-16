/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** sorting
*/

#include "dataframe.h"

dataframe_t *duplicate_data(dataframe_t *dataframe)
{
    dataframe_t *duplicate = malloc(sizeof(dataframe_t));
    data_t *current = dataframe->data;
    data_t *new_data = NULL;
    void **new_array = NULL;

    if (!duplicate || !dataframe)
        return NULL;
    duplicate->column_names = dataframe->column_names;
    duplicate->column_types = dataframe->column_types;
    duplicate->nb_columns = dataframe->nb_columns;
    duplicate->nb_rows = dataframe->nb_rows;
    duplicate->separator = dataframe->separator;
    for (; current != NULL; current = current->next) {
        new_array = malloc(sizeof(void *) * dataframe->nb_columns);
        for (int i = 0; i < dataframe->nb_columns; i++)
            new_array[i] = current->array[i];
        add_data(&new_data, new_array);
    }
    duplicate->data = new_data;
    return duplicate;
}

void swap_node(data_t **head, sort_t *sort)
{
    if (sort->prev)
    sort->prev->next = sort->next;
    else
        *head = sort->next;
    sort->curr->next = sort->next->next;
    sort->next->next = sort->curr;
}

void bubble_sort(sort_t *sort, int index_column,
    bool (*sort_func)(void *value1, void *value2))
{
    if (sort_func(sort->curr->array[index_column],
        sort->next->array[index_column])) {
        swap_node(&(sort->sorted)->data, sort);
        sort->swapped = true;
        if (sort->prev == NULL) {
            sort->prev = sort->next;
        } else {
            sort->prev = sort->prev->next;
        }
        sort->next = sort->curr->next;
    } else {
        sort->prev = sort->curr;
        sort->curr = sort->next;
        sort->next = sort->next->next;
    }
}

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2))
{
    sort_t *sort = malloc(sizeof(sort_t));
    int index_column = 0;

    sort->sorted = duplicate_data(dataframe);
    if (!sort->sorted)
        return NULL;
    index_column = get_column_index(dataframe, column);
    if (index_column == -1)
        return NULL;
    do {
        sort->swapped = false;
        sort->prev = NULL;
        sort->curr = sort->sorted->data;
        sort->next = sort->curr->next;
        while (sort->next != NULL) {
            bubble_sort(sort, index_column, sort_func);
        }
    } while (sort->swapped);
    return sort->sorted;
}
