/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** sub
*/

#include "op.h"

/**
 * @brief Executes the 'sub' instruction.
 *
 * Subtracts the value of the second register from the first register
 * and stores the result in a third register. Updates the carry flag.
 *
 * @param arena Pointer to the arena structure containing the VM state.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_sub(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *curr_proc)
{
    int register_one = arena->vm[((curr_proc->pc + 2) + MEM_SIZE) % MEM_SIZE];
    int register_two = arena->vm[((curr_proc->pc + 3) + MEM_SIZE) % MEM_SIZE];
    int register_result = arena->vm[((curr_proc->pc + 4) + MEM_SIZE) %
        MEM_SIZE];
    int result = 0;

    if (register_one < 16 && register_one > 0 &&
        register_two < 16 && register_two > 0 &&
        register_result < 16 && register_result > 0) {
        result = champion->registers[register_one] -
            champion->registers[register_two];
        curr_proc->carry = (result == 0) ? 1 : 0;
        champion->registers[register_result] = result;
    }
}
