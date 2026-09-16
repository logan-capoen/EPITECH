/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** destroy
*/

#include "myworld.h"

void destroy_game_params(game_params_t *game_params)
{
    sfRenderWindow_destroy(game_params->window);
    sfSprite_destroy(game_params->background);
    sfSprite_destroy(game_params->background_menu);
    sfSprite_destroy(game_params->menu_size);
    sfSprite_destroy(game_params->world.background);
    for (int i = 0; i < 7; i++) {
        sfTexture_destroy(game_params->textures[i]);
    }
    free(game_params->textures);
    sfFont_destroy(game_params->font);
    sfSound_destroy(game_params->world.up);
    sfSound_destroy(game_params->world.down);
    sfView_destroy(game_params->ui);
    sfView_destroy(game_params->world.camera);
    sfClock_destroy(game_params->clock.clock);
}

void destroy_buttons(button_t *buttons)
{
    for (int i = 0; i < 8; i++) {
        sfSprite_destroy(buttons[i].button);
        sfTexture_destroy(buttons[i].button_texture);
        sfTexture_destroy(buttons[i].button_texture_hover);
        sfText_destroy(buttons[i].help);
    }
    free(buttons);
}

void destroy_map(sfVector2f **map2d, int size)
{
    for (int i = 0; i < size; i++)
        free(map2d[i]);
    free(map2d);
}
