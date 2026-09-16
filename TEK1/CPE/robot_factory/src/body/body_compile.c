/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** header_check
*/

#include "op.h"

int search_type(char *arg, char *instruction)
{
    char *instructions[4] = {"zjmp", "ldi", "sti", "fork"};
    int is_index = 0;

    for (int i = 0; i < 4; i++)
        if (my_strcmp(instruction, instructions[i]) == 0)
            is_index = 1;
    if (arg[0] == 'r') {
        if (my_getnbr(arg + 1) <= REG_NUMBER && my_getnbr(arg + 1) >= 1)
            return T_REG;
        else
            return -1;
    }
    if (arg[0] == '%' && (arg[1] == ':' || my_getnbr(arg) != -789456)) {
        if (is_index)
            return IND_SIZE;
        return DIR_SIZE;
    }
    if (my_getnbr(arg) != -789456)
        return IND_SIZE;
    return -1;
}

char *check_label_params(char *param)
{
    if (my_strlen(param) > 2 && my_strncmp(param, "%:", 2) == 0)
        return param + 2;
    return NULL;
}

static int compute_label_value(int called_pos, int saved_pos)
{
    if (called_pos < saved_pos) {
        return saved_pos - called_pos;
    }
    if (called_pos > saved_pos) {
        return 65536 - (called_pos - saved_pos);
    }
    return 0;
}

int find_value_labels(label_t *head, char *label_name, int curr_pos)
{
    label_t *current = head;

    while (current != NULL) {
        current = current->next;
    }
    current = head;
    for (; current != NULL; current = current->next) {
        if (my_strncmp(current->name, label_name + 2,
            my_strlen(label_name) - 2) == 0) {
                return compute_label_value(curr_pos, current->position);
        }
    }
    return -1;
}

int check_coding_byte(int instruction)
{
    int indexes[4] = {0, 8, 11, 14};

    for (int i = 0; i < 4; i++)
        if (instruction == indexes[i])
            return 0;
    return 1;
}

static void set_bits(char *coding_byte, int b1, int b2, int index)
{
    int new_index = 0;
    int indexes[4] = {7, 5, 3, 1};

    new_index = indexes[index];
    *coding_byte = *coding_byte | (b1 << new_index);
    *coding_byte = *coding_byte | (b2 << (new_index - 1));
}

static void compute_coding_byte(args_t *arguments,
    char *coding_byte)
{
    int i = 0;

    *coding_byte = 0;
    for (; arguments[i].nb_bytes != 0; i++) {
        if ((arguments[i].value)[0] == 'r')
            set_bits(coding_byte, 0, 1, i);
        if ((arguments[i].value)[0] == DIRECT_CHAR)
            set_bits(coding_byte, 1, 0, i);
        if ((arguments[i].value) == NULL)
            set_bits(coding_byte, 0, 0, i);
        if ((arguments[i].value)[0] != 'r' &&
            (arguments[i].value)[0] != DIRECT_CHAR &&
            (arguments[i].value) != NULL)
            set_bits(coding_byte, 1, 1, i);
    }
    for (; i < MAX_ARGS_NUMBER; i++)
        set_bits(coding_byte, 0, 0, i);
}

void create_coding_byte(body_t *head)
{
    body_t *current = head;
    char coding_byte = 0;

    for (; current != NULL; current = current->next) {
        coding_byte = 0;
        if (check_coding_byte(current->instruction)) {
            compute_coding_byte(current->arguments, &coding_byte);
            current->codingbyte = coding_byte;
        }
        if (!check_coding_byte(current->instruction))
            current->codingbyte = -1;
    }
}
