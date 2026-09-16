/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** handle_scene_world
*/

#include "myworld.h"

static int is_scrolled(game_params_t *game_params)
{
    if (game_params->event.type == sfEvtMouseWheelScrolled) {
        if (game_params->event.mouseWheelScroll.delta > 0) {
            sfView_zoom(game_params->world.camera, 0.9f);
        }
        if (game_params->event.mouseWheelScroll.delta < 0) {
            sfView_zoom(game_params->world.camera, 1.1f);
        }
    }
}

int hover_button(button_t *button, sfVector2f mouse_pos,
    game_params_t *game_params)
{
    sfFloatRect button_rect;

    for (int i = 0; i < 8; i++) {
        button_rect = sfSprite_getGlobalBounds(button[i].button);
        if (sfFloatRect_contains(&button_rect, mouse_pos.x, mouse_pos.y)) {
            sfSprite_setTexture(button[i].button,
                button[i].button_texture_hover, sfTrue);
            return 1;
        }
        sfSprite_setTexture(button[i].button,
            button[i].button_texture, sfTrue);
    }
    return 0;
}

static void move_view(game_params_t *game_params)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        sfView_move(game_params->world.camera, (sfVector2f){0, -10});
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        sfView_move(game_params->world.camera, (sfVector2f){0, 10});
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        sfView_move(game_params->world.camera, (sfVector2f){-10, 0});
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        sfView_move(game_params->world.camera, (sfVector2f){10, 0});
    }
    sfRenderWindow_setView(game_params->window, game_params->world.camera);
}

static void rotate_view(game_params_t *game_params)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        game_params->world.rotation_horizontal -= 3;
        if (game_params->world.rotation_horizontal < 0) {
            game_params->world.rotation_horizontal += 360;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        game_params->world.rotation_horizontal += 3;
        if (game_params->world.rotation_horizontal > 360)
            game_params->world.rotation_horizontal -= 360;
    }
}

void handle_event_world(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    game_params->clock.time =
        sfClock_getElapsedTime(game_params->clock.clock);
    game_params->clock.seconds =
        game_params->clock.time.microseconds / 1000000.0;
    if (game_params->clock.seconds > 0.01) {
        move_view(game_params);
        rotate_view(game_params);
        sfClock_restart(game_params->clock.clock);
    }
    is_scrolled(game_params);
}
