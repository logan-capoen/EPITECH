/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** utilities
*/

/**
 * @file utilities.c
 * @brief Some function used globally in the code
 *
 * Several kind of functions
 */

#include "op.h"

/**
 * @brief Remove all the comments
 *
 * @param *buff
 * @return char* The new buffer without the comments
 */
char *remove_comments(char *buff)
{
    int len = my_strlen(buff);
    char *new_buff = malloc(sizeof(char) * (len + 1));
    int in_comment = 0;
    int index = 0;

    if (new_buff == NULL)
        return NULL;
    for (int i = 0; i < len; i++) {
        if (buff[i] == '#')
            in_comment = 1;
        if (buff[i] == '\n')
            in_comment = 0;
        if (!in_comment) {
            new_buff[index] = buff[i];
            index++;
        }
    }
    new_buff[index] = '\0';
    free(buff);
    return new_buff;
}

/**
 * @brief Check if a double quote was left alone
 *
 * @param *buff The buffer which contains all the s file
 * @return int A status code to say if a quote was left alone or not
 */
int check_wrong_quotes(char *buff)
{
    int wrong_quote = 0;

    for (int i = 0; buff[i] != 0; i++) {
        if (buff[i] == '"') {
            wrong_quote = (wrong_quote == 0) ? -1 : 0;
        }
    }
    return wrong_quote;
}

/**
 * @brief Reverse the order of four bytes
 *
 * @param num The number we have to reverse bytes from
 * @return unsigned_int The new number with reversed bytes
 */
unsigned int reverse_bytes(unsigned int num, int size)
{
    unsigned int b0;
    unsigned int b1;
    unsigned int b2;
    unsigned int b3;

    if (size == 4) {
        b0 = (num & 0x000000FF) << 24;
        b1 = (num & 0x0000FF00) << 8;
        b2 = (num & 0x00FF0000) >> 8;
        b3 = (num & 0xFF000000) >> 24;
        return b0 | b1 | b2 | b3;
    }
    if (size == 2) {
        b0 = (num & 0x00FF) << 8;
        b1 = (num & 0xFF00) >> 8;
        return b0 | b1;
    }
    return 0;
}

/**
 * @brief Get the size of the '.s' file
 *
 * @param *path The path to the file we have to get the size from
 * @return int The size of the file or -1 if failed
 */
int get_size(char *path)
{
    struct stat sb;

    if (lstat(path, &sb) == -1)
        return -1;
    return sb.st_size;
}

char *int_to_str(int num)
{
    char *buff = malloc(BIGINT_SIZE);
    int i = 0;

    if (buff == NULL)
        return NULL;
    for (int j = 0; j < BIGINT_SIZE; j++)
        buff[j] = '\0';
    if (num == 0) {
        buff[i] = '0';
        i++;
    } else {
        while (num > 0) {
            buff[i] = num % 10 + '0';
            i++;
            num /= 10;
        }
    }
    buff[i] = '\0';
    return my_revstr(buff);
}
