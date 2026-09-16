/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** body_check
*/

#include "op.h"

int compare_args_number(char **body)
{
    int awaited = count_awaited_args(body);
    int actual_args = 0;

    if (awaited == -1)
        return -1;
    for (; body[actual_args] != NULL; actual_args++);
    return (actual_args == awaited) ? 1 : 0;
}

// int main(void)
// {
//     char *buff = malloc(sizeof(char) * 1000);
//     int fd = open("../champions/jon.s", O_RDONLY);
//     read(fd, buff, 1000);
//     char **arr = my_str_to_word_array(buff, ' ');
//     for (int i = 0; arr[i] != NULL; i++)
//         printf("%s\n", arr[i]);
//     char **deux = extract_body(arr);
//     for (int i = 0; deux[i] != NULL; i++)
//         printf("%s\n", deux[i]);
//     return 0;
// }
//gcc body/body_check.c -I../include -L../lmy ../lib/my/my_strcmp.c
//../lib/my/my_strdup.c ../lib/my/my_str_to_word_array.c
//../lib/my/my_strlen.c ../lib/my/my_strncpy.c
