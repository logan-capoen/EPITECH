/*
** EPITECH PROJECT, 2025
** get_value
** File description:
** get_value function for cuddle lib
*/

#include "dataframe.h"
#include <stdio.h>

void *df_get_value(dataframe_t *dataframe, int row, const char *column)
{
    int index = get_column_index(dataframe, column);
    data_t *current = dataframe->data;

    if (index == -1)
        return NULL;
    if (row >= dataframe->nb_rows)
        return NULL;
    for (int i = 0; i < row; i++)
        current = current->next;
    return current->array[index];
}

int sizeof_value(column_type_t type)
{
    if (type == INT)
        return sizeof(int);
    if (type == UINT)
        return sizeof(unsigned int);
    if (type == FLOAT)
        return sizeof(float);
    if (type == BOOL)
        return sizeof(bool);
    return sizeof(char *);
}

void **df_get_values(dataframe_t *dataframe, const char *column)
{
    int index = get_column_index(dataframe, column);
    data_t *current = dataframe->data;
    void **values = malloc(sizeof(void *) *dataframe->nb_rows);
    int i = 0;
    int type_size = sizeof_value(dataframe->column_types[index]);

    if (!values || index == -1)
        return NULL;
    for (; current != NULL; i++) {
        values[i] = malloc(type_size);
        if (!values[i])
            return NULL;
        values[i] = current->array[index];
        current = current->next;
    }
    values[i] = NULL;
    return values;
}

static
int cmp_by_type(column_type_t type, void *value, void **unique_values, int i)
{
    if (type == INT)
        if (*(int *)unique_values[i] == *(int *)value)
            return 1;
    if (type == UINT)
        if (*(unsigned int *)unique_values[i] == *(unsigned int *)value)
            return 1;
    if (type == FLOAT)
        if (*(float *)unique_values[i] == *(float *)value)
            return 1;
    if (type == BOOL)
        if (*(bool *)unique_values[i] == *(bool *)value)
            return 1;
    if (strcmp((char *)unique_values[i], (char *)value) == 0)
        return 1;
    return 0;
}

static
int in_uniques_values(void *value, void **unique_values, column_type_t type)
{
    for (int i = 0; unique_values[i] != NULL; i++) {
        if (cmp_by_type(type, value, unique_values, i) == 1)
            return 1;
    }
    return 0;
}

void **df_get_unique_values(dataframe_t *dataframe, const char *column)
{
    void **values = df_get_values(dataframe, column);
    void **unique_values = malloc(sizeof(void *) *dataframe->nb_rows);
    int i = 0;
    int j = 0;

    if (!values || !unique_values)
        return NULL;
    for (int a = 0; a < dataframe->nb_rows; a++)
        unique_values[a] = NULL;
    for (; values[i] != NULL; i++) {
        if (in_uniques_values(values[i], unique_values, dataframe->column_types
            [get_column_index(dataframe, column)]) == 0) {
            unique_values[j] = malloc(sizeof_value(dataframe->column_types
            [get_column_index(dataframe, column)]));
            unique_values[j] = values[i];
            j++;
        }
    }
    unique_values[j] = NULL;
    return unique_values;
}
