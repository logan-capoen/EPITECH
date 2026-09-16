/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** utilities
*/

/**
 * @file utilities.c
 * @brief Utility functions for the Corewar virtual machine.
 *
 * Contains helper functions used throughout the Corewar implementation,
 * including parameter fetching, wait time calculation, instruction
 * validation, and memory array resets.
 */

#include "op.h"
#include "tab.h"

/**
 * @brief Retrieves a parameter value from memory or registers.
 *
 * This function extracts the value of a parameter depending on its type:
 * register, indirect, or direct. For indirect and direct types, it
 * reconstructs the value from bytes in memory.
 *
 * @param champion Pointer to the current champion structure.
 * @param arena Pointer to the arena structure (VM state).
 * @param arg_type The type of the argument (T_REG, T_IND, or T_DIR).
 * @param position The memory position from which to extract the value.
 * @return The integer value corresponding to the argument type.
 */
int get_param(champion_t *champion, arena_t *arena,
    int arg_type, int position)
{
    int combined = 0;

    switch (arg_type) {
        case T_REG:
            return champion->registers[arena->vm[position]];
        case T_IND:
            combined = (arena->vm[position - 3] << 24) |
                (arena->vm[position - 2] << 16) |
                (arena->vm[position - 1] << 8) |
                (arena->vm[position]);
            return combined;
        case T_DIR:
            combined = (arena->vm[position - 1] << 8) |
                arena->vm[position];
            return combined;
        default:
            return 0;
    }
}

/**
 * @brief Resets a 4-element integer array to -1.
 *
 * Used to clear argument type arrays or other temporary storage.
 *
 * @param arr The array to reset.
 */
void reset_array(int *arr)
{
    arr[0] = -1;
    arr[1] = -1;
    arr[2] = -1;
    arr[3] = -1;
}

/**
 * @brief Checks if a byte corresponds to a valid instruction.
 *
 * Compares a byte against the `op_tab` to verify if it matches a known
 * instruction code.
 *
 * @param byte The byte to check.
 * @return The index in `op_tab` if valid, -1 otherwise.
 */
int check_instruction(unsigned char byte)
{
    for (int i = 0; i < 16; i++) {
        if (op_tab[i].code == byte)
            return i;
    }
    return -1;
}

/**
 * @brief Determines whether an instruction includes a coding byte.
 *
 * Instructions like `live`, `zjmp`, `fork`, and `lfork` do not use a
 * coding byte. This function returns 0 for those, and 1 for others.
 *
 * @param instruction The opcode of the instruction.
 * @return 1 if it uses a coding byte, 0 otherwise.
 */
int check_coding_byte(unsigned char instruction)
{
    int indexes[4] = {1, 9, 12, 15};

    for (int i = 0; i < 4; i++)
        if (instruction == indexes[i])
            return 0;
    return 1;
}

/**
 * Creates and appends a new process node to a champion's process list.
 *
 * This function allocates a new process (proc_t), sets its default state
 * (carry = 1, wait = 0, pc = position), and adds it to the end of the
 * champion's linked list of processes.
 *
 * @param champion Pointer to the champion structure.
 * @param position Initial program counter (pc) for the new process.
 */
void create_node(champion_t *champion, int position)
{
    proc_t *new_proc = malloc(sizeof(proc_t));
    proc_t *tmp = champion->procs;

    new_proc->carry = 0;
    new_proc->wait = 0;
    new_proc->pc = position;
    new_proc->next = NULL;
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new_proc;
}
