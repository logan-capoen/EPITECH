/*
** EPITECH PROJECT, 2025
** head.c
** File description:
** c file for head function
*/

#include "dataframe.h"

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *head = malloc(sizeof(dataframe_t));
    data_t *current;

    if (!head || nb_rows < 0 || !dataframe)
        return NULL;
    current = dataframe->data;
    if (nb_rows > dataframe->nb_rows)
        nb_rows = dataframe->nb_rows;
    head->column_names = dataframe->column_names;
    head->column_types = dataframe->column_types;
    head->nb_columns = dataframe->nb_columns;
    head->nb_rows = nb_rows;
    head->separator = dataframe->separator;
    head->data = NULL;
    for (int i = 0; i < nb_rows; i++) {
        add_data(&head->data, current->array);
        current = current->next;
    }
    return head;
}
