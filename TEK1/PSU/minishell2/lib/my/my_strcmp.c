/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** compare two string
*/

int my_strcmp(char const *s1, char const *s2)
{
    int index;

    index = 0;
    for (int i = 0; s1[i] == s2[i]; i++) {
        if (s1[index] == '\0' || s2[index] == '\0')
            return 0;
        index++;
    }
    if (s1[index] < s2[index])
        return -1;
    return 1;
}
