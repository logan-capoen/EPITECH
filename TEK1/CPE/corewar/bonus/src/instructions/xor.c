/*
** EPITECH PROJECT, 2025
** Visual Studio Live Share (Workspace)
** File description:
** xor
*/

#include "../../include_csfml/op.h"

/**
 * @brief Executes the 'xor' instruction.
 *
 * Performs a bitwise XOR operation between two parameters and stores
 * the result in a register.
 *
 * @param arena Pointer to the arena structure containing the VM state.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_xor(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *curr_proc)
{
    int arg_index = 2;
    int *arg_type_array = arena->args->arg_type_array;
    int param1 = 0;
    int param2 = 0;
    int param3 = 0;

    arg_index += arg_type_array[0] - 1;
    param1 = get_param(champion, arena, arg_type_array[0],
        curr_proc->pc + arg_index);
    arg_index += arg_type_array[1];
    param2 = get_param(champion, arena, arg_type_array[1],
        curr_proc->pc + arg_index);
    arg_index += arg_type_array[2];
    param3 = arena->vm[(curr_proc->pc + arg_index + MEM_SIZE) % MEM_SIZE];
    champion->registers[param3 - 1] = param1 ^ param2;
}
