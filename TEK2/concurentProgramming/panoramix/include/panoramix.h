/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** panoramix
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_

    #include <pthread.h>
    #include <semaphore.h>
    #include <stdio.h>
    #include <stdlib.h>

    #define ERROR_STATUS 84

typedef struct village_s {
    int nb_villagers;
    int pot_size;
    int servings_left;
    int nb_fights;
    int nb_refills;
    pthread_mutex_t lock_pot;
    sem_t sem_druid;
    sem_t sem_villagers;
} village_t;

typedef struct villager_s {
    int id;
    village_t *village;
    pthread_t thread;
} villager_t;

void *druid_thread(void *arg);
void *villager_thread(void *arg);
void init_village(village_t *v, char **av);
void cleanup_village(village_t *v, villager_t *villagers);

#endif
