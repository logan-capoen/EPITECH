/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** info
*/

#include "dataframe.h"

char *type_to_str(column_type_t type)
{
    if (type == BOOL)
        return "bool";
    if (type == INT)
        return "int";
    if (type == UINT)
        return "unsigned int";
    if (type == STRING)
        return "string";
    if (type == FLOAT)
        return "float";
    return NULL;
}

void df_info(dataframe_t *dataframe)
{
    if (!dataframe)
        return;
    printf("%i columns:\n", dataframe->nb_columns);
    for (int i = 0; dataframe->column_names[i] != NULL; i++)
        printf("- %s: %s\n", dataframe->column_names[i],
            type_to_str(dataframe->column_types[i]));
}
