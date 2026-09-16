/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** world
*/

#include "myworld.h"
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "printf.h"
#include <unistd.h>
#include <math.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <time.h>

sfVector2f project_iso_point(int x, int y, int z, game_params_t *game_params)
{
    sfVector3f point3d = {x, y, z};
    sfVector2f point2d = {0, 0};
    float angle = (game_params->world.rotation_horizontal / 180.0)
    * 3.14159265;
    float center_x = (game_params->world.size) * game_params->world.zoom;
    float center_y = (game_params->world.size) * game_params->world.zoom / 4.0;
    float rotated_x = 0;
    float rotated_y = 0;

    point3d.x -= center_x;
    point3d.y -= center_y;
    rotated_x = cos(angle) * point3d.x - sin(angle) * point3d.y;
    rotated_y = sin(angle) * point3d.x + cos(angle) * point3d.y;
    rotated_x += center_x;
    rotated_y += center_y;
    point2d.x = rotated_x - rotated_y;
    point2d.y = (rotated_x + rotated_y) / 2 - point3d.z;
    return point2d;
}

int **create_3d_map(int size)
{
    int **map = malloc(sizeof(int *) * size);

    if (map == NULL)
        return NULL;
    for (int i = 0; i < size; i++) {
        map[i] = malloc(sizeof(int) * size);
        if (map[i] == NULL)
            return NULL;
    }
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            map[i][j] = 0;
    return map;
}

sfVector2f **create_2d_map(int **map3d, game_params_t *game_params)
{
    sfVector2f **map2d =
        malloc(sizeof(sfVector2f *) * game_params->world.size);
    int scale = 200 - game_params->world.size;

    if (map2d == NULL)
        return NULL;
    for (int i = 0; i < game_params->world.size; i++) {
        map2d[i] = malloc(sizeof(sfVector2f) * game_params->world.size);
        if (map2d[i] == NULL)
            return NULL;
    }
    for (int i = 0; i < game_params->world.size; i++)
        for (int j = 0; j < game_params->world.size; j++)
            map2d[i][j] = project_iso_point(i * game_params->world.zoom +
                game_params->world.offset_x, j * game_params->world.zoom +
                game_params->world.offset_y, map3d[i][j] * 5, game_params);
    return map2d;
}

static sfVertexArray *create_textured_square(sfVector2f **points,
    sfTexture *ground)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVector2u tex_size = sfTexture_getSize(ground);
    sfVertex vertex1 = {.position = *points[0],
        .color = sfWhite, .texCoords = {0, 0}};
    sfVertex vertex2 = {.position = *points[1],
        .color = sfWhite, .texCoords = {tex_size.x, 0}};
    sfVertex vertex3 = {.position = *points[2],
        .color = sfWhite, .texCoords = {tex_size.x, tex_size.y}};
    sfVertex vertex4 = {.position = *points[3],
        .color = sfWhite, .texCoords = {0, tex_size.y}};

    sfVertexArray_setPrimitiveType(vertex_array, sfQuads);
    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_append(vertex_array, vertex3);
    sfVertexArray_append(vertex_array, vertex4);
    return vertex_array;
}

static int tex_from_alt(game_params_t *game_params, int i, int j)
{
    int **map = game_params->world.map;
    int z_average = (map[i][j] + map[i + 1][j]
        + map[i + 1][j + 1] + map[i][j + 1]) / 4;

    if (z_average < -70)
        return 6;
    if (z_average < -40)
        return 5;
    if (z_average < -15)
        return 1;
    if (z_average < 0)
        return 0;
    if (z_average < 10)
        return 2;
    if (z_average < 70)
        return 4;
    return 3;
}

void limit_bordure(int i, int j,
    game_params_t *game_params, vertex_t *vertex)
{
        if (i < game_params->world.size - 1) {
            vertex->points[0] = &(vertex->map2d[i][j]);
            vertex->points[1] = &(vertex->map2d[i][j + 1]);
            vertex->points[2] = &(vertex->map2d[i + 1][j + 1]);
            vertex->points[3] = &(vertex->map2d[i + 1][j]);
            vertex->state = (sfRenderStates){sfBlendAlpha,
                sfTransform_Identity,
                game_params->textures[tex_from_alt(game_params, i, j)], NULL};
            vertex->square = create_textured_square
                (vertex->points, game_params->textures[0]);
            sfRenderWindow_drawVertexArray
                (game_params->window, vertex->square, &(vertex->state));
            sfVertexArray_destroy(vertex->square);
        }
}

void display_world(game_params_t *game_params)
{
    sfVector2f **points = malloc(sizeof(sfVector2f *) * 5);
    sfVertexArray *square = NULL;
    sfVector2f **map2d = create_2d_map(game_params->world.map, game_params);
    vertex_t vertex = {{sfBlendAlpha, sfTransform_Identity,
        game_params->textures[0], NULL}, points, NULL, map2d};
    int angle = game_params->world.rotation_horizontal;

    if (points == NULL)
        return;
    if (angle >= 0 && angle < 90)
        load_top_left(game_params, vertex);
    if (angle >= 90 && angle < 180)
        load_top_right(game_params, vertex);
    if (angle >= 180 && angle < 270)
        load_bottom_right(game_params, vertex);
    if (angle >= 270 && angle <= 360)
        load_bottom_left(game_params, vertex);
    destroy_map(map2d, game_params->world.size);
}
