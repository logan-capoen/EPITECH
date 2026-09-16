/*
** EPITECH PROJECT, 2025
** parser
** File description:
** Header file for parsing
*/

#ifndef PARSER_H
    #define PARSER_H
    #include "meowsh.h"
    #include <string.h>
    #include <fcntl.h>
    #include "utilities.h"

// Structs

typedef struct parsing_state_s {
    char *line;
    sep_t separator;
    int current_depth;
    bool in_single_quote;
    bool in_double_quote;
    bool in_backtick;
    int start_index;
    int current_subcommand_index;
} parsing_state_t;

// main_parsing

commands_t *parse_line(char *line);
commands_t *parse_commands(char *line, commands_t *commands, sep_t separator);
void change_depth(parsing_state_t *parsing_elements, char current_character);
int is_nested(parsing_state_t parsing_elements);
void change_backtick_and_quotes(parsing_state_t *parsing_elements,
    char current_character);
int is_command_inside_parenthesis(char *line);
char *cut_parenthesis(char *line);
commands_t *choose_parsing(char *line, commands_t *commands,
    sep_t separator, int depth);
// command_handling

int is_simple_separator(char current_character, sep_t separator);
int is_double_separator(char *line, int *current,
    sep_t separator, bool does_increment);
sep_t get_highest_separator(char *line);
commands_t *create_command_node(void);
commands_t *handle_no_separator_command(char *line, commands_t *commands);
int open_output_fd(commands_t *cmd, bool truncate, char *filename);
int open_input_fd(commands_t *cmd, char *filename);
commands_t *add_command(char *line, commands_t *cmd);
commands_t *check_input_redirection(char *line, commands_t *cmd, int index);
commands_t *check_output_redirection(char *line, commands_t *cmd, int *index);

// is_command_valid

int is_valid_syntax(char *line);
int is_valid_pipe_syntax(char *line);
bool is_nesting_matched(char *line);
bool is_space(char c);
bool is_nesting_matched(char *line);
int get_number_subcommands(sep_t separator, char *line);

void update_quote_state(char c,
    bool *in_single_quote, bool *in_double_quote);
bool is_null_command(const char *line, int i);
int is_valid_and_syntax(char *line);
int is_valid_semicolon_syntax(char *line);

sep_t change_separator(sep_t highest_separator, char *line, int i);

#endif
