/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** lfork
*/

/**
 * @file lfork.c
 * @brief Implements the `lfork` instruction in the Corewar virtual machine.
 *
 * The `lfork` (long fork) instruction is used to create a new process at a
 * specific offset from the current process's PC, without applying the IDX_MOD.
 * This allows for larger jumps in memory.
 */

#include "op.h"

/**
 * @brief Executes the `lfork` (long fork) instruction.
 *
 * This instruction should duplicate the current process and place the new
 * process at a PC equal to the current PC plus a given direct value.
 * Unlike `fork`, `lfork` does not apply the IDX_MOD restriction.
 *
 * @param arena Pointer to the arena structure containing VM state.
 * @param champion Pointer to the champion owning the process.
 * @param proc Pointer to the current process executing the instruction.
 */
void execute_lfork(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *curr_proc)
{
    int position = (arena->vm[((curr_proc->pc + 1) + MEM_SIZE) %
        MEM_SIZE] << 8)
        | (arena->vm[((curr_proc->pc + 2) + MEM_SIZE) % MEM_SIZE]);

    create_node(champion, curr_proc->pc + position);
    return;
}
