/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Functions to validate instruction arguments in Corewar.
*/

/**
 * @file check_args.c
 * @brief Functions to validate instructions and their arguments.
 *
 * This file contains functions to validate the arguments of instructions
 * in the Corewar virtual machine. It ensures that the arguments match the
 * expected types and calculates their sizes.
 */

#include "op.h"
#include "tab.h"

/**
 * @brief Determines if an instruction uses a short direct value.
 *
 * Some instructions in Corewar use a short direct value (2 bytes) instead
 * of the standard direct value (4 bytes). This function checks if the given
 * opcode corresponds to one of these instructions.
 *
 * @param opcode The opcode of the instruction.
 * @return true if the instruction uses a short direct value, false otherwise.
 */
static bool use_short_dir(int opcode)
{
    return (opcode == 9 || opcode == 10 || opcode == 11 ||
            opcode == 12 || opcode == 14 || opcode == 15);
}

/**
 * @brief Calculates the size in bytes for a given argument type.
 *
 * This function determines the number of bytes to read for a given
 * argument type depending on the instruction's specification.
 *
 * @param op A pointer to the op_t structure describing the instruction.
 * @param arg_type The type of the argument (T_REG, T_DIR, T_IND).
 * @return The size in bytes of the argument, or 0 if the type is invalid.
 */
static int calculate_arg_size(const op_t *op, int arg_type)
{
    if (arg_type == T_REG)
        return T_REG;
    if (arg_type == T_DIR)
        return use_short_dir(op->code) ? IND_SIZE : DIR_SIZE;
    if (arg_type == T_IND)
        return IND_SIZE;
    return 0;
}

/**
 * @brief Validates a single argument type and updates offset.
 *
 * This function checks whether the given argument type is allowed for the
 * current instruction. If valid, it updates the offset and stores the size
 * in the argument size array.
 *
 * @param op Pointer to the instruction definition in op_tab.
 * @param arena Pointer to the arena containing the args and memory.
 * @param expected Expected type(s) for the current argument.
 * @return 1 if the type is valid, 0 otherwise.
 */
static int check_type(const op_t *op, arena_t *arena, int expected)
{
    int arg_type = arena->args->arg_type;
    int arg_size = calculate_arg_size(op, arg_type);
    int index = arena->args->arg_index;

    arena->args->arg_type_array[index] = arg_size;
    if (arg_type == T_REG && !(expected & T_REG))
        return 0;
    if (arg_type == T_DIR && !(expected & T_DIR))
        return 0;
    if (arg_type == T_IND && !(expected & T_IND))
        return 0;
    if (arg_size == 0)
        return 0;
    arena->args->offset += arg_size;
    return 1;
}

/**
 * @brief Extracts the argument type from the coding byte.
 *
 * The coding byte contains the types of the arguments. This function
 * extracts the type of the current argument based on its index.
 *
 * @param arena Pointer to the arena structure.
 * @param coding_byte The coding byte to extract from.
 * @return Extracted argument type as T_REG, T_DIR, or T_IND.
 */
static int extract_arg_type(arena_t *arena, int coding_byte)
{
    int shift = 6 - 2 * arena->args->arg_index;
    int arg_type = (coding_byte >> shift) & 0b11;

    return (arg_type == 0b11) ? 0b100 : arg_type;
}

/**
 * @brief Handles argument validation when a coding byte is present.
 *
 * Uses the coding byte to extract and validate the current argument type.
 *
 * @param op Pointer to the instruction structure.
 * @param arena Pointer to the arena structure.
 * @param coding_byte The coding byte read from memory.
 * @return 1 if the argument is valid, 0 otherwise.
 */
static int handle_coding_byte(const op_t *op, arena_t *arena, int coding_byte)
{
    arena->args->arg_type = extract_arg_type(arena, coding_byte);
    if (!check_type(op, arena, op->type[arena->args->arg_index])) {
        reset_array(arena->args->arg_type_array);
        return 0;
    }
    return 1;
}

/**
 * @brief Handles validation of argument when no coding byte exists.
 *
 * If the instruction doesn't have a coding byte, its only argument is
 * assumed to be a direct value (T_DIR).
 *
 * @param op Pointer to the instruction definition.
 * @param arena Pointer to the arena structure.
 * @return 1 if the argument is valid, 0 otherwise.
 */
static int handle_no_coding_byte(const op_t *op, arena_t *arena)
{
    arena->args->arg_type = T_DIR;
    if (!check_type(op, arena, op->type[arena->args->arg_index])) {
        reset_array(arena->args->arg_type_array);
        return 0;
    }
    return 1;
}

/**
 * @brief Dispatcher for argument checking based on coding byte presence.
 *
 * Selects the appropriate handler based on whether the instruction uses
 * a coding byte, and validates the current argument.
 *
 * @param arena Pointer to the arena structure.
 * @param position Current memory index of the instruction.
 * @return 1 if the argument is valid, 0 otherwise.
 */
static int check_args_given_codingbyte(arena_t *arena, int position)
{
    int coding_byte = arena->vm[(position + 1) % MEM_SIZE];
    const op_t *op = NULL;
    unsigned char instruction = arena->vm[position];
    int index_instructions = check_instruction(instruction);

    if (index_instructions == -1)
        return 0;
    op = &op_tab[index_instructions];
    arena->args->nb_args = op->nbr_args;
    if (check_coding_byte(instruction)) {
        return handle_coding_byte(op, arena, coding_byte);
    } else {
        return handle_no_coding_byte(op, arena);
    }
}

/**
 * @brief Validates the arguments of a Corewar instruction.
 *
 * This function reads the argument types from the coding byte or defaults
 * to T_DIR if there is no coding byte, and checks them against the expected
 * types from the op_tab.
 *
 * @param arena Pointer to the arena structure containing state and memory.
 * @param position The index of the instruction in memory.
 * @return 1 if all arguments are valid, 0 otherwise.
 */
int check_args(arena_t *arena, int position)
{
    unsigned char instruction = arena->vm[position];
    int index_instruction = instruction - 1;
    const op_t *op = NULL;

    arena->args->arg_index = 0;
    if (index_instruction == -1)
        return 0;
    op = &op_tab[index_instruction];
    if (!op)
        return 0;
    for (; arena->args->arg_index < op->nbr_args;
        arena->args->arg_index++) {
        if (check_args_given_codingbyte(arena, position) == 0)
            return 0;
    }
    return 1;
}
