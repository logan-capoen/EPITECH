/*
** EPITECH PROJECT, 2024
** handle_buttons_mod_menu
** File description:
** handle all buttons in the skin menu
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"
#include "include/my.h"

void click_on_modsrx(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_srx);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        game_params->mod = 1;
}

void click_on_modfun(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons.button_fun);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        game_params->mod = 0;
}
