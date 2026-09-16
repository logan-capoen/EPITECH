/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** utilities
*/

#include "myworld.h"
#include <stdlib.h>
#include <stdio.h>
#include "printf.h"
#include "my.h"

void play_music(char *pathfile, int loop)
{
    sfMusic *sound;

    sound = sfMusic_createFromFile(pathfile);
    if (loop)
        sfMusic_setLoop(sound, sfTrue);
    sfMusic_play(sound);
}

void set_cursor(game_params_t game_params, char *pathfile)
{
    sfImage *cursor_image = sfImage_createFromFile(pathfile);
    sfVector2u size = sfImage_getSize(cursor_image);
    sfCursor *custom_cursor = sfCursor_createFromPixels(
        sfImage_getPixelsPtr(cursor_image), size, (sfVector2u){80, 80});

    sfRenderWindow_setMouseCursor(game_params.window, custom_cursor);
}

unsigned int revbytes(unsigned int num)
{
    unsigned int b0;
    unsigned int b1;
    unsigned int b2;
    unsigned int b3;

    b0 = (num & 0x000000FF) << 24;
    b1 = (num & 0x0000FF00) << 8;
    b2 = (num & 0x00FF0000) >> 8;
    b3 = (num & 0xFF000000) >> 24;
    return b0 | b1 | b2 | b3;
}

void reset_map(game_params_t *game_params)
{
    for (int i = 0; i < game_params->world.size; i++) {
        for (int j = 0; j < game_params->world.size; j++) {
            game_params->world.map[i][j] = 0;
        }
    }
}
