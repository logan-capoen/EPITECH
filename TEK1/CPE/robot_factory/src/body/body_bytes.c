/*
** EPITECH PROJECT, 2025
** robot_factory
** File description:
** body_bytes
*/

#include "tab.h"

int check_instruction(char *str)
{
    for (int i = 0; i < 16; i++) {
        if (my_strcmp(op_tab[i].mnemonique, str) == 0)
            return i;
    }
    return -1;
}

int count_awaited_args(char **body)
{
    int arg_counter = 0;
    int found_inst = 0;
    int result_label = 0;

    for (int i = 0; body[i] != NULL; i++) {
        found_inst = check_instruction(body[i]);
        if (found_inst != -1)
            arg_counter += op_tab[found_inst].nbr_args + 1;
        result_label = check_label(body[i]);
        if (result_label)
            arg_counter++;
        if (result_label == -1)
            return -1;
    }
    return arg_counter;
}

char **extract_body(char **arr)
{
    int arr_size = 0;
    char **body = NULL;
    int start = 0;

    while (arr[arr_size] != NULL)
        arr_size++;
    body = malloc(sizeof(char *) * (arr_size + 1));
    if (body == NULL)
        return NULL;
    for (; arr[start] != NULL && check_label(arr[start]) == 0 &&
        check_instruction(arr[start]) == -1; start++);
    for (int i = 0; arr[start + i] != NULL; i++) {
        body[i] = my_strdup(arr[start + i]);
    }
    body[arr_size - start] = NULL;
    return body;
}
// static int verify_type_bytes(int bytes, int type, int byte)
// {
//     if (byte != bytes) {
//         if (bytes + byte == type)
//             return 1;
//     }
//     return 0;
// }

// static int verify_type(int bytes, int j, int instruction)
// {
//     int types[3] = {1, 2, 4};
//     int correct_param = 0;
//
//     for (int i = 0; i < 3; i++) {
//         if (verify_type_bytes(bytes, op_tab[instruction].type[j], types[i]))
//             correct_param = 1;
//     }
//     if (bytes == 4)
//         if (2 == op_tab[instruction].type[j])
//             correct_param = 1;
//     if (bytes == op_tab[instruction].type[j] ||
//         op_tab[instruction].type[j] == 7)
//         correct_param = 1;
//     if (correct_param)
//         return bytes;
//     return -1;
// }
static int count_bytes(char **body, int i,
    int instruction, body_t **instructions)
{
    int nb_args = op_tab[instruction].nbr_args;
    int nb_bytes = 0;
    int bytes = 0;

    add_instruction(instructions, instruction);
    for (int j = 0; j < nb_args; j++) {
        bytes = search_type(body[i + j + 1],
            op_tab[instruction].mnemonique);
        if (bytes == -1)
            return -1000000;
        add_argument(instructions, body[i + j + 1], bytes, j);
        nb_bytes += bytes;
    }
    if (nb_args != 1 || my_strcmp(body[i], "aff") == 0)
        nb_bytes += 2;
    else
        nb_bytes++;
    return nb_bytes;
}

int parsing_body(char **body, label_t **labels, body_t **instructions)
{
    int nb_bytes = 0;
    int instruction = 0;
    int is_label = 0;

    for (int i = 0; body[i] != NULL; i++) {
        instruction = check_instruction(body[i]);
        if (instruction != -1) {
            nb_bytes += count_bytes(body, i, instruction,
                instructions);
        }
        is_label = check_label(body[i]);
        if (is_label) {
            add_label(labels, body[i], nb_bytes);
        }
        if (is_label == -1 || nb_bytes < 0) {
            return -1;
        }
    }
    return nb_bytes;
}

static void write_args(args_t *arguments, int fd_cor)
{
    unsigned int result = 0;
    unsigned int rev_result = 0;

    for (int i = 0; arguments[i].value != NULL; i++) {
        result = my_getnbr(arguments[i].value);
        rev_result = reverse_bytes(result, arguments[i].nb_bytes);
        if (arguments[i].nb_bytes == 1)
            write(fd_cor, &result, arguments[i].nb_bytes);
        if (arguments[i].nb_bytes != 1)
            write(fd_cor, &rev_result, arguments[i].nb_bytes);
    }
}

void compile_body(body_t *head, int fd_cor)
{
    body_t *current = head;

    for (; current != NULL; current = current->next) {
        write(fd_cor, &(op_tab[current->instruction].code), 1);
        if (current->codingbyte != -1)
            write(fd_cor, &(current->codingbyte), 1);
        write_args(current->arguments, fd_cor);
    }
}
