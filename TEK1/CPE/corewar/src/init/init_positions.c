/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** init_positions
*/

/*!
 * @file init_positions.c
 * @brief Computes and assigns starting positions for champions.
 *
 * This file contains functions for computing and storing starting positions
 * for all champions in the arena, ensuring they are evenly distributed.
 */
#include "op.h"

/*!
 * @brief Computes and assigns the starting position for a champion.
 *
 * This function calculates the starting position for the champion at
 * index @p i by dividing the arena's memory evenly among all champions.
 *
 * @param arena Pointer to the arena structure.
 * @param i Index of the champion.
 */
static void compute_position(arena_t *arena, int i)
{
    int position = (MEM_SIZE / arena->nb_champions) * i;

    arena->champions[i]->position = position;
}

/*!
 * @brief Stores starting positions for all champions.
 *
 * This function iterates through all champions in the arena. If a champion's
 * position is unset (equal to -1), it computes and
 * assigns a starting position.
 *
 * @param arena Pointer to the arena structure.
 */
void store_positions(arena_t *arena)
{
    for (int i = 0; i < arena->nb_champions; i++) {
        if (arena->champions[i]->position == -1)
            compute_position(arena, i);
    }
}
