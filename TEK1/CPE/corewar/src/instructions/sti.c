/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** sti
*/

#include "op.h"

/**
 * @brief Executes the 'sti' instruction.
 *
 * Stores the value of a register at an address computed from the sum
 * of two parameters relative to the current process's program counter.
 *
 * @param arena Pointer to the arena structure containing the VM state.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_sti(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *curr_proc)
{
    int arg_index = 2;
    int *arg_type_array = arena->args->arg_type_array;
    int param1 = 0;
    int param2 = 0;
    int param3 = 0;
    int result = 0;

    arg_index += arg_type_array[0] - 1;
    param1 = arena->vm[(curr_proc->pc + arg_index + MEM_SIZE) % MEM_SIZE];
    arg_index += arg_type_array[1];
    param2 = get_param(champion, arena, arg_type_array[1],
        curr_proc->pc + arg_index);
    arg_index += arg_type_array[2];
    param3 = get_param(champion, arena, arg_type_array[2],
        curr_proc->pc + arg_index);
    result = curr_proc->pc + (param2 + param3) % IDX_MOD;
    arena->vm[result + 3] = champion->registers[param1 - 1];
}
