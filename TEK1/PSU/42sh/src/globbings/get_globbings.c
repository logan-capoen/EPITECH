/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_globbings
*/

/**
 * @file get_globbings.c
 * @brief Functions for retrieving and managing globbing results.
 *
 * This file implements helper functions to concatenate globbing search
 * results based on a pattern.
 */

#include "globbings.h"

/**
 * @brief Compute the total length of an array of strings.
 *
 * This static function iterates over a null-terminated array of strings
 * and sums the lengths of each string.
 *
 * @param pathv Array of strings.
 * @return Total length of all strings.
 */
static unsigned long get_total_len(char **pathv)
{
    unsigned long len = 0;

    for (unsigned int i = 0; pathv[i]; i++)
        len += strlen(pathv[i]);
    return len;
}

/**
 * @brief Concatenate an array of strings into a single alloc'ed string.
 *
 * This static function concatenates all strings from the provided array,
 * separating each with a space. Memory is dynamically allocated for the new
 * string and should be freed by the caller.
 *
 * @param pathv Array of strings.
 * @return Pointer to the concatenated string, or NULL on failure.
 */
char *create_concat_array(char **pathv)
{
    unsigned long total_len = get_total_len(pathv);
    unsigned int count = 0;
    char *result = NULL;

    for (; pathv[count]; count++);
    result = malloc(total_len + count + 1);
    if (!result) {
        dprintf(2, "Allocation error\n");
        return NULL;
    }
    *result = '\0';
    for (unsigned int i = 0; pathv[i]; i++) {
        strcat(result, pathv[i]);
        strcat(result, " ");
    }
    result[total_len + count - 1] = '\0';
    return result;
}

/**
 * @brief Retrieve globbing matches as a concatenated string.
 *
 * This function uses the glob() library function to find matches for the
 * provided pattern. When matches are found, they are concatenated into a
 * single string. The allocated memory must be freed by the caller.
 *
 * @param find The globbing pattern.
 * @return Pointer to the concatenated result string, or NULL if no matches
 *         are found or on error.
 */
char *get_globbings(char *find)
{
    glob_t globuff;
    int glob_exit = 0;
    char *result = NULL;

    globuff.gl_offs = 0;
    globuff.gl_pathc = 0;
    globuff.gl_pathv = NULL;
    glob_exit = glob(find, 0, NULL, &globuff);
    if (glob_exit == 0 && globuff.gl_pathc > 0)
        result = create_concat_array(globuff.gl_pathv);
    else
        printf("%s: No match.\n", find);
    globfree(&globuff);
    return result;
}
