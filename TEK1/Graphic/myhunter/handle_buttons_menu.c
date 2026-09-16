/*
** EPITECH PROJECT, 2024
** handle_buttons_menu.c
** File description:
** handle all buttons in the menu
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"
#include "include/my.h"

void click_on_play(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_play);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        game_params->scene = 1;
}

void click_on_quit(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_quit);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        sfRenderWindow_close(game_params->window);
}

void click_on_skin(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_skin);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        game_params->scene = 3;
}

void click_on_mod(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_mod);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        game_params->scene = 4;
}
