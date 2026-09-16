/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** add
*/

/**
 * @file add.c
 * @brief Implements the `add` instruction for the Corewar VM.
 *
 * This file contains the function that executes the `add` operation,
 * which sums the contents of two registers and stores the result in a
 * third register. It also sets the carry flag based on the result.
 */

#include "op.h"

/**
 * @brief Executes the `add` instruction.
 *
 * Reads three register numbers from memory, verifies their validity,
 * adds the values from the first two registers, and stores the result
 * in the third register. Updates the carry flag to 1 if the result is 0,
 * or to 0 otherwise.
 *
 * @param arena Pointer to the arena structure containing VM memory.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_add(arena_t *arena,
    __attribute_maybe_unused__ champion_t *champion,
    proc_t *curr_proc)
{
    int register_one = arena->vm[((curr_proc->pc + 2) + MEM_SIZE) % MEM_SIZE];
    int register_two = arena->vm[((curr_proc->pc + 3) + MEM_SIZE) % MEM_SIZE];
    int register_result = arena->vm[
        (curr_proc->pc + 4 + MEM_SIZE) % MEM_SIZE];
    int result = 0;

    if (register_one < 17 && register_one > 2 &&
        register_two < 17 && register_two > 2 &&
        register_result < 17 && register_result > 2) {
        result = champion->registers[register_one - 1] +
            champion->registers[register_two - 1];
        curr_proc->carry = (result == 0) ? 1 : 0;
        champion->registers[register_result - 1] = result;
    }
}
