/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** describe
*/

#include "dataframe.h"

static double convert_to_type(void *value, int type)
{
    if (type == INT)
        return (double)*(int *)value;
    if (type == UINT)
        return (double)*(unsigned int *)value;
    if (type == FLOAT)
        return (double)*(float *)value;
    return 0;
}

static double
get_standard_deviation(double mean, dataframe_t *dataframe, int i)
{
    double sum = 0;
    data_t *current = dataframe->data;

    for (int j = 0; j < dataframe->nb_rows; j++) {
        sum += pow(convert_to_type(current->array[i],
            dataframe->column_types[i]) - mean, 2);
        current = current->next;
    }
    return sqrt(sum / dataframe->nb_rows);
}

static double get_mean(dataframe_t *dataframe, int i, double *min, double *max)
{
    double sum = 0;
    double value = 0;
    data_t *current = dataframe->data;

    for (int j = 0; j < dataframe->nb_rows; j++) {
        value = convert_to_type(current->array[i], dataframe->column_types[i]);
        if (*min > value)
            *min = value;
        if (*max < value)
            *max = value;
        sum += value;
        current = current->next;
    }
    return sum / dataframe->nb_rows;
}

static void get_info(dataframe_t *dataframe, int i)
{
    double min = convert_to_type(dataframe->data->array[i],
        dataframe->column_types[i]);
    double max = convert_to_type(dataframe->data->array[i],
        dataframe->column_types[i]);
    double mean = get_mean(dataframe, i, &min, &max);

    printf("Column: %s\n", dataframe->column_names[i]);
    printf("Count: %i\n", dataframe->nb_rows);
    printf("Mean: %.2f\n", mean);
    printf("Std: %.2f\n", get_standard_deviation(mean, dataframe, i));
    printf("Min: %.2f\n", min);
    printf("Max: %.2f\n", max);
}

void df_describe(dataframe_t *dataframe)
{
    if (!dataframe)
        return;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (dataframe->column_types[i] == INT ||
            dataframe->column_types[i] == UINT ||
            dataframe->column_types[i] == FLOAT)
            get_info(dataframe, i);
    }
}
