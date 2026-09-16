/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** handle_event
*/

#include "../../include_csfml/op.h"

int analyse_events(arena_t *arena)
{
    if (arena->params->event.type == sfEvtClosed) {
        sfRenderWindow_close(arena->params->window);
        return 0;
    }
    if (arena->params->event.type == sfEvtKeyPressed &&
        arena->params->event.key.code == sfKeyEscape) {
        sfRenderWindow_close(arena->params->window);
        return 0;
    }
    if (arena->params->event.type == sfEvtMouseButtonPressed) {
        act_buttons(arena, arena->params->event.mouseButton);
    }
    return 0;
}
