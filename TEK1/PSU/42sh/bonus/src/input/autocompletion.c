/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-mato.urbanac
** File description:
** autocompletion.c
*/

/**
 * @file autocompletion.c
 * @brief Implementation of the tab-autocompletion feature.
 *
 * This file contains functions related to autocompletion based on globbing.
 * It handles extracting the current word from user input, generating matches
 * using glob patterns, and either completing the input with a unique match or
 * displaying multiple possible matches.
 */

#include "input.h"
#include "globbings.h"
#include "parser.h"

/**
 * @brief Extracts the starting position
 *  and length of the last word typed in the input.
 *
 * This function finds the position of the last word typed
 * (everything after the last space)
 * in the input string and calculates its length.
 *
 * @param input The input structure containing the current input string.
 * @param start_out Pointer to store the starting position of the word.
 * @param word_len_out Pointer to store the length of the word.
 */
static void extract_word_info(input_t *input,
    int *start_out, int *word_len_out)
{
    char *current = input->str_input;
    int pos = input->cursor_pos;
    int start = pos;
    int word_len = 0;

    while (start > 0 && !is_space(current[start - 1]))
        start--;
    word_len = pos - start;
    *start_out = start;
    *word_len_out = word_len;
}

/**
 * @brief Constructs the globbing pattern based on the extracted word.
 *
 * If no word is typed, returns "*". Otherwise, returns "<word>*".
 * Caller must free the returned pointer.
 *
 * @param input The input structure containing the current input string.
 * @param start The starting position of the word.
 * @param word_len The length of the word.
 * @return A dynamically allocated string containing the globbing pattern.
 */
static char *construct_glob_pattern(input_t *input, int start, int word_len)
{
    char *base = NULL;
    char *pattern = NULL;

    if (word_len == 0)
        return strdup("*");
    base = strndup(&input->str_input[start], word_len);
    if (!base)
        return NULL;
    pattern = malloc(strlen(base) + 2);
    if (!pattern) {
        free(base);
        return NULL;
    }
    sprintf(pattern, "%s*", base);
    free(base);
    return pattern;
}

/**
 * @brief Replaces the last typed word in the input with the given match.
 *
 * This function updates the input string by replacing the word located at
 * the given position and length with the provided match string. It reallocates
 * memory for the new input string, updates the input length, and moves the
 * cursor position to the end of the inserted match.
 *
 * @param input Pointer to the input structure to be modified.
 * @param start The starting index of the word to replace.
 * @param word_len The length of the word to replace.
 * @param match The string to replace the word with.
 * @return 0 on success, 1 on memory allocation failure.
 */
static int apply_single_match(input_t *input, int start,
    int word_len, const char *match)
{
    int match_len = strlen(match);
    int new_len = input->input_len - word_len + match_len;
    char *new_input = malloc(new_len + 1);

    if (!new_input)
        return 1;
    strncpy(new_input, input->str_input, start);
    strcpy(new_input + start, match);
    strcpy(new_input + start + match_len, input->str_input + start + word_len);
    free(input->str_input);
    input->str_input = new_input;
    input->input_len = new_len;
    input->cursor_pos = start + match_len;
    return 0;
}

/**
 * @brief Writes all matching displays in colors.
 *
 * This function prints each matched path from the globbing results to
 * the standard output, in blue if a directory, else normally.
 *
 * @param file_to_write The name of the file / directory
 * @param file_stat The stats on the file / directory
 */
static void write_colors_directory(char *file_to_write, struct stat *file_stat)
{
    if (S_ISDIR(file_stat->st_mode)) {
        write(STDOUT_FILENO, BLUE, 7);
        write(STDOUT_FILENO, file_to_write,
            strlen(file_to_write));
        write(STDOUT_FILENO, RESET, 4);
    } else {
        write(STDOUT_FILENO, file_to_write,
            strlen(file_to_write));
    }
}

/**
 * @brief Displays all globbing matches on the terminal.
 *
 * This function prints each matched path from the globbing results to
 * the standard output, separated by two spaces and followed by a newline.
 * It is to use when multiple matches are found during autocompletion.
 *
 * @param globuff Pointer to the glob_t structure containing the matches.
 */
static void print_matches(glob_t *globuff)
{
    struct stat file_stat;

    write(STDOUT_FILENO, "\n", 1);
    for (size_t i = 0; i < globuff->gl_pathc; i++) {
        if (stat(globuff->gl_pathv[i], &file_stat) == 0) {
            write_colors_directory(globuff->gl_pathv[i], &file_stat);
        } else {
            write(STDOUT_FILENO, globuff->gl_pathv[i],
                strlen(globuff->gl_pathv[i]));
        }
        write(STDOUT_FILENO, "  ", 2);
    }
    write(STDOUT_FILENO, "\n", 1);
}

/**
 * @brief Applies completion or displays matches on the current word.
 *
 * This function uses the globbing pattern to find path matches and either:
 * - Replaces the word in the input if there's a single match.
 * - Prints all matches if there are multiple.
 *
 * @param input Pointer to the input structure.
 * @param start Starting index of the word in the input string.
 * @param word_len Length of the word to be replaced.
 * @param pattern The globbing pattern to use for matching.
 * @return 0 on success, 1 on allocation failure.
 */
static int perform_globbing_autocomplete(input_t *input, int start,
    int word_len, char *pattern)
{
    glob_t globuff;
    int result = 0;

    if (glob(pattern, 0, NULL, &globuff) != 0 || globuff.gl_pathc == 0) {
        globfree(&globuff);
        return 0;
    }
    if (globuff.gl_pathc == 1)
        result = apply_single_match(input, start,
            word_len, globuff.gl_pathv[0]);
    else
        print_matches(&globuff);
    globfree(&globuff);
    return result;
}

/**
 * @brief Handles tab-autocompletion by invoking globbing logic.
 *
 * This function processes the current input to provide tab-autocompletion.
 * It extracts the current word being typed, constructs a globbing pattern,
 * and uses it to find matches. If a single match is found, it replaces the
 * word in the input. If multiple matches are found, it displays them on the
 * terminal. The function also updates the input structure and redisplays the
 * input line after processing.
 *
 * @param input Pointer to the input structure containing
 * the current input string, cursor position, and input length.
 * @param shell Pointer to the shell structure containing environment variables
 *              and other shell-related data.
 * @return 0 on success, 1 on memory allocation failure or other errors.
 */
int autocomplete_tabs(input_t *input, shell_t *shell)
{
    int start = 0;
    int word_len = 0;
    int result = 0;
    char *pattern = NULL;

    extract_word_info(input, &start, &word_len);
    pattern = construct_glob_pattern(input, start, word_len);
    if (!pattern)
        return 1;
    result = perform_globbing_autocomplete(input, start, word_len, pattern);
    free(pattern);
    display_line(input, shell);
    return result;
}
