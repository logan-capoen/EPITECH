/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** init_champions
*/

/*!
 * @file init_champions.c
 * @brief Initializes champions for the corewar arena.
 *
 * This file contains functions to allocate and initialize champion
 * structures in the corewar arena. Each champion is assigned an identifier
 * and default values upon initialization.
 */

#include "op.h"

/*!
 * @brief Fills the champion structure with default values.
 *
 * This function initializes the registers to 0, sets the champion as
 * alive, assigns an identifier, and initializes other attributes.
 *
 * @param champion Double pointer to the champion structure.
 * @param id The identifier for the champion.
 */
static void fill_champion(champion_t *champion, int id)
{
    for (int i = 0; i < REG_NUMBER; i++)
        champion->registers[i] = 0;
    champion->id = id;
    champion->registers[0] = id;
    champion->position = -1;
    champion->name = NULL;
}

/*!
 * @brief Initializes champions in the arena.
 *
 * This function allocates memory for each champion in the corewar arena
 * and initializes them with default values.
 *
 * @param arena Pointer to the arena structure.
 */
void init_champions(arena_t *arena)
{
    for (int i = 0; i < MAX_CHAMPIONS; i++) {
        arena->champions[i] = malloc(sizeof(champion_t));
        if (!arena->champions[i]) {
            my_puterr("Could not allocate a champion\n");
            return;
        }
        fill_champion(arena->champions[i], i + 1);
        arena->champions[i]->procs = malloc(sizeof(proc_t));
        if (!arena->champions[i]->procs)
            return;
        arena->champions[i]->procs->pc = 0;
        arena->champions[i]->procs->carry = 0;
        arena->champions[i]->procs->wait = 0;
        arena->champions[i]->procs->next = NULL;
    }
}
