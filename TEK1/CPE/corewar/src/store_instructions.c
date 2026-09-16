/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** store_instructions
*/

/**
 * @file store_instructions.c
 * @brief Functions to store instructions in the virtual machine.
 *
 * This file contains the implementation of functions that handle the
 * storage of champion instructions into the Corewar virtual machine's
 * memory space.
 */

#include "op.h"

/**
 * @brief Fills the VM memory with a champion's instructions.
 *
 * Copies a champion's compiled instructions into the virtual machine's
 * memory starting at a given position. Handles wrapping around the memory
 * size (circular memory model).
 *
 * @param arena Pointer to the arena structure.
 * @param i Index of the champion whose code is being loaded.
 * @return 0 on success, 84 on failure (e.g., memory allocation error).
 */
static int fill_vm(arena_t *arena, int i)
{
    int index = 0;
    int position = arena->champions[i]->position;
    unsigned char *instructions =
        extract_instructions(arena->champions[i]);
    int len_champion = arena->champions[i]->len;

    if (!instructions)
        return 84;
    for (int j = position; j < position + len_champion; j++) {
        arena->vm[j % MEM_SIZE] = instructions[index];
        index++;
    }
    free(instructions);
    return 0;
}

/**
 * @brief Stores each champion's instructions in the VM memory.
 *
 * Iterates over all champions in the arena, extracting and copying
 * their instructions into the virtual machine's memory using `fill_vm`.
 *
 * @param arena Pointer to the arena structure.
 * @return 0 on success, 84 if an error occurs during instruction loading.
 */
int store_instructions(arena_t *arena)
{
    for (int i = 0; i < arena->nb_champions; i++) {
        if (fill_vm(arena, i) == 84)
            return 84;
    }
    return 0;
}
