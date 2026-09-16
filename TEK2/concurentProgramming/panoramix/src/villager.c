/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** villager
*/

#include "panoramix.h"

static int villager_drink(villager_t *villager)
{
    pthread_mutex_lock(&villager->village->lock_pot);
    printf("Villager %i: I need a drink... I see %i servings left.\n",
        villager->id, villager->village->servings_left);
    if (villager->village->servings_left <= 0) {
        if (villager->village->nb_refills <= 0) {
            pthread_mutex_unlock(&villager->village->lock_pot);
            return 0;
        }
        printf("Villager %i: Hey Pano wake up! We need "
            "more potion.\n", villager->id);
        sem_post(&villager->village->sem_druid);
        sem_wait(&villager->village->sem_villagers);
        if (villager->village->servings_left <= 0) {
            pthread_mutex_unlock(&villager->village->lock_pot);
            return 2;
        }
    }
    villager->village->servings_left--;
    pthread_mutex_unlock(&villager->village->lock_pot);
    return 1;
}

void *villager_thread(void *arg)
{
    villager_t *villager = (villager_t *)arg;
    int fights_done = 0;
    int thirst_quenched;

    printf("Villager %i: Going into battle!\n", villager->id);
    while (fights_done < villager->village->nb_fights) {
        thirst_quenched = villager_drink(villager);
        if (thirst_quenched == 0)
            break;
        if (thirst_quenched == 2)
            continue;
        fights_done++;
        printf("Villager %i: Take that roman scum! Only %i left.\n",
            villager->id, villager->village->nb_fights - fights_done);
    }
    printf("Villager %i: I'm going to sleep now.\n", villager->id);
    return NULL;
}
