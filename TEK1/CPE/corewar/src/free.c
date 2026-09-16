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
#include "op.h"

static void free_processes(proc_t *proc)
{
    proc_t *tmp = NULL;

    while (proc) {
        tmp = proc;
        proc = proc->next;
        free(tmp);
    }
}

static void free_champion(champion_t *champ, int valid)
{
    if (!champ)
        return;
    free_processes(champ->procs);
    if (valid) {
        if (champ->name)
            free(champ->name);
        if (champ->filename)
            free(champ->filename);
    }
    free(champ);
}

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
        free_champion(arena->champions[i], i < arena->nb_champions);
    }
    if (arena->args && arena->args->arg_type_array)
        free(arena->args->arg_type_array);
    free(arena);
}
