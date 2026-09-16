/*
** EPITECH PROJECT, 2025
** Visual Studio Live Share (Workspace)
** File description:
** lld
*/

#include "op.h"

/**
 * @brief Executes the 'lld' instruction.
 *
 * Loads a value (direct or indirect) into a register of the champion
 * and updates the carry flag of the current process accordingly.
 *
 * @param arena Pointer to the arena structure containing
 * the virtual machine state.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_lld(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *curr_proc)
{
    int arg_index = 2;
    int *arg_type_array = arena->args->arg_type_array;
    int param1 = 0;
    int id_register = 0;

    arg_index += arg_type_array[0] - 1;
    param1 = get_param(champion, arena, arg_type_array[0],
        curr_proc->pc + arg_index);
    if (arg_type_array[0] == IND_SIZE) {
        param1 = arena->vm[((curr_proc->pc + param1) + MEM_SIZE) % MEM_SIZE];
    }
    arg_index += arg_type_array[1];
    id_register = (arena->vm[curr_proc->pc + arg_index] + MEM_SIZE) % MEM_SIZE;
    if (id_register < 17 && id_register > 2)
        champion->registers[id_register - 1] = param1;
    curr_proc->carry = (param1 == 0) ? 1 : 0;
}
