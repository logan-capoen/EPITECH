/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** druid
*/

#include "panoramix.h"

static void druid_refill(village_t *village)
{
    village->nb_refills -= 1;
    printf("Druid: Ah! Yes, yes, I'm awake! Working on it! ");
    printf("Beware I can only make %i more refills after this one.\n",
        village->nb_refills);
    village->servings_left = village->pot_size;
    for (int i = 0; i < village->nb_villagers; i++)
        sem_post(&village->sem_villagers);
}

void *druid_thread(void *arg)
{
    village_t *village = (village_t *)arg;

    printf("Druid: I'm ready... but sleepy...\n");
    while (village->nb_refills > 0) {
        sem_wait(&village->sem_druid);
        druid_refill(village);
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    for (int i = 0; i < village->nb_villagers; i++)
        sem_post(&village->sem_villagers);
    return NULL;
}
