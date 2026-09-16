/*
** EPITECH PROJECT, 2024
** create function
** File description:
** function that create basic game parameters
*/

#include "myworld.h"
#include <stdlib.h>
#include <stdio.h>
#include "printf.h"

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

    window = sfRenderWindow_create(video_mode, "MYWORLD",
        sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    return window;
}

sfText *create_text(game_params_t *game_params,
    sfVector2f position, char *str, int size)
{
    sfText *text = sfText_create();

    sfText_setString(text, str);
    sfText_setFont(text, game_params->font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, sfBlack);
    sfText_setPosition(text, position);
    return text;
}

sfSound *create_sound(char *pathfile)
{
    sfSoundBuffer *buffer = sfSoundBuffer_createFromFile(pathfile);
    sfSound *sound = sfSound_create();

    sfSound_setBuffer(sound, buffer);
    return sound;
}
