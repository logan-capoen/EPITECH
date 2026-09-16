/*
** EPITECH PROJECT, 2024
** first_flags
** File description:
** definitions of fists flags fonctions
*/

#include "../../include/struct_printf.h"
#include "../../include/printf.h"
#include "../../include/my.h"
#include <stdlib.h>

char *dash_flag(char *buffer)
{
    unsigned char len = 0;
    unsigned char index = 0;

    if (buffer[0] != ' ')
        return buffer;
    while (buffer[len] == ' ')
        len++;
    index = my_strlen(buffer) - len;
    for (int i = 0; i < index; i++) {
        buffer[i] = buffer[len + i];
        buffer[len + i] = ' ';
    }
    return buffer;
}

char *zero_flag(char *buffer)
{
    if (buffer[0] != ' ')
        return buffer;
    for (int i = 0; i < my_strlen(buffer); i++) {
        if (buffer[i] == 'E')
            return buffer;
        if (buffer[i] == 'e')
            return buffer;
        if (buffer[i] == '-')
            buffer[0] = '-';
        if (buffer[i] == '+')
            buffer[0] = '+';
        if (buffer[i] == ' ' || buffer[i] == '-' || buffer[i] == '+')
            buffer[i] = '0';
    }
    return buffer;
}

char *sharp_flag(char *buffer)
{
    return buffer;
}

char *space_flag(char *buffer)
{
    char *new_buff = malloc(sizeof(char) * my_strlen(buffer)+ 2);

    for (int i = 0; i < my_strlen(buffer) + 1; i++)
        new_buff[i] = '\0';
    for (int i = 0; i < my_strlen(buffer); i++)
        if (buffer[i] == '-' || buffer[i] == '+'){
            free(new_buff);
            return buffer;
        }
    if (buffer[0] == ' ' || buffer[0] == '0') {
        buffer[0] = ' ';
        free(new_buff);
        return buffer;
    }
    new_buff[0] = ' ';
    my_strcat(new_buff, buffer);
    return new_buff;
}

char *plus_flag(char *buffer)
{
    unsigned int a = 0;
    char *new_buff = malloc(sizeof(char) * my_strlen(buffer) + 2);

    for (int i = 0; i < my_strlen(buffer) + 1; i++)
        new_buff[i] = '\0';
    if (buffer[0] != ' ') {
        new_buff[0] = '+';
        my_strcat(new_buff, buffer);
    return new_buff;
    }
    for (int i = 0; i < my_strlen(buffer); i++)
        if (buffer[i] == '-')
            return buffer;
    while (buffer[a] == ' ')
        a++;
    buffer[a - 1] = '+';
    return buffer;
}
