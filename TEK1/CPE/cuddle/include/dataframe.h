/*
** EPITECH PROJECT, 2025
** cuddle header
** File description:
** cuddle
*/

#ifndef CUDDLE
    #define CUDDLE

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdint.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <ctype.h>
    #include <math.h>
    #include <stdbool.h>

typedef enum column_type_s {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct data_s {
    void **array;
    struct data_s *next;
} data_t;

typedef struct dataframe_s {
    int nb_rows;
    int nb_columns;
    char **column_names;
    char separator;
    column_type_t *column_types;
    data_t *data;
} dataframe_t;

typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

typedef struct sort_s {
    data_t *prev;
    data_t *curr;
    data_t *next;
    dataframe_t *sorted;
    bool swapped;
} sort_t;

char **my_str_to_word_array(char const *str, char spliter);
dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *df, const char *filename);
int define_type(dataframe_t *head, char *line, char separator);
int add_data(data_t **data, void **array);
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);
dataframe_shape_t df_shape(dataframe_t *dataframe);
void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *dataframe);
void *df_get_value(dataframe_t *dataframe, int row, const char *column);
dataframe_t *df_filter(dataframe_t *dataframe,
    const char *column, bool (*filter_func)(void *value));
void **df_get_values(dataframe_t *dataframe, const char *column);
void **df_get_unique_values(dataframe_t *dataframe, const char *column);
dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value));
dataframe_t *df_to_type(dataframe_t *dataframe,
    const char *column, column_type_t downcast);
int sizeof_value(column_type_t type);
void *convert_type(char *value, int column, dataframe_t *data);
column_type_t found_type(char *str);
dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2));
int get_column_index(dataframe_t *dataframe, const char *column);
dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by, const
    char **to_aggregate, void *(*agg_func)(void **values, int nb_values));
#endif
