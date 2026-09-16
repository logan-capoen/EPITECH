/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** handle_input
*/

#include "minishell2.h"
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

static int check_redirections(char *line)
{
    int right = 0;
    int left = 0;
    int pipe = 0;

    for (int j = 0; line[j] != '\0'; j++) {
        if (line[j] == '<')
            left++;
        if (line[j] == '>')
            right++;
        if (line[j] == '|')
            pipe++;
        if (line[j] == '<' || line[j] == '>' || line[j] == '|')
            j++;
        if (left > 1 || right > 1 || pipe > 1)
            return 1;
    }
    return 0;
}

static int verify_parsing(char *line)
{
    char **array = my_str_to_word_array(line, " \t");
    int return_value = 0;

        for (int j = 0; array[j] != NULL; j++) {
            if (array[j][0] == '<' && array[j + 1] == NULL)
                return_value = 1;
            if (array[j][0] == '>' && array[j + 1] == NULL)
                return_value = 1;
            if (array[j][0] == '|' && array[j + 1] == NULL)
                return_value = 1;
        }
    free_arr(array);
    return return_value;
}

static int handle_error(char **lines)
{
    for (int i = 0; lines[i] != NULL; i++) {
        if (check_redirections(lines[i]))
            return 1;
    }
    for (int i = 0; lines[i] != NULL; i++) {
        if (verify_parsing(lines[i]))
            return 1;
    }
    return 0;
}

static int verify_redirection(int index, int i,
    char **array, input_t *input_struct)
{
    if (array[i][0] == '|') {
        input_struct->pipes[index] = my_strdup(array[i + 1]);
        return 1;
    }
    if (my_strcmp(array[i], ">>") == 0) {
        input_struct->outputs[index] = my_strdup(array[i + 1]);
        my_strcat(input_struct->outputs[index], " ");
        return 1;
    }
    if (array[i][0] == '<') {
        input_struct->inputs[index] = my_strdup(array[i + 1]);
        return 1;
    }
    if (array[i][0] == '>') {
        input_struct->outputs[index] = my_strdup(array[i + 1]);
        return 1;
    }
    return 0;
}

static void set_line(char *tmp, char **array, char *line_copy, char** line)
{
    *line = my_strdup(tmp);
    free_arr(array);
    free(line_copy);
    free(tmp);
}

static void split_input(char *line,
    input_t *input_struct, int index, int on_pipe)
{
    char *line_copy = my_strdup(line);
    char **array = my_str_to_word_array(line_copy, " \t");
    char *tmp = malloc(sizeof(char) * my_strlen(line) + 1);

    my_strcpy(tmp, array[0]);
    for (int i = 1; array[i] != NULL; i++) {
        if (on_pipe && array[i - 1][0] != '|') {
            my_strcat(input_struct->pipes[index], " ");
            my_strcat(input_struct->pipes[index], array[i]);
        }
        if (array[i][0] == '|')
            on_pipe = 1;
        if (verify_redirection(index, i, array, input_struct))
            continue;
        if (array[i - 1][0] != '<' && array[i - 1][0] != '>' && on_pipe == 0) {
            my_strcat(tmp, " ");
            my_strcat(tmp, array[i]);
        }
    }
    set_line(tmp, array, line_copy, &(input_struct->lines[index]));
}

static int initialize_input_struct(input_t *input_struct, char **lines)
{
    int len = 0;

    for (; lines[len] != NULL; len++);
    input_struct->lines = malloc(sizeof(char *) * (len + 1));
    input_struct->inputs = malloc(sizeof(char *) * (len + 1));
    input_struct->outputs = malloc(sizeof(char *) * (len + 1));
    input_struct->pipes = malloc(sizeof(char *) * (len + 1));
    if (!input_struct->lines ||
        !input_struct->inputs || !input_struct->outputs)
        return 1;
    for (int i = 0; i <= len; i++) {
        input_struct->lines[i] = NULL;
        input_struct->inputs[i] = NULL;
        input_struct->outputs[i] = NULL;
        input_struct->pipes[i] = NULL;
    }
    return 0;
}

static int check_line(char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' && line[i] != '\t')
            return 0;
    }
    return 1;
}

static int check_lines(char **lines)
{
    for (int i = 0; lines[i] != NULL; i++) {
        if (check_line(lines[i]))
            return 1;
    }
    return 0;
}

input_t *get_input(char *input)
{
    input_t *input_struct = malloc(sizeof(input_t));
    char **lines = my_str_to_word_array(input, ";");
    int on_pipe = 0;

    if (!input_struct || !lines || handle_error(lines) || check_lines(lines))
        return NULL;
    initialize_input_struct(input_struct, lines);
    for (int i = 0; lines[i] != NULL; i++) {
        split_input(lines[i], input_struct, i, on_pipe);
    }
    free_arr(lines);
    return input_struct;
}
