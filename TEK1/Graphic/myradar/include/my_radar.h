/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** my_radar
*/

#ifndef MY_RADAR_H_
    #define MY_RADAR_H_
    #include <SFML/Graphics/RenderWindow.h>
    #include <stdlib.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdio.h>

typedef struct game_clock {
    sfClock *clock;
    sfTime time;
    float seconds;
}game_clock_t;

typedef struct planes {
    sfSprite *plane;
    sfVector2f position;
    sfVector2f destination;
    sfVector2f direction;
    int isVisible;
    int under_tower;
    float speed;
    struct planes *next;
}planes_t;

typedef struct towers {
    sfSprite *tower;
    sfCircleShape *hitbox;
    int radius;
    struct towers *next;
}towers_t;

sfSprite *create_background(char *pathfile);
sfRenderWindow *create_window(void);
void create_tower(char *info_tower, towers_t **towers, sfTexture *texture);
void create_plane(char *info_plane, planes_t **planes, sfTexture *texture);
void delete_plane(planes_t **planes);
void check_all_collisions(planes_t **planes);
int is_under_tower(towers_t **towers, planes_t **planes);
int display_towers_and_planes(towers_t **towers,
    planes_t **planes, sfRenderWindow *window);
void update_airplanes(planes_t **planes);
int add_towers_and_planes(towers_t **towers,
    planes_t **planes, char *pathfile);
void delete_towers(towers_t **towers);
#endif
