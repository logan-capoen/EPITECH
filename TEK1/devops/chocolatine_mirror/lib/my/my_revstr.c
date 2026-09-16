/*
** EPITECH PROJECT, 2024
** my_revstr
** File description:
** reverses a string
*/

char *my_revstr(char *str)
{
    int len;
    int i;
    int c;

    len = 0;
    while (str[len] != '\0') {
        len++;
    }
    i = 0;
    while (i < len / 2) {
        c = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = c;
        i++;
    }
    return str;
}
