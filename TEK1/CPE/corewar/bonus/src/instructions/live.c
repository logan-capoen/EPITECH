/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** live
*/

/**
 * @file live.c
 * @brief Implements the `live` instruction for the Corewar virtual machine.
 *
 * The `live` instruction is used by a champion
 * to indicate that it is still alive. It helps the virtual machine determine
 * which champions are active and which can be eliminated.
 */

#include "../../include_csfml/op.h"

/**
 * @brief Retrieves the index of a champion by its ID.
 *
 * Searches the list of champions in the arena to find the one
 * with the given ID.
 *
 * @param id The ID of the champion to search for.
 * @param arena Pointer to the arena structure.
 * @return The index of the champion in the arena's champion list,
 * or -1 if not found.
 */
int id_to_index(int id, arena_t *arena)
{
    for (int i = 0; i < arena->nb_champions; i++) {
        if (arena->champions[i]->id == id)
            return i;
    }
    return -1;
}

/**
 * @brief Executes the `live` instruction.
 *
 * This instruction announces that the current champion is alive.
 * It reads the champion ID from the memory following the program counter
 * and marks the corresponding champion as live.
 *
 * @param arena Pointer to the arena structure.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the process executing the instruction.
 */
void execute_live(arena_t *arena,
    __attribute_maybe_unused__ champion_t *champion,
    proc_t *curr_proc)
{
    int id = (arena->vm[((curr_proc->pc + 1) + MEM_SIZE) % MEM_SIZE] << 24) |
        (arena->vm[((curr_proc->pc + 2) + MEM_SIZE) % MEM_SIZE] << 16) |
        (arena->vm[((curr_proc->pc + 3) + MEM_SIZE) % MEM_SIZE] << 8) |
        (arena->vm[((curr_proc->pc + 4) + MEM_SIZE) % MEM_SIZE]);
    int index = id_to_index(id, arena);

    if (index == -1)
        return;
    arena->live_signals[index] = true;
    arena->nb_live_signals += 1;
    my_printf("The player %i(%s) is alive.\n", champion->id, champion->name);
}
