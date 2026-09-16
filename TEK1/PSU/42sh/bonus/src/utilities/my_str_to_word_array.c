/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** cuts a string into an array
*/

/**
 * @file my_str_to_word_array.c
 * @brief Functions to split a string into an array of words.
 *
 * This file contains the implementation of the `my_str_to_word_array`
 * function, which splits a string into an array of words based on
 * specified delimiters. It also handles quoted strings to ensure
 * they are treated as a single word.
 */

#include "parser.h"

/**
 * @brief Checks if a character is a separator.
 *
 * This function determines if a character is a separator based on the provided
 * delimiters. It also handles quotes to ensure quoted sections are not split.
 *
 * @param c The character to check.
 * @param spliters A string containing the delimiter characters.
 * @param in_quote Pointer to an integer tracking whether the
 * current position is inside quotes.
 * @param check If set to 1, updates the `in_quote` state when
 * encountering quotes.
 * @return 1 if the character is a separator, 0 otherwise.
 */
static int is_separator(char c, const char *spliters, int *in_quote, int check)
{
    if (check) {
        if (c == '"' || c == '\'')
            *in_quote = !(*in_quote);
    }
    for (int i = 0; spliters[i]; i++) {
        if ((c == spliters[i] || c == '\t'
            || c == '\n' || c == ',') && !(*in_quote))
            return 1;
    }
    return 0;
}

/**
 * @brief Counts the number of words in a string.
 *
 * This function counts the number of words in a string based on the specified
 * delimiters. Quoted sections are treated as a single word.
 *
 * @param str The input string to analyze.
 * @param spliters A string containing the delimiter characters.
 * @param in_quote Pointer to an integer tracking whether
 * the current position is inside quotes.
 * @return The number of words in the string.
 */
static int count_words(const char *str, const char *spliters, int *in_quote)
{
    int count = 0;
    int in_word = 0;
    int result = 0;

    while (*str) {
        result = is_separator(*str, spliters, in_quote, 1);
        if (!result && !in_word) {
            in_word = 1;
            count++;
        }
        if (result)
            in_word = 0;
        str++;
    }
    return count;
}

/**
 * @brief Extracts the next word from a string.
 *
 * This function extracts the next word from the input string based on the
 * specified delimiters. Quoted sections are treated as a single word.
 *
 * @param str_ptr Pointer to the input string
 * (updated to the next position after the word).
 * @param spliters A string containing the delimiter characters.
 * @param in_quote Pointer to an integer tracking whether the
 * current position is inside quotes.
 * @return A dynamically allocated string containing the next
 * word, or NULL on failure.
 */
static char *get_next_word(const char **str_ptr,
    const char *spliters, int *in_quote)
{
    const char *str = *str_ptr;
    const char *start = NULL;
    int len = 0;
    char *word = NULL;

    while (*str && is_separator(*str, spliters, in_quote, 0))
        str++;
    start = str;
    while (*str && !is_separator(*str, spliters, in_quote, 1))
        str++;
    len = str - start;
    word = malloc(len + 1);
    if (!word)
        return NULL;
    strncpy(word, start, len);
    word[len] = '\0';
    *str_ptr = str;
    return word;
}

/**
 * @brief Splits a string into an array of words.
 *
 * This function splits the input string into an array of words based on the
 * specified delimiters. Quoted sections are treated as a single word.
 *
 * @param str The input string to split.
 * @param spliters A string containing the delimiter characters.
 * @return A dynamically allocated array of strings, or NULL on failure.
 */
char **my_str_to_word_array(const char *str, const char *spliters)
{
    int in_quote = 0;
    int word_count = count_words(str, spliters, &in_quote);
    char **arr = malloc((word_count + 1) * sizeof(char *));

    if (!arr)
        return NULL;
    for (int i = 0; i < word_count; i++)
        arr[i] = get_next_word(&str, spliters, &in_quote);
    arr[word_count] = NULL;
    return arr;
}
