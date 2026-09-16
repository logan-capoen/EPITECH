/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** main
*/

/*!
 * @file main.c
 * @brief Entry point for the program.
 *
 * This file contains the main function which initializes the arena, checks
 * command line arguments, and runs the corewar simulation.
 */
#include "op.h"

/*!
 * @brief Launches the corewar simulation.
 *
 * This function processes command line flags, initializes champion names,
 * stores starting positions and instructions, and finally frees the arena
 * memory. In case of a flag parsing error, the arena is freed and the
 * function returns an error code.
 *
 * @param arena Pointer to the arena structure.
 * @param ac Number of command line arguments.
 * @param av Array of command line argument strings.
 *
 * @return 0 on success, or 84 on error.
 */
static int init_main(arena_t *arena, int ac, char **av)
{
    if (!arena)
        return 84;
    if (parse_flag(arena, ac, av)) {
        free_arena(arena);
        return 84;
    }
    if (get_names(arena)) {
        free_arena(arena);
        return 84;
    }
    init_alive_champions(arena);
    store_positions(arena);
    if (store_instructions(arena) == 84) {
        free_arena(arena);
        return 84;
    }
    return 0;
}

/*!
 * @brief Program entry point.
 *
 * This function parses command line arguments, checks for help flag,
 * initializes the arena, and runs the corewar simulation. If any step
 * fails, it frees allocated memory and returns an error code.
 *
 * @param ac Number of command line arguments.
 * @param av Array of command line argument strings.
 *
 * @return 0 on success, or 84 on error.
 */
int main(int ac, char **av)
{
    arena_t *arena = NULL;

    if (ac == 1) {
        my_puterr("INIT: Too few warrior\n");
        return 84;
    }
    if (check_help(ac, av))
        return 0;
    arena = init_arena();
    if (init_main(arena, ac, av) == 84)
        return 84;
    for (int i = 0; i < arena->nb_champions; i++)
        arena->champions[i]->procs->pc = arena->champions[i]->position;
    return launch_corewar(arena);
}
//
// int fd = open("test.txt", O_CREAT | O_RDWR | O_TRUNC, 0600);
//     write(fd, arena->vm, MEM_SIZE);
//     close(fd);
