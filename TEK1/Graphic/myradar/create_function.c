/*
** EPITECH PROJECT, 2024
** create function
** File description:
** function that create basic game parameters
*/

#include "include/my_radar.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"
#include "include/my.h"
#include <math.h>

sfSprite *create_background(char *pathfile)
{
    sfTexture *background_texture = sfTexture_createFromFile
        (pathfile, NULL);
    sfSprite *background_sprite = sfSprite_create();

    sfSprite_setTexture(background_sprite, background_texture, sfTrue);
    return background_sprite;
}

sfRenderWindow *create_window(void)
{
    sfRenderWindow *window;
    sfVideoMode video_mode = {1920, 1080, 32};

    window = sfRenderWindow_create(video_mode, "Myradar",
        sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 40);
    return window;
}

static sfCircleShape *create_hitbox(sfVector2f position, float radius)
{
    sfCircleShape *circle = sfCircleShape_create();

    position.x -= radius;
    position.y -= radius;
    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setPosition(circle, position);
    sfCircleShape_setOutlineThickness(circle, 3);
    sfCircleShape_setOutlineColor(circle, sfWhite);
    sfCircleShape_setFillColor(circle, sfTransparent);
    return circle;
}

void create_tower(char *info_tower, towers_t **towers, sfTexture *texture)
{
    towers_t *new = malloc(sizeof(towers_t));
    char **info = my_str_to_word_array(info_tower);
    sfSprite *tower = sfSprite_create();
    sfVector2f position = {my_getnbr(info[1]), my_getnbr(info[2])};
    sfVector2u texture_size = sfTexture_getSize(texture);

    if (!new)
        return;
    sfSprite_setTexture(tower, texture, sfTrue);
    sfSprite_scale(tower, (sfVector2f){0.2, 0.2});
    sfSprite_setOrigin(tower, (sfVector2f)
        {texture_size.x / 2.0f, texture_size.y / 2.0f});
    sfSprite_setPosition(tower, (sfVector2f)
        {my_getnbr(info[1]), my_getnbr(info[2])});
    new->hitbox = create_hitbox(position, my_getnbr(info[3]) * 9);
    new->tower = tower;
    new->radius = my_getnbr(info[3]) * 9;
    new->next = *towers;
    *towers = new;
    free(info);
}

static sfVector2f set_rotation(char **info, sfSprite **plane)
{
    sfVector2f vector = {my_getnbr(info[3]) - my_getnbr(info[1]),
        my_getnbr(info[4]) - my_getnbr(info[2])};
    float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
    float angle = atan2(vector.y, vector.x) * (180 / 3.1415926535897);

    sfSprite_setRotation(*plane, angle + 90.0);
    return (sfVector2f){vector.x / magnitude, vector.y / magnitude};
}

void create_plane(char *info_plane, planes_t **planes, sfTexture *texture)
{
    planes_t *new = malloc(sizeof(planes_t));
    char **info = my_str_to_word_array(info_plane);

    if (!new)
        return;
    new->plane = sfSprite_create();
    sfSprite_setTexture(new->plane, texture, sfTrue);
    sfSprite_scale(new->plane, (sfVector2f){0.039, 0.039});
    sfSprite_setPosition(new->plane, (sfVector2f)
        {my_getnbr(info[1]), my_getnbr(info[2])});
    sfSprite_setOrigin(new->plane, (sfVector2f){256, 256});
    new->direction = set_rotation(info, &(new->plane));
    new->position = (sfVector2f){my_getnbr(info[1]), my_getnbr(info[2])};
    new->destination = (sfVector2f){my_getnbr(info[3]), my_getnbr(info[4])};
    new->isVisible = 1;
    new->under_tower = 0;
    new->speed = my_getnbr(info[5]);
    new->next = *planes;
    *planes = new;
    free(info);
}
