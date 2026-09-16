/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** UwU
*/

char *my_strcat(char *dest, char const *src)
{
    int len_dest;
    int i = 0;

    while (dest[i] != '\0')
        i++;
    for (int j = 0; src[j] != '\0'; j++) {
        dest[i] = src[j];
        i++;
    }
    dest[i + 1] = '\0';
    return dest;
}
