/*
** EPITECH PROJECT, 2024
** create function
** File description:
** function that create basic game parameters
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"

game_clock_t create_clock(void)
{
    sfClock *clock = sfClock_create();
    sfTime time;
    float seconds = 0.0;
    game_clock_t game_clock;

    game_clock.clock = clock;
    game_clock.time = time;
    game_clock.seconds = seconds;
    return game_clock;
}

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

    window = sfRenderWindow_create(video_mode, "Myhunter",
        sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    return window;
}

sfText *create_text(game_params_t game_params,
    sfVector2f position, char *str, int size)
{
    sfText *text = sfText_create();

    sfText_setString(text, str);
    sfText_setFont(text, game_params.font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, position);
    return text;
}

static life_t *create_life_sprite(sfVector2f position)
{
    sfTexture *life_texture = sfTexture_createFromFile
        ("assets/images/life_sprite.png", NULL);
    sfIntRect rect = {0, 0, 108, 108};
    sfSprite *life_sprite = sfSprite_create();
    life_t *life = malloc(sizeof(life_t));

    sfSprite_setTexture(life_sprite, life_texture, sfTrue);
    sfSprite_setPosition(life_sprite, position);
    life->life = life_sprite;
    life->rect = rect;
    return life;
}

life_t **create_all_life(void)
{
    life_t **lifes = malloc(sizeof(life_t *) * 3);
    int x = 1550;

    for (int i = 0; i < 3; i++) {
        lifes[i] = create_life_sprite((sfVector2f){x, 0});
        x += 120;
    }
    return lifes;
}
