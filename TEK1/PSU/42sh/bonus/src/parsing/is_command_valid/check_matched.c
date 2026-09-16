/*
** EPITECH PROJECT, 2025
** check matched
** File description:
** checks if the line is conform with parenthesis, quotes and double quotes
*/

/**
 * @file check_matched.c
 * @brief Check if parenthesis and quotes are matched.
 */

#include "parser.h"

/**
 * @brief Checks and updates the parenthesis count for closing parentheses.
 *
 * @param character The current character being parsed.
 * @param parenthesis_matched Pointer to the parenthesis balance counter.
 * @return true if the parentheses are valid, else false.
 */
static bool is_parenthesis_opened(char character, int *parenthesis_matched)
{
    if (character == ')') {
        if (*parenthesis_matched == 0)
            return false;
        (*parenthesis_matched)--;
    }
    return true;
}

/**
 * @brief Validates parentheses only if not inside quotes.
 *
 * @param parenthesis_matched Pointer to the current parenthesis counter.
 * @param character The character to check.
 * @param in_single_quote Whether the current context is inside single quotes.
 * @param in_double_quote Whether the current context is inside double quotes.
 * @return true if the character is valid in current context, false otherwise.
 */
static bool is_parenthesis_valid(int *parenthesis_matched, char character,
    bool in_single_quote, bool in_double_quote)
{
    if (!in_single_quote && !in_double_quote) {
        if (character == '(')
            (*parenthesis_matched)++;
        if (!is_parenthesis_opened(character, parenthesis_matched))
            return false;
    }
    return true;
}

/**
 * @brief Displays the error output based off unmatched quotes or parentheses.
 *
 * @param parenthesis_matched The final balance of parentheses.
 * @param in_single_quote Whether the line ended inside single quotes.
 * @param in_double_quote Whether the line ended inside double quotes.
 * @return false if any unmatched structure is found, true otherwise.
 */
static bool print_unmatched_output(int parenthesis_matched,
    bool in_single_quote, bool in_double_quote)
{
    if (in_single_quote) {
        write(2, "Unmatched '.\n", 13);
        return false;
    }
    if (in_double_quote) {
        write(2, "Unmatched \".\n", 13);
        return false;
    }
    if (parenthesis_matched > 0) {
        write(2, "Too many ('s.\n", 14);
        return false;
    }
    return true;
}

/**
 * @brief Checks if quotes and parentheses are matched in the input line.
 *
 * @param line The input string to validate.
 * @return true if all quotes and parentheses are closed, false otherwise.
 */
bool is_nesting_matched(char *line)
{
    int parenthesis_matched = 0;
    bool in_single_quote = false;
    bool in_double_quote = false;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        if (line[i] == '"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        if (!is_parenthesis_valid(&parenthesis_matched, line[i],
            in_single_quote, in_double_quote)) {
            write(2, "Too many )'s.\n", 14);
            return false;
        }
    }
    return print_unmatched_output(parenthesis_matched,
        in_single_quote, in_double_quote);
}
