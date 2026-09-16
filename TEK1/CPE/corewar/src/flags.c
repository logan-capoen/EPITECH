/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** flags
*/

/*!
 * @file flags.c
 * @brief Handles flags for the corewar arena.
 *
 * This file contains functions to parse the command line flags for the
 * corewar arena, including champion files and numeric options.
 */
#include "op.h"

/*!
 * @brief Checks if the provided file is a valid champion.
 *
 * This function attempts to open the file specified by @p arg. If the file
 * exists and its extension matches the expected champion extension ("cor"),
 * the champion's filename and name are set and the champion index is
 * incremented.
 *
 * @param arena Pointer to the arena structure.
 * @param index Pointer to the current champion index.
 * @param arg Path to the potential champion file.
 *
 * @return 1 if a valid champion is found, 0 otherwise.
 */
static int check_champion(arena_t *arena, int *index, char *arg)
{
    int fd = open(arg, O_RDONLY);

    if (fd == -1)
        return 0;
    if (my_strncmp("cor", arg + my_strlen(arg) - 3, 3) == 0) {
        arena->champions[*index]->filename = my_strdup(arg);
        close(fd);
        (*index)++;
        return 1;
    }
    close(fd);
    return 0;
}

/**
 * Handles flags provided before a champion's binary in the arguments.
 *
 * This function interprets and assigns values for -a (position),
 * -n (ID), and -d (dump cycle) flags, updating the current champion or
 * arena accordingly.
 *
 * @param arena Pointer to the arena structure.
 * @param args Command-line arguments.
 * @param index Pointer to the current champion index.
 * @param i Pointer to the current argument index.
 * @return 0 on success, 1 on invalid flag or number.
 */
static int handle_champion_flags(arena_t *arena, char **args,
    int *index, int *i)
{
    int nb = my_getnbr(args[(*i) + 1]);

    if (nb < 0)
        return 1;
    if (my_strcmp(args[*i], "-a") == 0)
        arena->champions[*index]->position = (nb + MEM_SIZE) % MEM_SIZE;
    if (my_strcmp(args[*i], "-n") == 0) {
        arena->champions[*index]->id = nb;
        arena->champions[*index]->registers[0] = nb;
    }
    if (my_strcmp(args[*i], "-dump") == 0)
        arena->dump = nb;
    if (!(my_strcmp(args[*i], "-a") == 0 ||
        my_strcmp(args[*i], "-n") == 0 || my_strcmp(args[*i], "-dump") == 0))
        return 1;
    (*i)++;
    return 0;
}

/**
 * Checks if the current argument is a valid champion or a flag.
 *
 * This function first checks whether the current argument is a valid
 * champion file. If not, it tries to handle it as a flag using
 * handle_champion_flags.
 *
 * @param arena Pointer to the arena structure.
 * @param args Command-line arguments.
 * @param index Pointer to the current champion index.
 * @param i Pointer to the current argument index.
 * @return 0 if argument was processed, 1 on error.
 */
static int check_arguments(arena_t *arena, char **args,
    int *index, int *i)
{
    if (check_champion(arena, index, args[*i]))
        return 0;
    if (!args[(*i) + 1])
        return 1;
    return handle_champion_flags(arena, args, index, i);
}

/*!
 * @brief Parses command line flags and initializes arena settings.
 *
 * This function iterates through the command line arguments and calls
 * @c check_args to set champion attributes and dump options. It ensures that
 * at least two champions are provided and returns an error if flag parsing
 * fails.
 *
 * @param arena Pointer to the arena structure.
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 *
 * @return 0 if parsing is successful, or 1 if an error is detected.
 */
int parse_flag(arena_t *arena, int argc, char **argv)
{
    int index = 0;
    int return_value = 0;

    for (int i = 1; i < argc && index <= MAX_CHAMPIONS; i++)
        if (check_arguments(arena, argv, &index, &i))
            return_value = 1;
    if (index < 2) {
        my_puterr("INIT: Too few warrior");
        return 1;
    } else if (return_value) {
        my_puterr("INIT: header error");
        return 1;
    }
    arena->nb_champions = index;
    return 0;
}
