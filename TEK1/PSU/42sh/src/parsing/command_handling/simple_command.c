/*
** EPITECH PROJECT, 2025
** simple command
** File description:
** handles a simple individual command, with input and output redirections
*/

/**
 * @file simple_command.c
 * @brief Handles an individual command, with input and output redirections.
 */

#include "parser.h"
#include "utilities.h"

/**
 * @brief Initialize a new command node.
 *
 * Allocates and initializes a new commands_t structure with default values.
 *
 * @return Pointer to the newly created commands_t, or NULL on failure.
 */
commands_t *create_command_node(void)
{
    commands_t *new_cmd = calloc(1, sizeof(commands_t));

    if (!new_cmd)
        return NULL;
    new_cmd->separator = NONE;
    new_cmd->fd_input = STDIN_FILENO;
    new_cmd->fd_output = STDOUT_FILENO;
    return new_cmd;
}

/**
 * @brief Add a command to the current commands_t node.
 *
 * Creates a subcommand and prepares it for parsing.
 *
 * @param line The command line to parse.
 * @param commands The parent command node to attach to.
 * @return Pointer to the subcommand created, or NULL on error.
 */
commands_t *add_command(char *line, commands_t *commands)
{
    commands->command = my_str_to_word_array(line, " \t");
    free(line);
    return commands;
}

/**
 * @brief Checks for heredoc redirection in the command line.
 *
 * This function parses a heredoc redirection ('<<') in the line,
 * extracts the delimiter, and stores it in the `commands->heredoc` field.
 *
 * @param line The command line string being parsed (will be modified).
 * @param i The current index in the line where the '<' character was found.
 * @param commands The command structure to store the heredoc delimiter in.
 * @return 1 if heredoc is detected and processed, 0 otherwise.
 */
static int check_heredoc(char *line, int i, commands_t *commands)
{
    char **array = NULL;

    if (line[i + 1] != '<')
        return 0;
    array = my_str_to_word_array(line + i + 2, " \t");
    if (!array || !array[0] || line[i + 2] == '<') {
        write(2, "Invalid heredoc given.\n", 23);
        free_array(array);
        return -1;
    }
    commands->heredoc = strdup(array[0]);
    if (!commands->heredoc) {
        free_array(array);
        return -1;
    }
    line[i] = '\0';
    line[i + 1] = '\0';
    free_array(array);
    return 1;
}

/**
 * @brief Checks for input redirection in the command line and processes it.
 *
 * This function parses a possible input redirection ('<') in the line,
 * handles heredoc redirection ('<<'), and opens the corresponding input file
 * for standard input redirection.
 *
 * @param line The command line string being parsed (will be modified).
 * @param commands The structure to store the input file descriptor or heredoc.
 * @param i The current index in the line where the '<' character was found.
 * @return A pointer to the updated commands structure, or NULL on error.
 */
commands_t *check_input_redirection(char *line, commands_t *commands, int i)
{
    char **array = NULL;
    int heredoc_result = 0;

    if (line[i] != '<')
        return commands;
    heredoc_result = check_heredoc(line, i, commands);
    if (heredoc_result == -1)
        return NULL;
    if (heredoc_result == 1)
        return commands;
    array = my_str_to_word_array(line + i + 1, " \t");
    if (!array || !array[0]) {
        write(2, "Missing name for redirect.\n", 27);
        free_array(array);
        return NULL;
    }
    commands->fd_input = open_input_fd(commands, array[0]);
    line[i] = '\0';
    free_array(array);
    return commands;
}

/**
 * @brief Checks for output redirection in the command line and processes it.
 *
 * This function handles both simple (>) and append (>>) output redirection.
 * It opens the corresponding output file and stores its file descriptor in
 * `commands->fd_output`.
 *
 * @param line The command line string being parsed (will be modified).
 * @param commands The command structure to store the output fd in
 * @param i A pointer to the current index in the line where the '>' was found
 * @return A pointer to the updated commands structure, or NULL on error.
 */
commands_t *check_output_redirection(char *line, commands_t *commands, int *i)
{
    char **array = NULL;

    if (line[*i] == '>') {
        array = my_str_to_word_array(line + *i + 1 +
            (line[*i + 1] == '>'), " \t");
        if (!array || !array[0]
            || (line[*i + 1] == '>' && line[*i + 2] == '>')) {
            write(2, "Missing name for redirect.\n", 27);
            return NULL;
        }
        commands->fd_output =
            open_output_fd(commands, line[*i + 1] != '>', array[0]);
        line[*i] = '\0';
        if (line[*i + 1] == '>') {
            line[*i + 1] = '\0';
            (*i)++;
        }
        free_array(array);
    }
    return commands;
}

/**
 * @brief Handle parsing when no separator is found.
 *
 * If the command is nested in parentheses, remove them and parse again.
 * Otherwise, just add the command directly.
 *
 * @param line The input command line.
 * @param commands The current commands_t node.
 * @return The updated commands_t after handling the command.
 */
commands_t *handle_no_separator_command(char *line, commands_t *commands)
{
    parsing_state_t parsing_elements =
        {line, commands->separator, 0, false, false, false, 0, 0};

    if (!line)
        return NULL;
    for (int i = 0; line[i] != '\0'; i++) {
        change_depth(&parsing_elements, line[i]);
        change_backtick_and_quotes(&parsing_elements, line[i]);
        if (is_nested(parsing_elements))
            continue;
        if (!check_input_redirection(line, commands, i)
            || !check_output_redirection(line, commands, &i))
            return NULL;
    }
    if (is_command_inside_parenthesis(line))
        return choose_parsing(cut_parenthesis(line),
            commands, commands->separator, commands->depth + 1);
    return add_command(line, commands);
}
