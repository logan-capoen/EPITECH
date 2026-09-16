/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** main
*/

/**
 * @file main.c
 * @brief Handle the main functions of the 'Robot factory' project
 *
 * Check for right arguments and help menu display.
 * Creates the '.cor' file and compile the opened '.s' file.
 */

#include "op.h"

void free_double_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}

static int create_label(args_t *arguments, label_t *labels, int start, int i)
{
    char *label_value = NULL;
    char *label = NULL;

    if (check_label_params(arguments[i].value) != NULL) {
        label_value = int_to_str(
            find_value_labels(labels, arguments[i].value, start));
        if (label_value == NULL)
            return -1;
        label = malloc(sizeof(char) *
            (my_strlen(arguments[i].value) + my_strlen(label_value) + 2));
        if (label == NULL) {
            free(label_value);
            return -1;
        }
        my_strcpy(label, "%");
        my_strcat(label, label_value);
        free(label_value);
        arguments[i].value = label;
    }
    return 0;
}

static int add_label_bytes(args_t *arguments,
    int start, label_t *labels, body_t *instructions)
{
    int nb_bytes = 1;

    for (int i = 0; arguments[i].value != NULL; i++) {
        if (create_label(arguments, labels, start, i) != 0)
            return -1;
    }
    for (int i = 0; arguments[i].value != NULL; i++)
        nb_bytes += arguments[i].nb_bytes;
    if (instructions->codingbyte != -1)
        nb_bytes++;
    return nb_bytes;
}

static void verify_label(body_t *instructions, label_t *labels)
{
    int nb_bytes = 0;
    label_t *curr = labels;
    label_t *tmp = curr;

    for (; instructions != NULL; instructions = instructions->next)
        nb_bytes += add_label_bytes
            (instructions->arguments, nb_bytes, labels, instructions);
    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        free(tmp->name);
        free(tmp);
    }
}

static void free_all(body_t *instructions, char **extracted_body, char **arr)
{
    body_t *curr = instructions;
    body_t *tmp = curr;

    while (curr != NULL) {
            tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        for (int i = 0; extracted_body[i] != NULL; i++)
            free(extracted_body[i]);
        free(extracted_body);
        free_double_arr(arr);
}

static int compile_all(char **arr, char **av, int size, body_t *instructions)
{
    int fd_cor = -1;

    fd_cor = compile_header(arr, av, size);
    if (fd_cor == -1) {
        close(fd_cor);
        return 84;
    }
    if (size != 0)
        compile_body(instructions, fd_cor);
    close(fd_cor);
    return 0;
}

static int get_s_file(int ac, char **av, char ***arr)
{
    char *buff = NULL;

    *arr = *arr;
    if (check_help(ac, av))
        return 0;
    buff = create_buffer(ac, av);
    if (buff == NULL)
        return 84;
    *arr = my_str_to_word_array(buff, ' ');
    free(buff);
    return 0;
}

/**
 * @brief Get the cli arguments, verifies them and interpret them
 *
 * @param ac The number of cli args
 * @param **av The array of cli args
 * @return int The main exit status code
 */
int main(int ac, char **av)
{
    char **arr = NULL;
    label_t *labels = NULL;
    body_t *instructions = NULL;
    int size = 0;
    char **extracted_body = NULL;
    int compile_result = 0;

    if (get_s_file(ac, av, &arr) != 0)
        return 84;
    size = handle_body(arr, &labels, &instructions, &extracted_body);
    if (size == -1)
        return 84;
    verify_label(instructions, labels);
    compile_result = compile_all(arr, av, size, instructions);
    free_all(instructions, extracted_body, arr);
    return compile_result;
}
