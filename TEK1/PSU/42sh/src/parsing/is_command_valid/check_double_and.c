/*
** EPITECH PROJECT, 2025
** check double and
** File description:
** checks if the line is conform with &&
*/

/**
 * @file check_double_and.c
 * @brief Functions to check the validity of &&' syntax in the line.
 */

 #include "parser.h"

/**
 * @brief Checks if `&&` at position i is syntactically invalid.
 *
 * Invalid `&&` include:
 * - A `&&` followed by another `&&` and a null command.
 * - A `&&` followed by a null command.
 *
 * @param line The command line string.
 * @param i The index to check for `&&`.
 * @return true if the `&&` is invalid, false otherwise.
 */
static bool is_invalid_and(const char *line, int i)
{
    if (line[i] == '&' && line[i + 1] == '&') {
        if (line[i + 2] == '&' && is_null_command(line, i + 2))
            return true;
        if (line[i + 2] != '&' && is_null_command(line, i))
            return true;
    }
    return false;
}

/**
 * @brief Checks if the `&&` syntax in the command line is valid.
 *
 * This function ensures that:
 * - The line does not start with `&&`.
 * - `&&` are not followed by invalid or missing commands.
 * - `&&` checks ignore characters inside quotes.
 *
 * @param line The command line string to validate.
 * @return 1 if the `&&` syntax is valid, 0 otherwise.
 */
int is_valid_and_syntax(char *line)
{
    bool in_single_quote = false;
    bool in_double_quote = false;
    int i = 0;

    if (!line || !*line)
        return 0;
    while (line[i] && is_space(line[i]))
        i++;
    if (line[i] == '&' && line[i + 1] == '&') {
        write(2, "Invalid null command.\n", 22);
        return 0;
    }
    for (; line[i]; i++) {
        update_quote_state(line[i], &in_single_quote, &in_double_quote);
        if (!in_single_quote && !in_double_quote && is_invalid_and(line, i)) {
            write(2, "Invalid null command.\n", 22);
            return 0;
        }
    }
    return 1;
}
