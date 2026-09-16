/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** UwU
*/

char *my_strcat(char *dest, char const *src)
{
    int i = 0;

    for (; dest[i] != '\0'; i++);
    for (int j = 0; src[j] != '\0'; j++) {
        dest[i] = src[j];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
