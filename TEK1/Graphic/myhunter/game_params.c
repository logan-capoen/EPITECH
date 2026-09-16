/*
** EPITECH PROJECT, 2024
** game_params
** File description:
** all function to create game params
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"
#include "include/my.h"

void set_cursor(game_params_t game_params, char *pathfile)
{
    sfImage *cursor_image = sfImage_createFromFile(pathfile);
    sfVector2u size = sfImage_getSize(cursor_image);
    sfCursor *custom_cursor = sfCursor_createFromPixels(
        sfImage_getPixelsPtr(cursor_image), size, (sfVector2u){80, 80});

    sfRenderWindow_setMouseCursor(game_params.window, custom_cursor);
}

void set_score(game_params_t game_params, sfText *score)
{
    char buff[5];

    for (int i = 0; i < 5; i++)
        buff[i] = 0;
    if (game_params.score_game != 0)
        int_to_str(game_params.score_game, buff);
    else
        buff[0] = '0';
    sfText_setString(score, my_revstr(buff));
    sfRenderWindow_drawText(game_params.window, score, NULL);
}

void display_lifes(game_params_t game_params)
{
    for (int i = 0; i < 3; i++) {
        sfSprite_setTextureRect(game_params.life_sprite[i]->life,
            game_params.life_sprite[i]->rect);
        sfRenderWindow_drawSprite(game_params.window,
            game_params.life_sprite[i]->life, NULL);
    }
}
