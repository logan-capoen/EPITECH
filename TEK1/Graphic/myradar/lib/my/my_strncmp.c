/*
** EPITECH PROJECT, 2024
** my_strncmp
** File description:
** compare the n char of two string
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    for (; s1[i] == s2[i] && i < n; i++) {
        if ((s1[i] == '\0' || s2[i] == '\0') || (i == n - 1 && s1[i] == s2[i]))
            return 0;
    }
    if (s1[i] < s2[i])
        return -1;
    return 1;
}
