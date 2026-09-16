/*
** EPITECH PROJECT, 2025
** parser
** File description:
** parses the char *line and turns it into commands_t
*/

/**
 * @file parser.c
 * @brief Main parsing functions that recursively parse into subcommands.
 */

#include "parser.h"

/**
 * @brief Get the number of subcommands in a command.
 *
 * Counts the number of subcommands using a separator.
 *
 * @param separator The separator to cut my line.
 * @param line The input command line.
 * @return The number of subcommands.
 */
int get_number_subcommands(sep_t separator, char *line)
{
    parsing_state_t parsing_elements =
        {line, separator, 0, false, false, false, 0, 0};
    int number_subcommands = 0;
    int start_index = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        change_depth(&parsing_elements, line[i]);
        change_backtick_and_quotes(&parsing_elements, line[i]);
        if (is_nested(parsing_elements))
            continue;
        if (is_simple_separator(line[i], separator) ||
            is_double_separator(line, &i, separator, true)) {
            start_index = i;
            number_subcommands++;
        }
    }
    if (start_index + 1 != (int)strlen(line))
        number_subcommands++;
    return number_subcommands;
}

/**
 * @brief Parse a full command line recursively.
 *
 * Splits the line by the highest-level separator
 * and recursively parses subcommands.
 *
 * @param line The input command line.
 * @param start_index A pointer to the start index of the line.
 * @param index The end index of the line.
 * @param is_simple_separator 1 if the separator is COLUMN or PIPE, else 0.
 * @return A pointer to the new substring, NULL on error.
 */
char *cut_substring(char *line, int *start_index,
    int index, int is_simple_separator)
{
    int len = index - *start_index;
    char *substring = NULL;

    if (!line || !start_index || len < 0)
        return NULL;
    substring = malloc(len + 1);
    if (!substring)
        return NULL;
    strncpy(substring, line + *start_index, len);
    substring[len] = '\0';
    *start_index = index + (is_simple_separator ? 1 : 2);
    return substring;
}

/**
 * @brief Creates a new subcommand if a separator is found
 *
 * @param parsing_elements The major parsing elements
 * @param commands The parent command node.
 * @param i A pointer to the current index in the line to parse.
 */
static void add_subcommand(parsing_state_t *parsing_elements,
    commands_t *commands, int *i)
{
    if (is_simple_separator(parsing_elements->line[*i], commands->separator)) {
        commands->subcommands[parsing_elements->current_subcommand_index] =
        choose_parsing(cut_substring(parsing_elements->line,
        &parsing_elements->start_index, *i, 1), NULL,
        parsing_elements->separator, commands->depth);
        parsing_elements->current_subcommand_index++;
    }
    if (is_double_separator(parsing_elements->line,
        i, commands->separator, false)) {
        commands->subcommands[parsing_elements->current_subcommand_index]
        = choose_parsing(cut_substring(parsing_elements->line,
        &parsing_elements->start_index, *i, 0), NULL,
        parsing_elements->line[*i] == '&' ? AND : OR, commands->depth);
        parsing_elements->current_subcommand_index++;
    }
}

/**
 * @brief Parse a full command line recursively.
 *
 * Splits the line by the highest-level separator
 * and recursively parses subcommands.
 *
 * @param line The input command line.
 * @param commands The parent command node.
 * @param separator The separator to use to cut the line
 * @return A pointer to the new added command, or NULL on error.
 */
commands_t *parse_commands(char *line, commands_t *commands, sep_t separator)
{
    parsing_state_t parsing_elements =
        {line, separator, 0, false, false, false, 0, 0};

    for (int i = 0; line[i] != '\0'; i++) {
        change_depth(&parsing_elements, line[i]);
        change_backtick_and_quotes(&parsing_elements, line[i]);
        if (is_nested(parsing_elements))
            continue;
        add_subcommand(&parsing_elements, commands, &i);
    }
    if (parsing_elements.start_index + 1 != (int)strlen(line)) {
        commands->subcommands[parsing_elements.current_subcommand_index] =
        choose_parsing(cut_substring(line, &parsing_elements.start_index,
        strlen(line), 1), NULL, separator, commands->depth);
    }
    return commands;
}

/**
 * @brief Assigns separators between subcommands in reverse order.
 *
 * This function traverses the subcommands array and shifts each separator
 * to the next subcommand, so that separators logically sit between commands.
 * For example, in "ls ; echo hi", the ';' belongs to the second command.
 * *
 * @param commands The command structure containing subcommands.
 * @param number_subcommands The number of expected subcommands.
 * @return Always returns 1.
 */
static int check_subcommands(commands_t *commands, int number_subcommands)
{
    sep_t separator = NONE;
    sep_t tmp = NONE;

    for (int i = 0; i < number_subcommands; i++) {
        if (commands->subcommands[i] != NULL) {
            tmp = commands->subcommands[i]->separator;
            commands->subcommands[i]->separator = separator;
            separator = tmp;
        }
    }
    return 1;
}

/**
 * @brief Parses a command line and constructs
 * a command structure based on separators.
 *
 * This function analyzes the input line,
 * handles command separators (e.g., `;`, `&&`, `||`), and splits the command
 * into subcommands. It also manages the depth for nested commands
 * (such as parentheses) and assigns the good separator to each subcommand.
 *
 * @param line The input command line.
 * @param commands The parent command node.
 * @param separator The separator to use if needed to cut
 * @param depth The current depth, used for parenthesis handling
 * @return A pointer to the new added command, or NULL on error.
 */
commands_t *choose_parsing(char *line, commands_t *commands,
    sep_t separator, int depth)
{
    sep_t highest_separator = get_highest_separator(line);
    int nbr_subcommands = 0;

    if (!commands)
        commands = create_command_node();
    if (!commands)
        return NULL;
    commands->depth = depth;
    commands->separator = separator;
    if (highest_separator == NONE)
        return handle_no_separator_command(line, commands);
    nbr_subcommands = get_number_subcommands(highest_separator, line);
    commands->subcommands = calloc(nbr_subcommands + 1, sizeof(commands_t *));
    if (!commands->subcommands)
        return NULL;
    commands = parse_commands(line, commands, highest_separator);
    if (!check_subcommands(commands, nbr_subcommands))
        return NULL;
    free(line);
    return commands;
}

/**
 * @brief Entry point for parsing a command line.
 *
 * Validates the syntax and initializes the command tree.
 *
 * @param line The command line to parse.
 * @return The root of the parsed command tree, or NULL on error.
 */
commands_t *parse_line(char *line)
{
    char *dup_line = strdup(line);

    if (!dup_line)
        return NULL;
    if (!is_valid_syntax(line)) {
        free(dup_line);
        return NULL;
    }
    return choose_parsing(dup_line, NULL, NONE, 0);
}
