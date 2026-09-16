/*
** EPITECH PROJECT, 2025
** tmp_core
** File description:
** buttons
*/

#include "../../include_csfml/op.h"

static void handle_champion_button(game_params_t *params, int i)
{
    if (params->buttons[i]->file)
        free(params->buttons[i]->file);
    params->buttons[i]->file = file_explorer_load();
    sfRectangleShape_setFillColor(params->buttons[i]->rect, sfRed);
}

static void handle_launch_button(arena_t *arena)
{
    int ac = 0;
    char **array = NULL;

    if (check_launch_condition(arena->params)) {
        array = convert_champions(arena->params, &ac);
        arena->params->menu = 0;
        if (init_main(arena, ac, array))
            exit(84);
        for (int i = 0; i < arena->nb_champions; i++)
            arena->champions[i]->procs->pc = arena->champions[i]->position;
    }   
    else
        dprintf(2, "Refused launch choose 2 champions minimum\n");
}

void act_buttons(arena_t *arena, sfMouseButtonEvent mouseButton)
{
    sfVector2i click_pixel = {mouseButton.x, mouseButton.y};
    sfVector2f click_coords = sfRenderWindow_mapPixelToCoords
        (arena->params->window, click_pixel, NULL);
    sfFloatRect button_bounds;

    for (int i = 0; i < MAX_CHAMPS + 1; i++) {
        button_bounds = sfRectangleShape_getGlobalBounds
            (arena->params->buttons[i]->rect);
        if (!sfFloatRect_contains
            (&button_bounds, click_coords.x, click_coords.y))
            continue;
        if (i < 4) {
            handle_champion_button(arena->params, i);
        }
        if (i == 4) {
            handle_launch_button(arena);
        }
    }
}

static void init_button(game_params_t *params, int i, char *name, sfVector2f position)
{
    params->buttons[i] = malloc(sizeof(buttons_t));
    params->buttons[i]->id = i;
    params->buttons[i]->rect = sfRectangleShape_create();
    sfRectangleShape_setSize(params->buttons[i]->rect, (sfVector2f){350, 100});
    sfRectangleShape_setPosition(params->buttons[i]->rect, position);
    sfRectangleShape_setFillColor(params->buttons[i]->rect, sfBlue);
    params->buttons[i]->text = sfText_create();
    sfText_setFont(params->buttons[i]->text, params->font);
    sfText_setString(params->buttons[i]->text, name);
    sfText_setScale(params->buttons[i]->text, (sfVector2f){1.5, 1.5});
    sfText_setPosition(params->buttons[i]->text,
        (sfVector2f){position.x + 20, position.y + 20});
    sfText_setFillColor(params->buttons[i]->text, sfWhite);
    params->buttons[i]->file = NULL;
}

void create_buttons(game_params_t *params)
{
    char *names[MAX_CHAMPS + 1] =
        {"Champion 1", "Champion 2", "Champion 3", "Champion 4", "Core War"};
    sfVector2f positions[MAX_CHAMPS + 1] =
        {{250, 320}, {1250, 320}, {250, 750}, {1250, 750}, {750, 950}};

    params->buttons = malloc(sizeof(buttons_t *) * (MAX_CHAMPS + 1));
    if (!params->buttons) {
        dprintf(2, "Allocation error\n");
        return;
    }
    for (int i = 0; i < MAX_CHAMPS + 1; i++) {
        init_button(params, i, names[i], positions[i]);
    }
}
