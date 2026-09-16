/*
** EPITECH PROJECT, 2024
** handle_scene.c
** File description:
** functions for handle scene
*/

#include "myworld.h"
#include <stdlib.h>
#include <stdio.h>
#include "printf.h"
#include "my.h"

void handle_scene_menu(game_params_t *game_params, button_t *buttons)
{
    if (game_params->scene == 0) {
        sfRenderWindow_setView(game_params->window, game_params->ui);
        sfRenderWindow_drawSprite(game_params->window,
            game_params->background_menu, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons[0].button, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons[1].button, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons[3].button, NULL);
        display_help(buttons, game_params);
        sfRenderWindow_display(game_params->window);
        sfRenderWindow_clear(game_params->window, sfBlack);
    }
}

static void draw_world_buttons(game_params_t *game_params, button_t *buttons)
{
    sfRenderWindow_drawSprite(game_params->window,
        buttons[2].button, NULL);
    sfRenderWindow_drawSprite(game_params->window,
        buttons[4].button, NULL);
    sfRenderWindow_drawSprite(game_params->window,
        buttons[5].button, NULL);
    sfRenderWindow_drawSprite(game_params->window,
        buttons[6].button, NULL);
    sfRenderWindow_drawSprite(game_params->window,
        buttons[7].button, NULL);
}

void handle_scene_world(game_params_t *game_params, button_t *buttons)
{
    if (game_params->scene == 4) {
        sfRenderWindow_setView(game_params->window, game_params->ui);
        sfRenderWindow_drawSprite(game_params->window,
            game_params->world.background, NULL);
        sfRenderWindow_setView(game_params->window, game_params->world.camera);
        display_world(game_params);
        sfRenderWindow_setView(game_params->window, game_params->ui);
        draw_world_buttons(game_params, buttons);
        display_help(buttons, game_params);
        sfRenderWindow_display(game_params->window);
        sfRenderWindow_clear(game_params->window, sfBlack);
    }
}
