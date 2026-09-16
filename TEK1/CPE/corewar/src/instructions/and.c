/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** and
*/

/**
 * @file and.c
 * @brief Implements the `and` instruction for the Corewar VM.
 *
 * This instruction performs a bitwise AND operation between two operands
 * and stores the result in a register. It also updates the carry flag
 * based on whether the result is zero.
 */

#include "op.h"

/**
 * @brief Executes the `and` instruction.
 *
 * This function fetches two parameters from memory based on their types,
 * performs a bitwise AND operation, and stores the result in the target
 * register. It also updates the carry flag depending on whether the result
 * is zero.
 *
 * @param arena Pointer to the arena containing VM state and memory.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the process executing the instruction.
 */
void execute_and(arena_t *arena,
    __attribute_maybe_unused__ champion_t *champion,
    proc_t *curr_proc)
{
    int arg_index = 2;
    int *arg_type_array = arena->args->arg_type_array;
    int param1 = 0;
    int param2 = 0;
    int param3 = 0;
    int result = 0;

    arg_index += arg_type_array[0] - 1;
    param1 = get_param(champion, arena, arg_type_array[0],
        curr_proc->pc + arg_index);
    arg_index += arg_type_array[1];
    param2 = get_param(champion, arena, arg_type_array[1],
        curr_proc->pc + arg_index);
    arg_index += arg_type_array[2];
    param3 = arena->vm[(curr_proc->pc + arg_index + MEM_SIZE) % MEM_SIZE];
    result = param1 & param2;
    curr_proc->carry = (result == 0) ? 1 : 0;
    if (param1 > 2 && param1 < 17)
        champion->registers[param3 - 1] = result;
}
