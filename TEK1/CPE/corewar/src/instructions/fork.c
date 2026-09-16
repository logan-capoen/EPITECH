/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** fork
*/

/**
 * @file fork.c
 * @brief Stub implementation of the `fork` instruction for Corewar.
 *
 * This file defines the `fork` instruction handler, which is intended to
 * duplicate a process at a specified address. This current implementation is
 * a placeholder and does not perform any operations.
 */

#include "op.h"

/**
 * @brief Executes the `fork` instruction.
 *
 * In Corewar, `fork` creates a new process at a position
 * defined relative to the current one. This function is
 * currently a stub and does not yet implement the expected behavior.
 *
 * @param arena Pointer to the arena containing VM state and memory.
 * @param champion Pointer to the champion executing the instruction.
 * @param proc Pointer to the process executing the instruction.
 */
void execute_fork(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *curr_proc)
{
    int position = (arena->vm[((curr_proc->pc + 1) + MEM_SIZE) %
        MEM_SIZE] << 8)
        | (arena->vm[((curr_proc->pc + 2) + MEM_SIZE) % MEM_SIZE]);

    create_node(champion, curr_proc->pc + position % IDX_MOD);
    return;
}
