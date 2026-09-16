/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** manage_char_array.c
*/

/**
 * @file manage_char_array.c
 * @brief Utility functions to manage arrays of strings.
 *
 * This file contains helper functions to manage dynamically allocated
 * arrays of strings, including freeing, duplicating, and deleting elements.
 */

#include "utilities.h"

/**
 * @brief Frees a dynamically allocated array of strings.
 *
 * This function iterates through the array, freeing each string, and then
 * frees the array itself.
 *
 * @param array The array of strings to free.
 */
void free_array(char **array)
{
    for (int i = 0; array && array[i]; i++)
        free(array[i]);
    if (array)
        free(array);
}

/**
 * @brief Gets the length of an array of strings.
 *
 * This function calculates the number of
 * elements in the given array of strings.
 *
 * @param array The array of strings.
 * @return The number of elements in the array.
 */
static int get_array_len(char **array)
{
    int len = 0;

    for (; array && array[len]; len++);
    return len;
}

/**
 * @brief Duplicates an array of strings.
 *
 * This function creates a new array of strings that is a deep copy of the
 * source array. Each string in the source array is duplicated.
 *
 * @param src The source array of strings to duplicate.
 * @return A newly allocated array of strings, or NULL on failure.
 */
char **dup_array(char **src)
{
    int len_array = get_array_len(src);
    char **dest = malloc(sizeof(char *) * (len_array + 1));

    if (!dest)
        return NULL;
    for (int i = 0; i < len_array + 1; i++)
        dest[i] = NULL;
    for (int i = 0; i < len_array; i++) {
        dest[i] = strdup(src[i]);
        if (!dest[i]) {
            free_array(dest);
            return NULL;
        }
    }
    return dest;
}

/**
 * @brief Deletes an element from an array of strings.
 *
 * This function removes the element at the specified index from the array
 * and shifts the remaining elements to fill the gap. The array is resized
 * accordingly.
 *
 * @param array Pointer to the array of strings.
 * @param index The index of the element to delete.
 * @return 0 on success, 1 on failure (e.g., invalid index
 * or memory allocation failure).
 */
int del_elt(char ***array, int index)
{
    int len_array = get_array_len(*array);
    char **array_tmp = NULL;

    if (index < 0 || index + 1 > len_array)
        return 1;
    array_tmp = malloc(sizeof(char *) * len_array);
    if (!array_tmp)
        return 1;
    for (int i = 0; (*array)[i]; i++)
        if (i != index)
            array_tmp[i - (i > index)] = (*array)[i];
    array_tmp[len_array - 1] = NULL;
    free((*array)[index]);
    free(*array);
    *array = array_tmp;
    return 0;
}
