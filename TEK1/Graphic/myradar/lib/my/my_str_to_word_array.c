/*
** EPITECH PROJECT, 2024
** my_str_to_word_array.c
** File description:
** UwU
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../include/my.h"

static int is_not_space(char c)
{
    return c != ' ' && c != '\t' && c != '\n';
}

static char *extract_word(const char *str, int start, int end)
{
    int len = end - start;
    char *word = malloc(sizeof(char) * (len + 1));

    if (!word)
        return NULL;
    my_strncpy(word, str + start, len);
    word[len] = '\0';
    return word;
}

static int count_words(const char *str)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_not_space(str[i])) {
            count++;
            in_word = 1;
        } else
            in_word = 0;
    }
    return count;
}

char **my_str_to_word_array(const char *str)
{
    int word_count = count_words(str);
    char **array = malloc(sizeof(char *) * (word_count + 1));
    int start = -1;
    int index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_not_space(str[i]) && start == -1)
            start = i;
        if (start != -1 && !is_not_space(str[i])) {
            array[index] = extract_word(str, start, i);
            index++;
            start = -1;
        }
    }
    if (start != -1) {
        array[index] = extract_word(str, start, my_strlen(str));
        index++;
    }
    array[index] = NULL;
    return array;
}
