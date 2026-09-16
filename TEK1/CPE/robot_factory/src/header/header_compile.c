/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** header_compile
*/

#include "op.h"

int compile_header(char **arr, char **av, int size)
{
    header_t *my_header = malloc(sizeof(header_t));
    char **header = check_header(arr);
    int cor_fd = -1;

    if (!my_header || !header)
        return -1;
    for (int i = my_strlen(header[1]); i < PROG_NAME_LENGTH + 1; i++)
        my_header->prog_name[i] = '\0';
    if (header[2] != NULL)
        for (int i = my_strlen(header[3]); i < COMMENT_LENGTH + 1; i++)
            my_header->comment[i] = '\0';
    my_header->magic = reverse_bytes((unsigned int)COREWAR_EXEC_MAGIC, 4);
    my_strcpy(my_header->prog_name, header[1]);
    my_header->prog_size = reverse_bytes((unsigned int)size, 4);
    if (header[2] != NULL)
        my_strcpy(my_header->comment, header[3]);
    cor_fd = create_cor(av);
    write(cor_fd, my_header, sizeof(header_t));
    free(my_header);
    return cor_fd;
}
