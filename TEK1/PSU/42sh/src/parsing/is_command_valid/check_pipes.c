/*
** EPITECH PROJECT, 2025
** check pipes
** File description:
** checks if the line is conform with pipes
*/

/**
 * @file check_pipes.c
 * @brief Functions to check the validity of pipes' syntax in the line.
 */

#include "parser.h"

/**
* @brief Checks if a character is a space, tab, or newline.
*
* @param c The character to check.
* @return true if the character is a whitespace, false otherwise.
*/
bool is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * @brief Updates the quote states depending on the current character.
*
 * This function toggles the in_single_quote or in_double_quote flags
 * depending on whether the current character is a quote and whether we are
 * currently inside the other type of quote.
 *
 * @param c The current character.
 * @param in_single_quote Pointer to a flag : if inside single quotes.
 * @param in_double_quote Pointer to a flag : if inside double quotes.
 */
void update_quote_state(char c,
    bool *in_single_quote, bool *in_double_quote)
{
    if (c == '\'' && !*in_double_quote)
        *in_single_quote = !*in_single_quote;
    else if (c == '"' && !*in_single_quote)
        *in_double_quote = !*in_double_quote;
}

/**
 * @brief Determines if a null command follows the current pipe character.
 *
 * Skips spaces and checks if there's nothing valid after the pipe.
 *
 * @param line The command line string.
 * @param i The index of the pipe character.
 * @return true if nothing follows the pipe, false otherwise.
 */
bool is_null_command(const char *line, int i)
{
    int j = i + 1;

    while (line[j] && is_space(line[j]))
        j++;
    return (line[j] == '\0' || (line[j] == '|'));
}

/**
 * @brief Checks if a pipe at position i is syntactically invalid.
 *
 * Invalid pipes include:
 * - A pipe followed by another pipe and a null command.
 * - A pipe followed by a null command.
 *
 * @param line The command line string.
 * @param i The index to check for a pipe.
 * @return true if the pipe is invalid, false otherwise.
 */
static bool is_invalid_pipe(const char *line, int i)
{
    if ((line[i] == '|')) {
        if (line[i + 1] == '|' && is_null_command(line, i + 1))
            return true;
        if (line[i + 1] != '|' && is_null_command(line, i))
            return true;
    }
    return false;
}

/**
 * @brief Checks if the pipe syntax in the command line is valid.
 *
 * This function ensures that:
 * - The line does not start with a pipe.
 * - Pipes are not followed by invalid or missing commands.
 * - Pipe checks ignore characters inside quotes.
 *
 * @param line The command line string to validate.
 * @return 1 if the pipe syntax is valid, 0 otherwise.
 */
int is_valid_pipe_syntax(char *line)
{
    bool in_single_quote = false;
    bool in_double_quote = false;
    int i = 0;

    if (!line || !*line)
        return 0;
    while (line[i] && is_space(line[i]))
        i++;
    if (line[i] == '|') {
        write(2, "Invalid null command.\n", 22);
        return 0;
    }
    for (; line[i]; i++) {
        update_quote_state(line[i], &in_single_quote, &in_double_quote);
        if (!in_single_quote && !in_double_quote && is_invalid_pipe(line, i)) {
            write(2, "Invalid null command.\n", 22);
            return 0;
        }
    }
    return 1;
}
