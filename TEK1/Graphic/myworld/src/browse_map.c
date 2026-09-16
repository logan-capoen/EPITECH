/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** browse_map
*/

#include "myworld.h"

void load_top_left(game_params_t *game_params, vertex_t vertex)
{
    for (int i = 0; i < game_params->world.size - 1; i++) {
        for (int j = 0; j < game_params->world.size - 1; j++) {
            limit_bordure(i, j, game_params, &vertex);
        }
    }
}

void load_top_right(game_params_t *game_params, vertex_t vertex)
{
    for (int j = game_params->world.size - 2; j >= 0; j--) {
        for (int i = 0; i < game_params->world.size - 1; i++) {
            limit_bordure(i, j, game_params, &vertex);
        }
    }
}

void load_bottom_right(game_params_t *game_params, vertex_t vertex)
{
    for (int i = game_params->world.size - 2; i >= 0; i--) {
        for (int j = game_params->world.size - 2; j >= 0; j--) {
            limit_bordure(i, j, game_params, &vertex);
        }
    }
}

void load_bottom_left(game_params_t *game_params, vertex_t vertex)
{
    for (int j = 0; j < game_params->world.size - 1; j++) {
        for (int i = game_params->world.size - 2; i >= 0; i--) {
            limit_bordure(i, j, game_params, &vertex);
        }
    }
}
