/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** zjmp
*/

#include "op.h"

/**
 * @brief Executes the 'zjmp' instruction.
 *
 * Jumps to a new position in the arena if the carry flag is set.
 *
 * The jump offset is a signed 16-bit value read from the
 * instruction arguments.
 * The actual jump position is calculated modulo IDX_MOD.
 *
 * @param arena Pointer to the arena structure containing the VM state.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_zjmp(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *curr_proc)
{
    int position = (arena->vm[((curr_proc->pc + 1)+ MEM_SIZE) % MEM_SIZE] << 8)
        | (arena->vm[((curr_proc->pc + 2) + MEM_SIZE) % MEM_SIZE]);

    if (position & 0x8000)
        position -= 0x10000;
    if (curr_proc->carry != 1) {
        curr_proc->pc++;
        return;
    }
    curr_proc->pc = (curr_proc->pc + position % IDX_MOD + MEM_SIZE) % MEM_SIZE;
}
