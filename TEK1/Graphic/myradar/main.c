/*
** EPITECH PROJECT, 2025
** main
** File description:
** main for my_radar
*/

#include "include/my_radar.h"
#include <sys/types.h>
#include <math.h>
#include "include/printf.h"
#include <sys/stat.h>
#include <dirent.h>
#include "my.h"

static int handle_event(sfEvent event, sfRenderWindow *window)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if ((event.type == sfEvtClosed) || (event.type == sfEvtKeyPressed
            && event.key.code == sfKeyEscape)) {
            sfRenderWindow_close(window);
            return 0;
        }
    }
    return 0;
}

static int handle_stop(planes_t *planes, towers_t **towers)
{
    towers_t *tmp = *towers;

    if (planes == NULL) {
        while (tmp != NULL) {
            tmp->radius = -1;
            tmp = tmp->next;
        }
        delete_towers(towers);
        return 1;
    }
    return 0;
}

static void delete_left_planes(planes_t **planes)
{
    planes_t *tmp = *planes;

    while (tmp != NULL) {
        tmp->isVisible = 0;
        tmp = tmp->next;
    }
    delete_plane(planes);
}

static int window(towers_t **towers, planes_t **planes)
{
    sfSprite *background = create_background("asset/map.jpg");
    sfRenderWindow *window = create_window();
    sfEvent event;

    while (sfRenderWindow_isOpen(window)) {
        handle_event(event, window);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, background, NULL);
        update_airplanes(planes);
        is_under_tower(towers, planes);
        check_all_collisions(planes);
        display_towers_and_planes(towers, planes, window);
        sfRenderWindow_display(window);
        if (handle_stop(*planes, towers))
            break;
    }
    if (*planes != NULL)
        delete_left_planes(planes);
    delete_towers(towers);
    sfRenderWindow_destroy(window);
}

static int handle_error(char *file_path)
{
    struct stat sf;

    if ((stat(file_path, &sf) != 0) || (!S_ISREG(sf.st_mode))) {
        my_printf("wrong pathfile");
        return 84;
    }
    return 0;
}

static void display_info(void)
{
    my_printf("The My Radar project simulates collisions "
    "between planes.\nPlanes move based on their defined "
    "speed and direction\nbut cannot collide when protected"
    " by a control tower within a defined radius.\nThe program is "
    "executed with the command ./my_radar file.txt,\n"
    "where the file contains the "
    "coordinates and characteristics of towers and planes.");
}

static int istty(char **env)
{
    int istty = 1;

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strcmp(env[i], "DISPLAY=:0") == 0 || my_strcmp(env[i], "DISPLAY=:1") == 0)
            istty = 0;
    }
    if (istty){
        my_printf("you're not in a graphical interface ;)");
        return 84;
    }
    return 0;
}

int main(int argc, char **argv, char **env)
{
    towers_t *towers = NULL;
    planes_t *planes = NULL;

    if (argc == 2 && my_strcmp("-h", argv[1]) == 0) {
        display_info();
        return 0;
    }
    if (argc != 2 || handle_error(argv[1]) == 84 || istty(env) == 84)
        return 84;
    if (add_towers_and_planes(&towers, &planes, argv[1]) == 84) {
        my_printf("wrong script");
        return 84;
    }
    window(&towers, &planes);
    return 0;
}
