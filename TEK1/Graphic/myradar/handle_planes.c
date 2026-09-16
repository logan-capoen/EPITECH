/*
** EPITECH PROJECT, 2025
** handle_planes.c
** File description:
** handle_planes
*/

#include "include/my_radar.h"
#include <sys/types.h>
#include <math.h>
#include "include/printf.h"
#include "include/my.h"

static void cond_delete_plane(planes_t *tmp, planes_t *prev, planes_t **planes)
{
    if (prev == NULL) {
        *planes = tmp->next;
    } else {
        prev->next = tmp->next;
    }
}

void delete_plane(planes_t **planes)
{
    planes_t *tmp = *planes;
    planes_t *prev = NULL;
    planes_t *to_free = NULL;

    while (tmp != NULL) {
        if (tmp->isVisible != 1) {
            cond_delete_plane(tmp, prev, planes);
            sfSprite_destroy(tmp->plane);
            to_free = tmp;
            tmp = tmp->next;
            free(to_free);
        } else {
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

int display_towers_and_planes(towers_t **towers,
    planes_t **planes, sfRenderWindow *window)
{
    towers_t *tmp_towers = *towers;
    planes_t *tmp_planes = *planes;

    while (tmp_towers != NULL) {
            sfRenderWindow_drawSprite(window, tmp_towers->tower, NULL);
            sfRenderWindow_drawCircleShape(window, tmp_towers->hitbox, NULL);
            tmp_towers = tmp_towers->next;
    }
    while (tmp_planes != NULL) {
            sfRenderWindow_drawSprite(window, tmp_planes->plane, NULL);
            tmp_planes = tmp_planes->next;
    }
    return 0;
}

void update_airplanes(planes_t **planes)
{
    planes_t *tmp = *planes;

    while (tmp) {
        tmp->position.x += tmp->direction.x * (tmp->speed / 60);
        tmp->position.y += tmp->direction.y * (tmp->speed / 60);
        sfSprite_setPosition(tmp->plane, tmp->position);
        if (fabs(tmp->position.x - tmp->destination.x) < 5 &&
            fabs(tmp->position.y - tmp->destination.y) < 5) {
            tmp->isVisible = 0;
            delete_plane(planes);
        }
        tmp = tmp->next;
    }
}

static int handle_error(char *line)
{
    char **info = my_str_to_word_array(line);
    int len = 0;

    for (; info[len] != NULL; len++);
    if (info[0][0] == 'A')
        if (len != 7 || my_getnbr(info[1]) < 0 ||
            my_getnbr(info[2]) < 0 || my_getnbr(info[3]) < 0 ||
            my_getnbr(info[4]) < 0 || my_getnbr(info[5]) < 0 ||
            my_getnbr(info[6]) < 0)
            return 84;
    if (info[0][0] == 'T')
        if (len != 4 || my_getnbr(info[1]) < 0 ||
            my_getnbr(info[2]) < 0 || my_getnbr(info[3]) < 0)
            return 84;
    if (info[0][0] != 'A' && info[0][0] != 'T')
        return 84;
    return 0;
}

int add_towers_and_planes(towers_t **towers,
    planes_t **planes, char *pathfile)
{
    FILE *file = fopen(pathfile, "r");
    char *line = NULL;
    size_t len = 0;
    sfTexture *tower_texture =
        sfTexture_createFromFile("asset/tower.png", NULL);
    sfTexture *plane_texture =
        sfTexture_createFromFile("asset/plane.png", NULL);
    ssize_t read = getline(&line, &len, file);

    while (read != -1) {
        if (handle_error(line) == 84)
            return 84;
        if (line[0] == 'T')
            create_tower(line, towers, tower_texture);
        if (line[0] == 'A')
            create_plane(line, planes, plane_texture);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
}

static void cond_delete_towers(towers_t *tmp,
    towers_t *prev, towers_t **towers)
{
    if (prev == NULL) {
        *towers = tmp->next;
    } else {
        prev->next = tmp->next;
    }
}

void delete_towers(towers_t **towers)
{
    towers_t *tmp = *towers;
    towers_t *prev = NULL;
    towers_t *to_free = NULL;

    while (tmp != NULL) {
        if (tmp->radius == -1) {
            cond_delete_towers(tmp, prev, towers);
            sfSprite_destroy(tmp->tower);
            to_free = tmp;
            tmp = tmp->next;
            free(to_free);
        } else {
            prev = tmp;
            tmp = tmp->next;
        }
    }
}
