/*
** EPITECH PROJECT, 2025
** detection.c
** File description:
** detecion
*/

#include "include/my_radar.h"
#include <sys/types.h>
#include <math.h>
#include "include/printf.h"

static int is_collision(planes_t *plane1, planes_t *plane2)
{
    if (plane1->position.x + 20 > plane2->position.x &&
        plane1->position.x < plane2->position.x + 20 &&
        plane1->position.y + 20 > plane2->position.y &&
        plane1->position.y < plane2->position.y + 20) {
        return 1;
    }
    return 0;
}

static void cond_check_collision(planes_t *tmp1, planes_t *tmp2)
{
    if (!(tmp1->under_tower || tmp2->under_tower)
        && is_collision(tmp1, tmp2)) {
        tmp1->isVisible = 0;
        tmp2->isVisible = 0;
    }
}

void check_all_collisions(planes_t **planes)
{
    planes_t *tmp1 = *planes;
    planes_t *tmp2 = NULL;

    while (tmp1 != NULL) {
        tmp2 = tmp1->next;
        while (tmp2 != NULL) {
            cond_check_collision(tmp1, tmp2);
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
    }
    delete_plane(planes);
}

static int check_tower(towers_t *tmp_towers, planes_t *tmp_planes)
{
    sfVector2f center = {0, 0};
    float dx = 0;
    float dy = 0;

    center = sfCircleShape_getPosition(tmp_towers->hitbox);
    dx = center.x + tmp_towers->radius - tmp_planes->position.x;
    dy = center.y + tmp_towers->radius - tmp_planes->position.y;
    if ((dx * dx + dy * dy) <= (tmp_towers->radius * tmp_towers->radius)) {
        tmp_planes->under_tower = 1;
    }
}

int is_under_tower(towers_t **towers, planes_t **planes)
{
    towers_t *tmp_towers = *towers;
    planes_t *tmp_planes = *planes;

    while (tmp_planes != NULL) {
        tmp_planes->under_tower = 0;
        tmp_planes = tmp_planes->next;
    }
    tmp_planes = *planes;
    while (tmp_planes != NULL) {
        tmp_towers = *towers;
        while (tmp_towers != NULL) {
            check_tower(tmp_towers, tmp_planes);
            tmp_towers = tmp_towers->next;
        }
        tmp_planes = tmp_planes->next;
    }
    return 0;
}
