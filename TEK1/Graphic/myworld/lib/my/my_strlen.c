/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** counts and returns the number of characters
*/

int my_strlen(char const *str)
{
    int i;

    i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}
