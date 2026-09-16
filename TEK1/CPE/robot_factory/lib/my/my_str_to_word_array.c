/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** my_str_to_word_array
*/

#include "my.h"

static int is_separator(char c, char spliter, int *in_quote, int check)
{
    if (check)
        if (c == '"')
            *in_quote = !(*in_quote);
    return (c == spliter || c == '\t' ||
        c == '\n' || c == ',') && !(*in_quote);
}

static int count_words(const char *str, char spliter, int *in_quote)
{
    int count = 0;
    int in_word = 0;
    int result = 0;

    while (*str) {
        result = is_separator(*str, spliter, in_quote, 1);
        if (!result && !in_word) {
            in_word = 1;
            count++;
        }
        if (result) {
            in_word = 0;
        }
        str++;
    }
    return count;
}

static char *get_next_word(const char **str_ptr, char spliter, int *in_quote)
{
    const char *str = *str_ptr;
    const char *start;
    int len;
    char *word;

    for (; *str && is_separator(*str, spliter, in_quote, 0); str++);
    start = str;
    for (; *str && !is_separator(*str, spliter, in_quote, 1); str++);
    len = str - start;
    word = malloc(len + 1);
    if (word == NULL)
        return NULL;
    if (word) {
        my_strncpy(word, start, len);
        word[len] = '\0';
    }
    *str_ptr = str;
    return word;
}

char **my_str_to_word_array(char const *str, char spliter)
{
    int in_quote = 0;
    int word_count = count_words(str, spliter, &in_quote);
    char **arr = malloc((word_count + 1) * sizeof(char *));

    if (!arr)
        return NULL;
    for (int i = 0; i < word_count; i++)
        arr[i] = get_next_word(&str, spliter, &in_quote);
    arr[word_count] = NULL;
    return arr;
}
