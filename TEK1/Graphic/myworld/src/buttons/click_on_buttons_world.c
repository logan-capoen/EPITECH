/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** click_on_buttons
*/

#include "myworld.h"

void click_on_back(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;
    world_t world = game_params->world;

    hitbox = sfSprite_getGlobalBounds(buttons[2].button);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y)) {
        game_params->scene = 0;
        world.zoom = 1.0 / (world.size) * 850;
        world.offset_x = game_params->window_size.x / 2.25 -
        (world.size * world.zoom) / 2.0;
        world.offset_y = game_params->window_size.y / 5.0 -
        (world.size * world.zoom) / 1.5;
        world.rotation_horizontal = 60.0;
        world.rotation_vertical = 20.0;
        sfView_reset(game_params->world.camera, (sfFloatRect){0, 0, 1920, 1080});
    }
}

void click_on_save(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons[4].button);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y)) {
        printf("Detected button\n");
        save_map(&(game_params->world));
    }
}

void click_on_up(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons[5].button);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y)) {
        game_params->world.brush = 1;
    }
}

void click_on_empty(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons[6].button);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y)) {
        game_params->world.brush = 0;
    }
}

void click_on_down(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons[7].button);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        game_params->world.brush = -1;
}
