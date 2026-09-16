/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** aff
*/

/**
 * @file aff.c
 * @brief Implements the `aff` instruction for the Corewar VM.
 *
 * This instruction prints the value of a register as an ASCII character.
 * It reads a register number from memory and prints the value in that
 * register modulo 256 as a character.
 */

#include "op.h"

/**
 * @brief Executes the `aff` instruction.
 *
 * This function fetches a register number from memory and prints the
 * content of the register as a character (value % 256). If the register
 * number is invalid, the instruction is ignored.
 *
 * @param arena Pointer to the arena structure containing the VM memory.
 * @param champion Pointer to the champion executing the instruction.
 * @param curr_proc Pointer to the current process executing the instruction.
 */
void execute_aff(arena_t *arena,
    __attribute_maybe_unused__ champion_t *champion,
    proc_t *curr_proc)
{
    int reg = arena->vm[((curr_proc->pc + 1) + MEM_SIZE) % MEM_SIZE];
    int value = 0;

    if (reg < 3 || reg > 16)
        return;
    value = champion->registers[reg - 1];
    my_printf("AFF: %c\n", value % 256);
    return;
}
