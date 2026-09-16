/*
** EPITECH PROJECT, 2024
** event.c
** File description:
** handle event functions
*/

#include "myworld.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int analyse_events(game_params_t *game_params, button_t *buttons)
{
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(game_params->window,
        sfMouse_getPositionRenderWindow(game_params->window), game_params->ui);

    if (game_params->scene == 4)
        handle_event_world(game_params, buttons, mouse_pos);
    hover_button(buttons, mouse_pos, game_params);
    if (game_params->event.type == sfEvtClosed) {
        sfRenderWindow_close(game_params->window);
        return 0;
    }
    if (game_params->event.type == sfEvtKeyPressed &&
        game_params->event.key.code == sfKeyEscape) {
        sfRenderWindow_close(game_params->window);
        return 0;
    }
    if (game_params->event.type == sfEvtKeyPressed)
        keyboard_pressed(game_params, buttons);
    if (game_params->event.type == sfEvtMouseButtonPressed)
        keypressed_event(game_params, buttons, mouse_pos);
    return 0;
}

static int event_menu(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    if (game_params->scene == 0) {
        click_on_quit(game_params, buttons, mouse_pos);
        click_on_load(game_params, buttons, mouse_pos);
        click_on_world(game_params, buttons, mouse_pos);
        return 1;
    }
    return 0;
}

static int event_world(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    if (game_params->scene == 4) {
        click_on_back(game_params, buttons, mouse_pos);
        click_on_map(game_params);
        click_on_save(game_params, buttons, mouse_pos);
        click_on_up(game_params, buttons, mouse_pos);
        click_on_empty(game_params, buttons, mouse_pos);
        click_on_down(game_params, buttons, mouse_pos);
        return 1;
    }
    return 0;
}

void keypressed_event(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    if (event_menu(game_params, buttons, mouse_pos))
        return;
    if (event_world(game_params, buttons, mouse_pos)) {
        return;
    }
}

void keyboard_pressed(game_params_t *game_params, button_t *buttons)
{
    if (game_params->event.key.code == sfKeyU)
        game_params->world.brush = 1;
    if (game_params->event.key.code == sfKeyI)
        game_params->world.brush = -1;
    if (game_params->event.key.code == sfKeyR)
        reset_map(game_params);
    if (game_params->event.key.code == sfKeyB)
        game_params->world.brush = 0;
    if (game_params->event.key.code == sfKeyAdd)
        game_params->world.radius++;
    if (game_params->event.key.code == sfKeySubtract
        && game_params->world.radius > 1)
        game_params->world.radius--;
}
