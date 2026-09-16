/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** create_function
*/

#include "../../include_csfml/op.h"

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

    window = sfRenderWindow_create(video_mode, "COREWAR",
        sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    return window;
}

sfText *create_text(game_params_t *game_params, char *str,
    int size, sfColor color)
{
    sfText *text = sfText_create();

    sfText_setString(text, str);
    sfText_setFont(text, game_params->font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, color);
    return text;
}

sfRectangleShape *create_pc_display(game_params_t *params, sfColor color)
{
    sfRectangleShape *pc_display = sfRectangleShape_create();

    sfRectangleShape_setSize(pc_display, (sfVector2f){15, 15});
    sfRectangleShape_setFillColor(pc_display, color);
    return pc_display;
}

void play_music(void)
{
    sfMusic *music = sfMusic_createFromFile("assets/sound.mp3");

    if (!music)
        return;
    sfMusic_setLoop(music, sfTrue);

    sfMusic_play(music);
}
