/*
** EPITECH PROJECT, 2025
** Visual Studio Live Share (Workspace)
** File description:
** or
*/

#include "../../include_csfml/op.h"

/**
 * @brief Executes the 'or' instruction.
 *
 * Performs a bitwise OR between two parameters and stores the result
 * in a specified register.
 *
 * @param arena Pointer to the arena structure containing the VM state.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_or(arena_t *arena, __attribute_maybe_unused__
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
    if (param3 < 17 && param3 > 2)
        champion->registers[param3 - 1] = param1 | param2;
}
