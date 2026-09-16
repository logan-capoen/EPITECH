/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** int_to_str.c
*/

#include "utilities.h"

/**
 * @brief Converts a non-negative integer to a dynamically allocated string.
 *
 * Allocates memory to store the string representation of the given integer
 * and formats it into the allocated memory.
 *
 * @param value The integer value to convert (must be non-negative).
 * @return A dynamically allocated string containing the number representation,
 *         or NULL on allocation failure or invalid input.
 */
char *int_to_str(int value)
{
    int count = 0;
    char *str = NULL;
    int copy = value;

    if (value < 0)
        return NULL;
    if (value == 0)
        return strdup("0");
    while (copy > 0) {
        copy /= 10;
        count++;
    }
    str = malloc(sizeof(char) * (count + 1));
    if (!str)
        return NULL;
    sprintf(str, "%d", value);
    return str;
}
