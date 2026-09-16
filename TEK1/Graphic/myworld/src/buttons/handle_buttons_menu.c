/*
** EPITECH PROJECT, 2024
** handle_buttons_menu.c
** File description:
** handle all buttons in the menu
*/

#include "myworld.h"
#include <stdlib.h>
#include <stdio.h>
#include "printf.h"
#include "my.h"

void click_on_quit(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons[1].button);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y))
        sfRenderWindow_close(game_params->window);
}

static void set_loaded_map(game_params_t *game_params, int **tab, int size)
{
    if (tab != NULL)
        game_params->world.map = tab;
    game_params->world.zoom = 1.0 / (game_params->world.size) * 850;
    game_params->world.offset_x = game_params->window_size.x / 2.25 -
        (game_params->world.size * game_params->world.zoom) / 2.0;
    game_params->world.offset_y = game_params->window_size.y / 5.0 -
        (game_params->world.size * game_params->world.zoom) / 1.5;
}

void click_on_load(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox = sfSprite_getGlobalBounds(buttons[3].button);
    int **tab = NULL;
    int size = 0;

    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y)) {
        game_params->scene = 4;
        tab = load(game_params);
        if (tab != NULL)
            set_loaded_map(game_params, tab, size);
        else
            game_params->scene = 0;
    }
}

static char *handle_input_size(game_params_t *game_params,
    char *input, int *input_length)
{
    if (game_params->event.type == sfEvtClosed) {
        sfRenderWindow_close(game_params->window);
    }
    if (game_params->event.type == sfEvtTextEntered) {
        if (game_params->event.text.unicode >= '0' &&
            game_params->event.text.unicode <= '9' && *input_length < 3) {
            input[*input_length] = (char)game_params->event.text.unicode;
            (*input_length)++;
            input[*input_length] = '\0';
        }
        if (game_params->event.text.unicode == 8 && *input_length > 0) {
                (*input_length)--;
                input[*input_length] = '\0';
        }
    }
    return input;
}

static void display_size(game_params_t *game_params, char *input, sfText *text)
{
    sfText_setString(text, input);
    sfRenderWindow_clear(game_params->window, sfWhite);
    sfRenderWindow_drawSprite(game_params->window,
        game_params->menu_size, NULL);
    sfRenderWindow_drawText(game_params->window, text, NULL);
    sfRenderWindow_display(game_params->window);
}

static void loop_size_map(game_params_t *game_params, int *input_length,
    char *input, sfText *text)
{
    while (sfRenderWindow_isOpen(game_params->window)) {
        while (sfRenderWindow_pollEvent(game_params->window,
            &game_params->event))
            input = handle_input_size(game_params, input, input_length);
        display_size(game_params, input, text);
        if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
            break;
        }
    }
}

int get_size_map(game_params_t *game_params)
{
    sfText* text = create_text(game_params, (sfVector2f){650, 400}, NULL, 200);
    char *input = malloc(sizeof(char) * 4);
    int input_length = 0;
    int size = 0;

    if (input == NULL)
        return -1;
    input[0] = '\0';
    loop_size_map(game_params, &input_length, input, text);
    size = my_getnbr(input);
    if (size > 150)
        return 100;
    sfText_destroy(text);
    return size;
}

void click_on_world(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;

    hitbox = sfSprite_getGlobalBounds(buttons[0].button);
    if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y)) {
        game_params->world.size = get_size_map(game_params);
        set_loaded_map(game_params, NULL, game_params->world.size);
        game_params->scene = 4;
        game_params->world.map = create_3d_map(game_params->world.size);
    }
}
