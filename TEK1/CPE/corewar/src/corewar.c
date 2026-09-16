/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** Corewar main loop and instruction execution logic.
*/

/**
 * @file corewar.c
 * @brief Corewar game logic implementation.
 *
 * This file contains the main functions for managing the Corewar game,
 * including checking champion statuses, executing instructions, and
 * determining the winner.
 */

#include "op.h"
#include "instructions.h"
#include "tab.h"

/**
 * @brief Checks if only one champion is still alive.
 *
 * Iterates through the alive_champions array and counts the number of
 * champions still marked as alive. Returns 1 if one or none are alive,
 * otherwise returns 0.
 *
 * @param arena Pointer to the arena structure.
 * @return 1 if one or no champions are alive, 0 otherwise.
 */
static int is_one_standing(arena_t *arena)
{
    int nb_alive = 0;

    for (int i = 0; i < MAX_CHAMPIONS; i++)
        if (arena->alive_champions[i] == true)
            nb_alive++;
    if (nb_alive <= 1)
        return 1;
    return 0;
}

/**
 * @brief Updates the alive status of champions based on live signals.
 *
 * Champions that have not sent a live signal are marked as dead and a
 * message is printed indicating their death.
 *
 * @param arena Pointer to the arena structure.
 */
static void check_if_alive(arena_t *arena)
{
    for (int i = 0; i < arena->nb_champions; i++) {
        if (arena->live_signals[i] == false) {
            arena->alive_champions[i] = false;
        }
    }
}

/**
 * @brief Checks if the cycle-to-die threshold has been reached.
 *
 * If the number of cycles is a multiple of CYCLE_TO_DIE, then the function
 * checks which champions are still alive.
 *
 * @param arena Pointer to the arena structure.
 * @param cycle_to_die Current cycle count to check against CYCLE_TO_DIE.
 */
static void check_cycle_to_die(arena_t *arena, int cycle_to_die)
{
    if (cycle_to_die != 0 && cycle_to_die % (CYCLE_TO_DIE -
        (CYCLE_DELTA * (arena->nb_live_signal / NBR_LIVE))) == 0)
        check_if_alive(arena);
}

/**
 * @brief Initializes and executes the current instruction for a process.
 *
 * Checks the current instruction in memory and executes it if valid.
 * If the instruction is not valid, the program counter is simply advanced.
 * Handles waiting cycles and instruction execution.
 *
 * @param arena Pointer to the arena structure.
 * @param champion Pointer to the champion structure.
 * @param first_loop Pointer to the first loop counter.
 * @param curr_proc Pointer to the current process.
 */
static void initialize_execution(arena_t *arena, champion_t *champion,
    int *first_loop, proc_t *curr_proc)
{
    int instruction = arena->vm[curr_proc->pc];
    int index_instruction = check_instruction(instruction);

    if (index_instruction == -1) {
        curr_proc->pc = (curr_proc->pc + 1) % MEM_SIZE;
        return;
    }
    if (*first_loop == 0) {
        tab[index_instruction].instruction_func(arena, champion, curr_proc);
        if (my_strcmp(op_tab[index_instruction].mnemonique, "zjmp"))
            curr_proc->pc = (curr_proc->pc + arena->args->offset) % MEM_SIZE;
        instruction = arena->vm[curr_proc->pc];
        curr_proc->wait = op_tab[instruction - 1].nbr_cycles;
    } else {
        curr_proc->wait = op_tab[index_instruction].nbr_cycles;
        (*first_loop)--;
    }
}

/**
 * @brief Executes instructions for a given champion's process.
 *
 * Verifies the instruction and its arguments. If the process has a wait
 * time, it is decremented. If the process is ready, the instruction is
 * executed.
 *
 * @param arena Pointer to the arena structure.
 * @param champion Pointer to the champion structure.
 * @param first_loop Pointer to the first loop counter.
 * @param curr_proc Pointer to the current process.
 */
static void execute_instructions(arena_t *arena, champion_t *champion,
    int *first_loop, proc_t *curr_proc)
{
    int value = 0;

    arena->args->offset = (check_coding_byte
        (arena->vm[(curr_proc->pc + MEM_SIZE) % MEM_SIZE]) ? 2 : 1);
    value = check_args(arena, curr_proc->pc);
    if (!value) {
        return;
    }
    if (curr_proc->wait > 0) {
        curr_proc->wait--;
        return;
    }
    initialize_execution(arena, champion, first_loop, curr_proc);
}

/**
 * @brief Iterates through all champions and executes their processes.
 *
 * For each champion, traverses its list of processes and executes the
 * current instruction if applicable.
 *
 * @param arena Pointer to the arena structure.
 * @param tmp_proc Temporary pointer to a process (unused here).
 * @param first_loop Pointer to the first loop counter.
 */
static void browse_champs(arena_t *arena, proc_t *tmp_proc, int *first_loop)
{
    for (int i = 0; i < arena->nb_champions; i++) {
        tmp_proc = arena->champions[i]->procs;
        for (; tmp_proc != NULL; tmp_proc = tmp_proc->next)
            execute_instructions(arena, arena->champions[i],
                first_loop, tmp_proc);
    }
}

static int check_winning(arena_t *arena)
{
    int last = 0;

    for (; last < MAX_CHAMPIONS &&
        arena->alive_champions[last] == false; last++);
    if (!arena->alive_champions[last]) {
        my_puterr("Nobody survives.\n");
        free_arena(arena);
        return 0;
    }
    my_printf("The player %i(%s) has won.\n",
        arena->champions[last]->id, arena->champions[last]->name);
    free_arena(arena);
    return 0;
}

/**
 * @brief Launches the Corewar game loop.
 *
 * Initializes the necessary data and repeatedly processes cycles until
 * only one champion remains. Frees the arena at the end.
 *
 * @param arena Pointer to the arena structure.
 * @return 0 on successful completion of the game, 84 on error.
 */
int launch_corewar(arena_t *arena)
{
    int nb_cycle = 0;
    int first_loop = arena->nb_champions;
    args_t args = {0, 0, 0, malloc(sizeof(int) * MAX_ARGS), 0};
    proc_t *tmp_proc = NULL;

    if (!args.arg_type_array)
        return 84;
    arena->args = &args;
    while (!is_one_standing(arena) && nb_cycle != arena->dump) {
        nb_cycle++;
        check_cycle_to_die(arena, nb_cycle);
        browse_champs(arena, tmp_proc, &first_loop);
    }
    return check_winning(arena);
}
