/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** Uwu
*/
#include <stdlib.h>
#include <stdio.h>
#include "../../include/my.h"
#include <stdlib.h>
#include <string.h>

static int is_separator(char c, char spliter)
{
    return c == spliter || c == '\t';
}

static int count_words(const char *str, char spliter)
{
    int count = 0;
    int in_word = 0;

    while (*str) {
        if (!is_separator(*str, spliter) && !in_word) {
            in_word = 1;
            count++;
        }
        if (is_separator(*str, spliter)) {
            in_word = 0;
        }
        str++;
    }
    return count;
}

static char *get_next_word(const char **str_ptr, char spliter)
{
    const char *str = *str_ptr;
    const char *start;
    int len;
    char *word;

    for (; *str && is_separator(*str, spliter); str++);
    start = str;
    for (; *str && !is_separator(*str, spliter); str++);
    len = str - start;
    word = malloc(len + 1);
    if (word) {
        my_strncpy(word, start, len);
        word[len] = '\0';
    }
    *str_ptr = str;
    return word;
}

char **my_str_to_word_array(char const *str, char spliter)
{
    int word_count = count_words(str, spliter);
    char **arr = malloc((word_count + 1) * sizeof(char *));

    if (!arr)
        return NULL;
    for (int i = 0; i < word_count; i++)
        arr[i] = get_next_word(&str, spliter);
    arr[word_count] = NULL;
    return arr;
}
