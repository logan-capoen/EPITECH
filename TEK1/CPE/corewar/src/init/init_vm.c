/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** init_vm
*/

/*!
 * @file init_vm.c
 * @brief Initializes the virtual machine memory.
 *
 * This file contains the implementation of the function to allocate and
 * initialize the virtual machine for the corewar arena.
 */
#include "op.h"

/*!
 * @brief Allocates and initializes the virtual machine memory.
 *
 * This function allocates memory for the virtual machine, initializes all
 * bytes to 0, and appends a null terminator at the end.
 *
 * @return A pointer to the initialized virtual machine memory, or NULL if
 * memory allocation fails.
 */
unsigned char *init_vm(void)
{
    unsigned char *vm = malloc(sizeof(char) * (MEM_SIZE + 1));

    if (!vm) {
        my_puterr("Could not allocate vm space\n");
        return NULL;
    }
    *vm = 0;
    for (int i = 0; i < MEM_SIZE; i++) {
        vm[i] = 0;
    }
    vm[MEM_SIZE] = '\0';
    return vm;
}
