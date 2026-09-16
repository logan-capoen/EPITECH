/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** tail
*/

#include "dataframe.h"

dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *newdataframe = malloc(sizeof(dataframe_t));
    data_t *current = dataframe->data;
    data_t *new = NULL;

    if (newdataframe == NULL || nb_rows < 0 || !dataframe)
        return NULL;
    if (nb_rows > dataframe->nb_rows)
        nb_rows = dataframe->nb_rows;
    newdataframe->nb_rows = nb_rows;
    newdataframe->nb_columns = dataframe->nb_columns;
    newdataframe->column_names = dataframe->column_names;
    newdataframe->column_types = dataframe->column_types;
    newdataframe->separator = dataframe->separator;
    for (int i = 0; i < dataframe->nb_rows - nb_rows; i++)
        current = current->next;
    for (; current != NULL; current = current->next)
        add_data(&new, current->array);
    newdataframe->data = new;
    return newdataframe;
}
