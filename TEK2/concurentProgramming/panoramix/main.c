/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** main
*/

#include "panoramix.h"

static int check_args(int argc, char **argv)
{
    if (argc != 5) {
        fprintf(stderr, "USAGE: ./panoramix <nb_villagers> <pot_size> "
            "<nb_fights> <nb_refills>\n");
        return ERROR_STATUS;
    }
    for (int i = 1; i < 5; i++) {
        if (atoi(argv[i]) <= 0) {
            fprintf(stderr, "Values must be > 0.\n");
            return ERROR_STATUS;
        }
    }
    return 0;
}

void cleanup_village(village_t *v, villager_t *villagers)
{
    pthread_mutex_destroy(&v->lock_pot);
    sem_destroy(&v->sem_druid);
    sem_destroy(&v->sem_villagers);
    free(villagers);
}

int main(int argc, char **argv)
{
    village_t village;
    pthread_t druid;
    villager_t *villagers;

    if (check_args(argc, argv) == ERROR_STATUS)
        return ERROR_STATUS;
    init_village(&village, argv);
    villagers = malloc(sizeof(villager_t) * village.nb_villagers);
    pthread_create(&druid, NULL, druid_thread, &village);
    for (int i = 0; i < village.nb_villagers; i++) {
        villagers[i].id = i;
        villagers[i].village = &village;
        pthread_create(&villagers[i].thread, NULL, villager_thread,
            &villagers[i]);
    }
    for (int i = 0; i < village.nb_villagers; i++)
        pthread_join(villagers[i].thread, NULL);
    cleanup_village(&village, villagers);
    return 0;
}
