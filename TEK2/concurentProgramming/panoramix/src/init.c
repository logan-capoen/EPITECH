/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** init
*/

#include "panoramix.h"

void init_village(village_t *v, char **av)
{
    v->nb_villagers = atoi(av[1]);
    v->pot_size = atoi(av[2]);
    v->servings_left = v->pot_size;
    v->nb_fights = atoi(av[3]);
    v->nb_refills = atoi(av[4]);
    pthread_mutex_init(&v->lock_pot, NULL);
    sem_init(&v->sem_druid, 0, 0);
    sem_init(&v->sem_villagers, 0, 0);
}
