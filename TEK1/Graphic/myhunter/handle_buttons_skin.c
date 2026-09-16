/*
** EPITECH PROJECT, 2024
** handle_buttons_skin.c
** File description:
** handle all buttons in the skin menu
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"
#include "include/my.h"

void click_on_back(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_back);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        game_params->scene = 0;
}

void click_on_skin_landing_net(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_skin_landing_net);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        set_cursor(*game_params, "assets/images/landing_net.png");
}

void click_on_skin_crosshair(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_skin_crosshair);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        set_cursor(*game_params, "assets/images/crosshair.png");
}

void click_on_skin_mouse(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_skin_mouse);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        set_cursor(*game_params, "assets/images/skin_cursor.png");
}
