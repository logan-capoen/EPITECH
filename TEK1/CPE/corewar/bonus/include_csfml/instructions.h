/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** instructions
*/

#ifndef INSTRUCTIONS_H
    #define INSTRUCTIONS_H
    #include "op.h"

void execute_live(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_add(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_sub(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_zjmp(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);


void execute_ld(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_st(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_and(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_or(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_xor(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_ldi(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_sti(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_fork(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_lld(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_lldi(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_lfork(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

void execute_aff(arena_t *arena, __attribute_maybe_unused__
    champion_t *champion, proc_t *proc);

typedef struct {
    char *command;
    void (*instruction_func)(arena_t *arena,
        __attribute_maybe_unused__ champion_t *champion, proc_t *proc);
} tab_instructions_t;

const tab_instructions_t tab[16] = {
    {"live", &execute_live},
    {"ld", &execute_ld}, //pas fé
    {"st", &execute_st}, //pas fé
    {"add", &execute_add},
    {"sub", &execute_sub},
    {"and", &execute_and}, //pas fé
    {"or", &execute_or}, //pas fé
    {"xor", &execute_xor}, //pas fé
    {"zjmp", &execute_zjmp},
    {"ldi", &execute_ldi}, //pas fé
    {"sti", &execute_sti}, //pas fé
    {"fork", &execute_fork}, //pas fé
    {"lld", &execute_lld}, //pas fé
    {"lldi", &execute_lldi}, //pas fé
    {"lfork", &execute_lfork}, //pas fé
    {"aff", &execute_aff} //pas fé
};
#endif //INSTRUCTIONS_H
