/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** free
*/

/*!
 * @file free.c
 * @brief Frees allocated memory for flags and arena structures.
 *
 * This file contains functions to free the memory allocated for the corewar
 * flags and arena.
 */
#include "../include_csfml/op.h"

/*!
 * @brief Frees memory allocated for the flags structure.
 *
 * This function frees the string holding the program's name and then frees
 * the flags structure.
 *
 * @param flags Pointer to the flags structure.
 */
void free_flags(flags_t *flags)
{
    free(flags->prog_name);
    free(flags);
}

/*!
 * @brief Frees memory allocated for the arena structure.
 *
 * This function frees the virtual machine memory, then iterates over the
 * champions array freeing each allocated champion before finally freeing the
 * arena structure.
 *
 * @param arena Pointer to the arena structure.
 */
void free_arena(arena_t *arena)
{
    if (arena->vm)
        free(arena->vm);
    for (int i = 0; i < MAX_CHAMPIONS; i++) {
        if (i < arena->nb_champions && arena->champions[i]->name)
            free(arena->champions[i]->name);
        if (i < arena->nb_champions && arena->champions[i]->filename)
            free(arena->champions[i]->filename);
        free(arena->champions[i]);
    }
    free(arena);
}
