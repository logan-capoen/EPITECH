/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** shape
*/

#include "dataframe.h"

dataframe_shape_t df_shape(dataframe_t *dataframe)
{
    dataframe_shape_t shape;

    if (!dataframe)
        return (dataframe_shape_t){0, 0};
    shape.nb_columns = dataframe->nb_columns;
    shape.nb_rows = dataframe->nb_rows;
    return shape;
}
