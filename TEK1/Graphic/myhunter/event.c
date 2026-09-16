/*
** EPITECH PROJECT, 2024
** event.c
** File description:
** handle event functions
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>

int analyse_events(game_params_t *game_params, button_t buttons)
{
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(game_params->window,
        sfMouse_getPositionRenderWindow(game_params->window), NULL);

    if (game_params->event.type == sfEvtClosed) {
        sfRenderWindow_close(game_params->window);
        return 0;
    }
    if (game_params->event.type == sfEvtKeyPressed &&
        game_params->event.key.code == sfKeyEscape) {
        sfRenderWindow_close(game_params->window);
        return 0;
    }
    if (game_params->event.type == sfEvtMouseButtonPressed)
        keypressed_event(game_params, buttons, mouse_pos);
    return 0;
}

static int event_game(game_params_t *game_params, sfVector2f mouse_pos)
{
    if (game_params->scene == 1) {
        if (game_params->mod == 0)
            sound_shoot_mod1();
        else
            play_sound("assets/sounds/shoot03.ogg", 0);
        click_on_bird(game_params, mouse_pos);
        return 1;
    }
    return 0;
}

static int event_game_over(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    if (game_params->scene == 2) {
        click_on_restart(game_params, buttons, mouse_pos);
        click_on_menu(game_params, buttons, mouse_pos);
        return 1;
    }
    return 0;
}

static int event_menu(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    if (game_params->scene == 0) {
        click_on_play(game_params, buttons, mouse_pos);
        click_on_quit(game_params, buttons, mouse_pos);
        click_on_skin(game_params, buttons, mouse_pos);
        click_on_mod(game_params, buttons, mouse_pos);
        return 1;
    }
    return 0;
}

static int event_skin(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    if (game_params->scene == 3) {
        click_on_skin_crosshair(game_params, buttons, mouse_pos);
        click_on_skin_landing_net(game_params, buttons, mouse_pos);
        click_on_back(game_params, buttons, mouse_pos);
        click_on_skin_mouse(game_params, buttons, mouse_pos);
        return 1;
    }
    return 0;
}

static int event_mod(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    if (game_params->scene == 4) {
        click_on_back(game_params, buttons, mouse_pos);
        click_on_modfun(game_params, buttons, mouse_pos);
        click_on_modsrx(game_params, buttons, mouse_pos);
        return 1;
    }
    return 0;
}

void keypressed_event(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    if (event_game(game_params, mouse_pos))
        return;
    if (event_game_over(game_params, buttons, mouse_pos))
        return;
    if (event_menu(game_params, buttons, mouse_pos))
        return;
    if (event_skin(game_params, buttons, mouse_pos))
        return;
    if (event_mod(game_params, buttons, mouse_pos))
        return;
}
