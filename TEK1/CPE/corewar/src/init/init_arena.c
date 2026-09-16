/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** init
*/

/*!
 * @file init_arena.c
 * @brief Initializes the corewar arena.
 *
 * This file contains functions to initialize the arena, including the
 * virtual machine, live signals, and champions.
 * It is part of the EPITECH PROJECT, 2025.
 */
#include "op.h"

/*!
 * @brief Initializes alive champions in the arena.
 *
 * This function sets each champions life to true.
 * It is the global array that is modified when CYCLE_TO_DIE is passed.
 *
 * @param arena Pointer to the arena structure.
 */
void init_alive_champions(arena_t *arena)
{
    for (int i = 0; i < MAX_CHAMPIONS; i++) {
        arena->alive_champions[i] = (i < arena->nb_champions);
    }
}

/*!
 * @brief Initializes live signals in the arena.
 *
 * This function sets the first four live signals to false.
 * It is modified when champions send the 'live' instructions.
 *
 * @param arena Pointer to the arena structure.
 */
static void init_live_signals(arena_t *arena)
{
    arena->live_signals[0] = false;
    arena->live_signals[1] = false;
    arena->live_signals[2] = false;
    arena->live_signals[3] = false;
}

/*!
 * @brief Checks that the arena components are properly initialized.
 *
 * This function verifies that the virtual machine is allocated and filled,
 * and that the champions array is properly populated.
 *
 * @param arena Pointer to the arena structure.
 *
 * @return 0 if initialization is valid, 1 if an error occurred.
 */
static int check_initialization(arena_t *arena)
{
    if (!arena->vm) {
        my_puterr("Vm not allocated\n");
        free_arena(arena);
        return 1;
    }
    if (*arena->vm) {
        my_puterr("Vm not properly filled\n");
        free_arena(arena);
        return 1;
    }
    if (!*arena->champions) {
        my_puterr("Chmapions array not filled\n");
        free_arena(arena);
        return 1;
    }
    return 0;
}

/*!
 * @brief Initializes the arena.
 *
 * This function allocates the arena structure, initializes the virtual
 * machine, live signals, champions, and sets a default dump flag.
 *
 * @return Pointer to the initialized arena, or NULL if an error occurred.
 */
arena_t *init_arena(void)
{
    arena_t *arena = malloc(sizeof(arena_t));

    if (!arena) {
        my_puterr("Arena structure allocation error\n");
        return NULL;
    }
    arena->vm = init_vm();
    arena->nb_champions = 0;
    init_live_signals(arena);
    arena->dump = -1;
    arena->nb_live_signal = 0;
    init_champions(arena);
    if (check_initialization(arena))
        return NULL;
    return arena;
}
