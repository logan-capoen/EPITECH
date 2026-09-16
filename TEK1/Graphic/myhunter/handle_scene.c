/*
** EPITECH PROJECT, 2024
** handle_scene.c
** File description:
** functions for handle scene
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"
#include "include/my.h"

void handle_scene_0(game_params_t *game_params, button_t buttons)
{
    if (game_params->scene == 0) {
        sfRenderWindow_display(game_params->window);
        sfRenderWindow_clear(game_params->window, sfBlack);
        sfRenderWindow_drawSprite(game_params->window,
            game_params->background_menu, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_play, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_skin, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_mod, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_quit, NULL);
    }
}

void handle_scene_1(game_params_t *game_params, button_t buttons,
    sfText *score, sfText *text_score)
{
    if (game_params->scene == 1) {
        display_lifes(*game_params);
        sfRenderWindow_display(game_params->window);
        sfRenderWindow_clear(game_params->window, sfBlack);
        sfRenderWindow_drawSprite(game_params->window,
            game_params->background, NULL);
        create_bird_after_lapstime(game_params);
        sfRenderWindow_drawText(game_params->window, text_score, NULL);
        set_score(*game_params, score);
        display_bird(*game_params);
        verify_position_bird(game_params);
        is_game_over(game_params);
    }
}

void handle_scene_2(game_params_t *game_params,
    button_t buttons, sfText *text_game_over)
{
    if (game_params->scene == 2) {
        game_params->bird = NULL;
        sfRenderWindow_display(game_params->window);
        sfRenderWindow_clear(game_params->window, sfBlack);
        sfRenderWindow_drawSprite(game_params->window,
            game_params->background, NULL);
        sfRenderWindow_drawText(game_params->window,
            text_game_over, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_go_menu, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_go_restart, NULL);
    }
}

void handle_scene_3(game_params_t *game_params, button_t buttons)
{
    if (game_params->scene == 3) {
        sfRenderWindow_display(game_params->window);
        sfRenderWindow_clear(game_params->window, sfBlack);
        sfRenderWindow_drawSprite(game_params->window,
            game_params->background_menu, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_skin_crosshair, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_skin_landing_net, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_back, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_skin_mouse, NULL);
    }
}

void handle_scene_4(game_params_t *game_params, button_t buttons)
{
    if (game_params->scene == 4) {
        sfRenderWindow_display(game_params->window);
        sfRenderWindow_clear(game_params->window, sfBlack);
        sfRenderWindow_drawSprite(game_params->window,
            game_params->background_menu, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_srx, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_fun, NULL);
        sfRenderWindow_drawSprite(game_params->window,
            buttons.button_back, NULL);
    }
}
