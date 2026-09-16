/*
** EPITECH PROJECT, 2024
** handle_buttons_game_over.c
** File description:
** handle all buttons in the game_over menu
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"
#include "include/my.h"

void click_on_restart(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_go_restart);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        game_params->scene = 1;
}

void click_on_menu(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_go_menu);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        game_params->scene = 0;
}
