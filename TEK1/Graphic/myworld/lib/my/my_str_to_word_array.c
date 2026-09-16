/*
** EPITECH PROJECT, 2025
** MiniShell1
** File description:
** Put a string into a double array
*/

/**
 * @file str_to_word_array.c
 * @brief Convert a string into a double array
 *
 * Contains the functions that will create a double array with a
 * given string and a custom delimiter to know how to split it.
 */

#include "../../include/my.h"

/**
 * @brief Parse a word and insert it into the double array
 * @param *word_array Some settings to know how and where to split
 * @param *i The index of the begining of the word
 * @param *str The global string to parse
 * @param insert The index of where to insert in the double array
 */
void put_word_in_array(struct word_array *word_array,
    int *i, char *str, int insert)
{
    char *storage = NULL;
    int index = 0;
    int len = 0;

    for (int j = *i; str[j] != word_array->delimiter && str[j] != '\0'; j++) {
        len++;
    }
    storage = malloc(sizeof(char) * (len + 1));
    if (storage == NULL) {
        free(word_array->tab);
        return;
    }
    for (int j = *i; str[j] != word_array->delimiter && str[j] != '\0'; j++) {
        storage[index] = str[j];
        index++;
    }
    storage[len] = '\0';
    word_array->tab[insert] = storage;
    *i += len;
}

/**
 * @brief Check for some memory problems and initiate the insertion of a word
 * @param *word_array Some settings to know how and where to split
 * @param *tmp_i The index of the begining of the word
 * @param *str The global string to parse
 * @return int A boolean to know if continuation or not
 */
int check_mem(struct word_array *word_array, int *tmp_i, char *str)
{
    if (word_array->tab == NULL)
        return 0;
    put_word_in_array(word_array, tmp_i, str, 0);
    if (word_array->tab == NULL) {
        for (int i = 0; word_array->tab[i] != NULL; i++)
            free(word_array->tab[i]);
        return 0;
    }
    return 1;
}

/**
 * @brief Creates a double array from a string
 * @param *str The global string to parse
 * @param delimiter The char to know how to split the string
 * @return char** The double array created
 */
char **str_in_array(char *str, char delimiter)
{
    int word_counter = 1;
    int tmp_i = 0;
    int insert_index = 1;
    struct word_array word_array = {NULL, delimiter};

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == delimiter && (str[i + 1] != delimiter))
            word_counter++;
    word_array.tab = malloc(sizeof(char *) * (word_counter + 1));
    if (word_array.tab == NULL || !check_mem(&word_array, &tmp_i, str))
        return NULL;
    for (int i = tmp_i; insert_index < word_counter; i++) {
        if (str[i] == delimiter)
            continue;
        put_word_in_array(&word_array, &i, str, insert_index);
        insert_index++;
    }
    word_array.tab[word_counter] = NULL;
    return word_array.tab;
}
