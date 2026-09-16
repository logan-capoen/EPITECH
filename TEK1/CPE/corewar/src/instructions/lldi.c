/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** lldi
*/

#include "op.h"

/**
 * @brief Executes the 'lldi' instruction.
 *
 * Loads a value from memory calculated by adding two parameters,
 * then stores the result in a register and updates the carry flag.
 *
 * @param arena Pointer to the arena structure containing the VM state.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_lldi(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *curr_proc)
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
    result = param1 + param2;
    curr_proc->carry = (result == 0) ? 1 : 0;
    if (param3 < 17 && param3 > 2)
        champion->registers[param3 - 1] =
            arena->vm[(curr_proc->pc + result + MEM_SIZE) % MEM_SIZE];
}
