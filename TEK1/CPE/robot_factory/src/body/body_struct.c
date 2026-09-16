/*
** EPITECH PROJECT, 2025
** robot_factory
** File description:
** body_struct
*/

#include "op.h"

void our_rev_list(body_t **begin)
{
    body_t *now = *begin;
    body_t *before = NULL;
    body_t *next;

    while (now != NULL){
        next = now->next;
        now->next = before;
        before = now;
        now = next;
    }
    *begin = before;
}

void add_argument(body_t **instructions, char *value, int nb_bytes, int i)
{
    args_t argument;

    argument.value = value;
    argument.nb_bytes = nb_bytes;
    (*instructions)->arguments[i] = argument;
    for (int j = i + 1; j < MAX_ARGS_NUMBER; j++) {
        (*instructions)->arguments[j].value = NULL;
        (*instructions)->arguments[j].nb_bytes = 0;
    }
}

int add_instruction(body_t **instructions, int instruction)
{
    body_t *node = malloc(sizeof(body_t));

    if (node == NULL) {
        return -1;
    }
    node->instruction = instruction;
    node->codingbyte = 0;
    node->next = *instructions;
    *instructions = node;
    return 0;
}

int handle_body(char **arr, label_t **labels, body_t **instructions,
    char ***extracted_body)
{
    int size = 0;

    *extracted_body = extract_body(arr);
    if ((*extracted_body)[0] == NULL)
        return 0;
    if (compare_args_number(*extracted_body) == 0) {
        return -1;
    }
    size = parsing_body(*extracted_body, labels, instructions);
    our_rev_list(instructions);
    create_coding_byte(*instructions);
    return size;
}
