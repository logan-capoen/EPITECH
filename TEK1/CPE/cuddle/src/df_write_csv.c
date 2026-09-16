/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_write_csv
*/

#include "dataframe.h"

static void put_separator(dataframe_t *df, int i, FILE *file)
{
    if (i != df->nb_columns - 1)
        fprintf(file, "%c", df->separator);
}

void print_one_line(FILE *file, data_t *current, dataframe_t *df, int j)
{
    switch (df->column_types[j]) {
    case INT:
        fprintf(file, "%d", *(int *)current->array[j]);
        break;
    case UINT:
        fprintf(file, "%u", *(unsigned int *)current->array[j]);
        break;
    case FLOAT:
        fprintf(file, "%.2f", *(float *)current->array[j]);
        break;
    default:
        fprintf(file, "%s", (char *)current->array[j]);
    }
    put_separator(df, j, file);
    return;
}

static int check_file(FILE **file, const char *filename)
{
    *file = fopen(filename, "w");
    if (!*file)
        return 84;
    return 0;
}

int df_write_csv(dataframe_t *df, const char *filename)
{
    FILE *file;
    data_t *current = NULL;

    if (!df || check_file(&file, filename) == 84)
        return 84;
    file = fopen(filename, "w");
    current = df->data;
    for (int i = 0; i < df->nb_columns; i++) {
        fprintf(file, "%s", df->column_names[i]);
        put_separator(df, i, file);
    }
    fprintf(file, "\n");
    for (; current != NULL; current = current->next) {
        for (int j = 0; j < df->nb_columns; j++) {
            print_one_line(file, current, df, j);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}
