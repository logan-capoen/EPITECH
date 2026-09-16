/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** put_spaces.c
*/

/**
 * @file put_spaces.c
 * @brief Functions to add spaces around operators in a shell input string.
 *
 * This file contains functions to process a shell input string and ensure
 * that spaces are added around operators
 * (e.g., `>`, `<`, `|`, `;`, `>>`, `<<`).
 * It handles quoted strings to avoid modifying operators inside quotes.
 */

#include "format.h"

/**
 * @brief Checks if a character is a single-character operator.
 *
 * This function determines if the given character is one of the supported
 * single-character operators (`>`, `<`, `|`, `;`).
 *
 * @param c The character to check.
 * @return 1 if the character is an operator, 0 otherwise.
 */
static int is_one_char_op(char c)
{
    return (c == '>' || c == '<' || c == '|' || c == ';');
}

/**
 * @brief Determines the length of an operator at the start of a string.
 *
 * This function checks if the beginning of the string contains a valid
 * operator (e.g., `>>`, `<<`, `||`, `&&`, or single-character operators)
 * and returns its length.
 *
 * @param s The string to check.
 * @return The length of the operator (1 or 2), or 0 if no operator is found.
 */
static int get_op_len(const char *s)
{
    if (!strncmp(s, ">>", 2) || !strncmp(s, "<<", 2) ||
        !strncmp(s, "||", 2) || !strncmp(s, "&&", 2))
        return 2;
    if (is_one_char_op(s[0]))
        return 1;
    return 0;
}

/**
 * @brief Checks if a space is needed before an operator.
 *
 * This function determines if a space should be added before an operator
 * based on the preceding character.
 *
 * @param s The input string.
 * @param pos The position of the operator in the string.
 * @return 1 if a space is needed, 0 otherwise.
 */
static int need_space_before(const char *s, int pos)
{
    return pos > 0 && s[pos - 1] != ' ' && !is_one_char_op(s[pos - 1]);
}

/**
 * @brief Checks if a space is needed after an operator.
 *
 * This function determines if a space should be added after an operator
 * based on the following character.
 *
 * @param s The input string.
 * @param pos The position of the operator in the string.
 * @param op_len The length of the operator.
 * @return 1 if a space is needed, 0 otherwise.
 */
static int need_space_after(const char *s, int pos, int op_len)
{
    return s[pos + op_len] && s[pos + op_len] != ' ' &&
        !is_one_char_op(s[pos + op_len]);
}

/**
 * @brief Handles quotes in the input string.
 *
 * This function tracks whether the current character is inside a quoted
 * string and updates the quote state accordingly.
 *
 * @param c The current character.
 * @param quote Pointer to the current quote state (`'0'` if not in quotes,
 *              or the quote character if inside quotes).
 * @return 1 if the character is a quote, 0 otherwise.
 */
static int handle_quote(char c, char *quote)
{
    if ((c == '"' || c == '\'')) {
        if (*quote == '0') {
            *quote = c;
            return 1;
        }
        if (*quote == c)
            *quote = '0';
        return 1;
    }
    return 0;
}

/**
 * @brief Calculates the new size of the input string with added spaces.
 *
 * This function determines the size of the output string after adding
 * spaces around operators, taking into account quoted strings.
 *
 * @param input The input string.
 * @param len The length of the input string.
 * @return The size of the output string, including added spaces.
 */
static int get_new_size(const char *input, size_t len)
{
    size_t extra = 0;
    int op_len = 0;
    char quote = '0';

    for (size_t i = 0; i < len;) {
        if (handle_quote(input[i], &quote) || quote != '0') {
            i++;
            continue;
        }
        op_len = get_op_len(&input[i]);
        if (op_len > 0) {
            extra += need_space_before(input, i);
            extra += need_space_after(input, i, op_len);
            i += op_len;
        } else
            i++;
    }
    return len + extra;
}

/**
 * @brief Copies a character from the input to the output string.
 *
 * This function copies the current character from the input string to the
 * output string and increments the input and output indices.
 *
 * @param input The input string.
 * @param output The output string.
 * @param i Pointer to the current index in the input string.
 * @param j Pointer to the current index in the output string.
 */
static void keep_char(char *input, char *output, size_t *i, size_t *j)
{
    output[*j] = input[*i];
    *i += 1;
    *j += 1;
}

/**
 * @brief Adds a space to the output string.
 *
 * This function inserts a space character into the output string and
 * increments the output index.
 *
 * @param output The output string.
 * @param j Pointer to the current index in the output string.
 */
static void put_space(char *output, size_t *j)
{
    output[*j] = ' ';
    *j += 1;
}

/**
 * @brief Processes the input string and adds spaces around operators.
 *
 * This function iterates through the input string, identifies operators,
 * and adds spaces around them as needed. It also handles quoted strings
 * to avoid modifying operators inside quotes.
 *
 * @param input The input string.
 * @param output The output string to store the result.
 * @param j The current index in the output string.
 * @param op_len The length of the current operator.
 */
static void make_loop_spaces(char *input, char *output,
    size_t j, size_t op_len)
{
    char quote = '0';

    for (size_t i = 0; i < strlen(input);) {
        if (handle_quote(input[i], &quote) || quote != '0') {
            keep_char(input, output, &i, &j);
            continue;
        }
        op_len = get_op_len(&input[i]);
        if (op_len > 0 && need_space_before(input, i))
            put_space(output, &j);
        if (op_len > 0) {
            memcpy(&output[j], &input[i], op_len);
            j += op_len;
            i += op_len;
        }
        if (op_len > 0 && need_space_after(input, i - op_len, op_len))
            put_space(output, &j);
        if (op_len < 1)
            keep_char(input, output, &i, &j);
    }
}

/**
 * @brief Adds spaces around operators in a shell input string.
 *
 * This function processes the input string, identifies operators, and
 * ensures that spaces are added around them. It handles quoted strings
 * to avoid modifying operators inside quotes.
 *
 * @param input The input string to process.
 * @return A newly allocated string with spaces added around operators,
 *         or NULL on memory allocation failure.
 */
char *add_spaces_around_operators(char *input)
{
    size_t new_size = get_new_size(input, strlen(input));
    char *output = malloc(sizeof(char) * (new_size + 1));
    size_t op_len = 0;
    size_t j = 0;

    if (!output)
        return NULL;
    make_loop_spaces(input, output, j, op_len);
    output[new_size] = '\0';
    return output;
}
