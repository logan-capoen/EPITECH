/*
** EPITECH PROJECT, 2024
** handle_zero_precision
** File description:
** handling for zero with sup. precision
*/

#include <stdlib.h>
#include "../../include/printf.h"
#include "../../include/my.h"

static int there_is_a_dash(char *buff_arg_type)
{
    for (int i = 0; buff_arg_type[i] != '\0'; i++) {
        if (buff_arg_type[i] == '-')
            return 1;
    }
    return 0;
}

char *handle_zero_i_d(specifiers_t spec, char *buff_arg_type)
{
    char *buff = malloc(sizeof(char) * (my_strlen(buff_arg_type) + 2));
    int num_zero = spec.precision - my_strlen(buff_arg_type);
    int dec = 0;

    if (there_is_a_dash(buff_arg_type)) {
        buff[0] = '-';
        dec = 1;
    }
    num_zero += dec;
    for (int i = dec; i < num_zero; i++) {
        buff[i] = '0';
    }
    for (int j = num_zero; buff_arg_type[j - num_zero] != '\0'; j++) {
        if (buff_arg_type[j - num_zero] == '-') {
            buff[j] = '0';
        } else
            buff[j] = buff_arg_type[j - num_zero];
    }
    return buff;
}

char *handle_zero_f(specifiers_t spec, char *buff_arg_type)
{
    char *buff = malloc(sizeof(char) * (my_strlen(buff_arg_type) + 2));
    int num_zero = spec.precision - my_strlen(buff_arg_type);

    for (int i = 0; buff_arg_type[i] != '\0'; i++) {
        buff[i] = buff_arg_type[i];
    }
    for (int j = my_strlen(buff_arg_type); j < my_strlen(buff_arg_type)
        + num_zero; j++) {
        buff[j] = '0';
    }
    return buff;
}
