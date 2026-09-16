/*
** EPITECH PROJECT, 2025
** Visual Studio Live Share (Workspace)
** File description:
** st
*/

#include "op.h"

/**
 * @brief Executes the 'st' instruction.
 *
 * Stores the value of a register either into another register or
 * into the arena's memory at a calculated address.
 *
 * @param arena Pointer to the arena structure containing the VM state.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_st(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *curr_proc)
{
    int arg_index = 3;
    int *arg_type_array = arena->args->arg_type_array;
    int param1 = 0;
    int param2 = 0;

    param1 = arena->vm[(curr_proc->pc + 2 + MEM_SIZE) % MEM_SIZE];
    arg_index += arg_type_array[1] - 1;
    if (arg_type_array[0] == T_REG) {
        param2 = arena->vm[(curr_proc->pc + 3 + MEM_SIZE) % MEM_SIZE];
        if ((param1 < 17 && param1 > 2) && (param2 < 17 && param2 > 2))
            champion->registers[param2 - 1] = champion->registers[param1 - 1];
    } else {
        param2 = get_param(champion, arena, arg_type_array[1],
            curr_proc->pc + arg_index);
        if (param1 < 17 && param1 > 2)
        arena->vm[curr_proc->pc + param2 % IDX_MOD] =
            champion->registers[param1 - 1];
    }
    return;
}
