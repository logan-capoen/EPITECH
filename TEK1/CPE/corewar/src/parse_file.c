/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** parse_file
*/

/**
 * @file parse_file.c
 * @brief Functions to parse champion files and extract their names and
 *        instructions.
 */

#include "op.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Reads data from a champion file.
 *
 * This function reads a specific portion of a binary file starting at a given
 * offset and returns the data as a null-terminated string.
 *
 * @param file The file pointer to the champion file.
 * @param buffer A pointer to a temporary buffer for reading.
 * @param offset The starting position in the file to read from.
 * @param len The number of bytes to read.
 * @return A pointer to the allocated string containing the data, or NULL on
 *         failure.
 */
static unsigned char *get_data_from_champion(FILE *file, unsigned char *buffer,
    int offset, int len)
{
    unsigned char *str = NULL;

    str = malloc(sizeof(char) * (len + 1));
    if (!(str)) {
        fclose(file);
        return NULL;
    }
    fseek(file, offset, SEEK_SET);
    for (int i = 0; i < len &&
        fread(buffer, sizeof(unsigned char), 1, file) == 1; i++) {
        str[i] = *buffer;
    }
    str[len] = '\0';
    fclose(file);
    return str;
}

/**
 * @brief Extracts the name of a champion from its binary file.
 *
 * This function reads the name of a champion from its binary file and stores
 * it in the `name` field of the `champion_t` structure.
 *
 * @param champion A pointer to the champion structure containing the filename.
 * @return 0 on success, 1 on failure (e.g., file could not be opened or memory
 *         allocation failed).
 */
static int extract_name(champion_t *champion)
{
    FILE *file = fopen(champion->filename, "rb");
    unsigned char buffer = '\0';
    int len = 0;

    if (!file)
        return 1;
    fseek(file, 4, SEEK_SET);
    for (; fread(&buffer, sizeof(unsigned char), 1, file)
        == 1 && buffer != 0; len++);
    champion->name = (char *)get_data_from_champion(file, &buffer, 4, len);
    if (!(champion->name))
        return 1;
    return 0;
}

/**
 * @brief Extracts the names of all champions in the arena.
 *
 * This function iterates over all champions in the arena and calls
 * `extract_name` for each of them to populate their `name` fields.
 *
 * @param arena A pointer to the arena structure containing the champions.
 * @return 0 on success, 1 if any champion's name could not be extracted.
 */
int get_names(arena_t *arena)
{
    for (int i = 0; i < arena->nb_champions; i++)
        if (extract_name(arena->champions[i]))
            return 1;
    return 0;
}

/**
 * @brief Extracts the instructions of a champion from its binary file.
 *
 * This function reads the instructions of a champion from its binary file,
 * starting after the header and name, and stores them in the `instructions`
 * field of the `champion_t` structure.
 *
 * @param champion A pointer to the champion structure containing the filename.
 * @return A pointer to the allocated instructions data, or NULL on failure.
 */
unsigned char *extract_instructions(champion_t *champion)
{
    FILE *file = fopen(champion->filename, "rb");
    unsigned char buffer = '\0';
    int offset = 0;
    int len = 0;

    if (!file)
        return NULL;
    for (; fread(&buffer, sizeof(unsigned char), 1, file) == 1 &&
        check_instruction(buffer) == -1; offset++);
    fseek(file, offset, SEEK_SET);
    for (; fread(&buffer, sizeof(unsigned char), 1, file) == 1; len++);
    champion->len = len;
    return get_data_from_champion(file, &buffer, offset, len);
}
