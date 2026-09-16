/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday06-theophile.riffe
** File description:
** my_revstr
*/

#include "my.h"

char *my_revstr(char *str)
{
    int len;
    char tmp = '2';

    if (str == NULL)
        return NULL;
    len = my_strlen(str);
    for (int i = 0; i < len / 2; i++){
        tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
    return str;
}
