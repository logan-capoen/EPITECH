/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** terraform
*/

#include "myworld.h"

static sfVector2f get_dist(game_params_t *game_params,
    int **indexes, float *min_distance, sfVector2f **d2_map)
{
    float dist = 0;
    int center_x = 0;
    int center_y = 0;
    sfVector2f position = sfRenderWindow_mapPixelToCoords
        (game_params->window, sfMouse_getPositionRenderWindow
        (game_params->window), game_params->world.camera);
    int i = *(indexes[2]);

    for (int j = 0; j < game_params->world.size - 1; j++) {
        center_x = (d2_map[i][j].x + d2_map[i + 1][j].x) / 2;
        center_y = (d2_map[i][j].y + d2_map[i][j + 1].y) / 2;
        dist = sqrtf(powf(position.x - center_x, 2) +
            powf(position.y - center_y, 2));
        if (*min_distance == -1 || dist < *min_distance) {
            *min_distance = dist;
            *(indexes[0]) = i;
            *(indexes[1]) = j;
        }
    }
    return position;
}

void terraform_map(game_params_t *game_params, int nx, int ny, float distance)
{
    float factor = 0.0;

    if (nx >= 0 && nx < game_params->world.size && ny >= 0 &&
        ny < game_params->world.size) {
        if (distance <= game_params->world.radius &&
            game_params->world.brush != 0) {
            factor = 1.0f - (distance / game_params->world.radius);
            game_params->world.map[nx][ny] += factor *
                (5 * game_params->world.brush);
        }
        if (distance <= game_params->world.radius &&
            game_params->world.brush == 0) {
            factor = 1.0f - (distance / game_params->world.radius);
            game_params->world.map[nx][ny] = 0;
        }
    }
}

void browse_map(game_params_t *game_params, int x, int y)
{
    int radius = game_params->world.radius;

    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            terraform_map(game_params, x + i, y + j, sqrtf(i * i + j * j));
        }
    }
}

static void play_map_sounds(game_params_t *game_params)
{
    if (game_params->world.brush == 1)
        sfSound_play(game_params->world.up);
    if (game_params->world.brush == -1)
        sfSound_play(game_params->world.down);
}

void click_on_map(game_params_t *game_params)
{
    sfVector2f position;
    sfVector2f **d2_map = create_2d_map(game_params->world.map, game_params);
    int x = -1;
    int y = -1;
    float min_distance = -1;
    int **indexes = malloc(sizeof(int *) * 3);

    if (indexes == NULL)
        return;
    play_map_sounds(game_params);
    for (int i = 0; i < game_params->world.size - 1; i++) {
        indexes[0] = &x;
        indexes[1] = &y;
        indexes[2] = &i;
        position = get_dist(game_params, indexes, &min_distance, d2_map);
    }
    if (x >= 0 && x < game_params->world.size && y
        >= 0 && y < game_params->world.size)
        browse_map(game_params, x, y);
}
