/*
** EPITECH PROJECT, 2024
** my_strncpy
** File description:
** copies n characters from a string into another
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int len;

    len = 0;
    while (src[len] != '\0') {
        len++;
    }
    for (int i = 0; i < n && i < len; i++) {
        dest[i] = src[i];
    }
    if (n > len) {
            dest[len] = '\0';
        }
    return dest;
}
