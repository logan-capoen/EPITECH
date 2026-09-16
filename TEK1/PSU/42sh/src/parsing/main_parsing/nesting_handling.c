/*
** EPITECH PROJECT, 2025
** nesting handling
** File description:
** changes the depth based off parenthesis, backticks and quotes
*/

/**
 * @file is_command_valid.c
 * @brief Handles nesting, and changes it if encountering parenthesis or quotes
 */

#include "parser.h"

/**
 * @brief Modify the depth counter when encountering parentheses.
 *
 * Increments or decrements the depth counter depending on the character.
 *
 * @param parsing_elements Pointer to the parsing elements' state
 * @param current_character Current character being read.
 */
void change_depth(parsing_state_t *parsing_elements, char current_character)
{
    if (current_character == '(')
        parsing_elements->current_depth++;
    else if (current_character == ')')
        parsing_elements->current_depth--;
}

/**
 * @brief Check if the parser is currently in a nested state.
 *
 * Determines if the parser is inside quotes, backticks or parentheses.
 *
 * @param parsing_elements The parsing elements' state
 * @return 1 if nested, 0 otherwise.
 */
int is_nested(parsing_state_t parsing_elements)
{
    if (parsing_elements.current_depth == 0 &&
        !parsing_elements.in_single_quote && !parsing_elements.in_backtick
        && !parsing_elements.in_double_quote)
        return 0;
    return 1;
}

/**
 * @brief Toggle quote or backtick status depending on the character.
 *
 * @param parsing_elements Pointer to the parsing elements' state
 * @param current_character Current character being read.
 */
void change_backtick_and_quotes(parsing_state_t *parsing_elements,
    char current_character)
{
    if (current_character == '`')
        parsing_elements->in_backtick = !(parsing_elements->in_backtick);
    if (current_character == '\'')
        parsing_elements->in_single_quote =
        !(parsing_elements->in_single_quote);
    if (current_character == '\"')
        parsing_elements->in_double_quote =
        !(parsing_elements->in_double_quote);
}

/**
 * @brief Trim spaces and validate parentheses at the boundaries.
 *
 * @param line The input command line.
 * @param start Pointer to the start index of the trimmed line.
 * @param end Pointer to the end index of the trimmed line.
 * @return 1 if the line starts and ends with parentheses, 0 otherwise.
 */
static int trim_and_validate_parentheses(char *line, int *start, int *end)
{
    if (!line)
        return 0;
    *start = 0;
    *end = strlen(line) - 1;
    while (is_space(line[*start]))
        (*start)++;
    while (*end > *start && is_space(line[*end]))
        (*end)--;
    if (line[*start] != '(' || line[*end] != ')')
        return 0;
    return 1;
}

/**
 * @brief Check if the command is entirely wrapped in parentheses.
 *
 * @param line The input command line.
 * @return 1 if command is parenthesized, 0 otherwise.
 */
int is_command_inside_parenthesis(char *line)
{
    int start = 0;
    int end = 0;
    int depth = 0;

    if (!trim_and_validate_parentheses(line, &start, &end))
        return 0;
    for (int i = start; i <= end; i++) {
        if (line[i] == '(')
            depth++;
        if (line[i] == ')')
            depth--;
        if (depth == 0 && i < end)
            return 0;
    }
    return depth == 0;
}

/**
 * @brief Remove extra spaces in the line, trims it
 *
 * @param line The input command line.
 * @param start A pointer to the new start of the line
 * @param end A pointer to the new end of the line
 * @return An int, for error outputs
 */
static int get_trimmed_bounds(char *line, int *start, int *end)
{
    if (!line)
        return 0;
    *start = 0;
    *end = strlen(line) - 1;
    while (is_space(line[*start]))
        (*start)++;
    while (*end > *start && is_space(line[*end]))
        (*end)--;
    if (line[*start] != '(' || line[*end] != ')')
        return 0;
    (*start)++;
    (*end)--;
    while (is_space(line[*start]) && *start <= *end)
        (*start)++;
    while (is_space(line[*end]) && *end >= *start)
        (*end)--;
    return 1;
}

/**
 * @brief Remove outer parentheses from the command line.
 *
 * Allocates and returns a copy of the line without outer parentheses.
 *
 * @param line The input command line.
 * @return A new string without the outer parentheses, or NULL on failure.
 */
char *cut_parenthesis(char *line)
{
    int start = 0;
    int end = 0;
    int len = 0;
    char *new_line = NULL;

    if (!get_trimmed_bounds(line, &start, &end))
        return NULL;
    len = end - start + 1;
    if (len <= 0) {
        free(line);
        return strdup("");
    }
    new_line = malloc(len + 1);
    if (!new_line)
        return NULL;
    strncpy(new_line, line + start, len);
    new_line[len] = '\0';
    free(line);
    return new_line;
}
