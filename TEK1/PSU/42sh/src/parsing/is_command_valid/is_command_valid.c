/*
** EPITECH PROJECT, 2025
** is command valid
** File description:
** changes the depth based off parenthesis, backticks and quotes
*/

/**
 * @file is_command_valid.c
 * @brief Ensures that the command line is properly formatted before execution.
 */

#include "parser.h"

/**
 * @brief Checks the line for errors.
 *
 * Validates the syntax.
 *
 * @param line The command line to check.
 * @return 1 if the line is well formated, else 0.
 */
int is_valid_syntax(char *line)
{
    if (!line)
        return 0;
    if (!is_valid_pipe_syntax(line) || !is_nesting_matched(line)
        || !is_valid_and_syntax(line) || !is_valid_semicolon_syntax(line))
        return 0;
    return 1;
}
