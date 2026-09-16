/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** labels
*/

#include "op.h"

static int is_labelchar(char c)
{
    for (int j = 0; j < my_strlen(LABEL_CHARS); j++) {
        if (LABEL_CHARS[j] == c)
            return 1;
    }
    return 0;
}

static int check_format_label(char *label, int len)
{
    for (int i = 0; i < len - 1; i++) {
        if (!is_labelchar(label[i]))
            return 0;
    }
    return 1;
}

int check_label(char *str)
{
    int len = my_strlen(str);

    if (str[len - 1] == LABEL_CHAR) {
        if (check_format_label(str, len))
            return 1;
        else
            return -1;
    }
    return 0;
}

int exist_name(label_t **head, label_t *node, char *name)
{
    label_t *curr = *head;

    for (; curr != NULL; curr = curr->next) {
        if (my_strcmp(name, curr->name) == 0) {
            free(node);
            return 1;
        }
    }
    return 0;
}

void free_labels(label_t **head)
{
    label_t *curr = *head;
    label_t *tmp = *head;

    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        free(tmp->name);
        free(tmp);
    }
    free(head);
}

int add_label(label_t **head, char *name, int position)
{
    label_t *node = malloc(sizeof(label_t));

    if (node == NULL) {
        free_labels(head);
        return -1;
    }
    if (exist_name(head, node, name))
        return -1;
    node->name = my_strdup(name);
    node->position = position;
    node->next = *head;
    *head = node;
    return 0;
}
