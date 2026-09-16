/*
** EPITECH PROJECT, 2025
** separators
** File description:
** gets the highest separator in the command,
** and determines if it's a simple or a double separator
*/

/**
 * @file separators.c
 * @brief Gets the highest-level separator between ';', '&&', '||' and '|'.
 */

#include "parser.h"

/**
 * @brief Update the highest separator found in the line.
 *
 * Compares the current highest and the one found at position i.
 *
 * @param highest_separator The current highest separator.
 * @param line The input command line.
 * @param i Current index being checked.
 * @return The updated highest separator.
 */
sep_t change_separator(sep_t highest_separator, char *line, int i)
{
    if (highest_separator == COLUMN || line[i] == ';')
        return COLUMN;
    if (highest_separator == AND_OR ||
        ((line[i] == '&' && (line[i + 1] && line[i + 1] == '&'))
        || (line[i] == '|' && (line[i + 1] && line[i + 1] == '|'))))
        return AND_OR;
    if (highest_separator == PIPE || line[i] == '|')
        return PIPE;
    return highest_separator;
}

/**
 * @brief Get the highest-priority separator in the line.
 *
 * Skips nested structures like parentheses, quotes and backticks.
 *
 * @param line The input command line.
 * @return The most important separator found, or -1 if none.
 */
sep_t get_highest_separator(char *line)
{
    parsing_state_t parsing_elements =
        {NULL, NONE, 0, false, false, false, 0, 0};
    sep_t highest_separator = NONE;

    if (!line)
        return NONE;
    for (int i = 0; line[i] != '\0'; i++) {
        change_depth(&parsing_elements, line[i]);
        change_backtick_and_quotes(&parsing_elements, line[i]);
        if (!is_nested(parsing_elements))
            highest_separator = change_separator(highest_separator, line, i);
    }
    return highest_separator;
}

/**
 * @brief Checks if the current character is a separator
 *
 * Only in case of semicolumn and pipe.
 *
 * @param current_character The current character to compare.
 * @param separator The highest sep_t defined separator.
 * @return 1 if it's a separator, else 0.
 */
int is_simple_separator(char current_character, sep_t separator)
{
    char real_separator = '\0';

    if (separator == AND_OR || separator == NONE)
        return 0;
    real_separator = separator == COLUMN ? ';' : '|';
    if (current_character == real_separator)
        return 1;
    return 0;
}

/**
 * @brief Checks if the current and following character are separators
 *
 * Only in case of AND/OR separator.
 *
 * @param line The input command line.
 * @param current The current character index.
 * @param separator The highest sep_t defined separator.
 * @param does_increment true if current has to be increased, else false.
 * @return 1 if it's a separator, else 0.
 */
int is_double_separator(char *line, int *current,
    sep_t separator, bool does_increment)
{
    if (separator != AND_OR)
        return 0;
    if ((line[*current] == '&' && (line[*current + 1]
        && line[*current + 1] == '&')) || (line[*current] == '|'
        && (line[*current + 1] && line[*current + 1] == '|'))) {
        if (does_increment)
            (*current)++;
        return 1;
    }
    return 0;
}
