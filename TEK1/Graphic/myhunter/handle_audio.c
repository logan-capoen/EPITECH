/*
** EPITECH PROJECT, 2024
** handle_audio.c
** File description:
** handle the audio in the game
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"
#include "include/my.h"

void play_sound(char *pathfile, int loop)
{
    sfMusic *sound;

    sound = sfMusic_createFromFile(pathfile);
    if (loop)
        sfMusic_setLoop(sound, sfTrue);
    sfMusic_play(sound);
}

void sound_shoot_mod1(void)
{
    int random = rand() % 3;

    switch (random) {
        case 0:
            play_sound("assets/sounds/shoot.ogg", 0);
            break;
        case 1:
            play_sound("assets/sounds/shoot01.ogg", 0);
            break;
        case 2:
            play_sound("assets/sounds/shoot02.ogg", 0);
    }
}

void play_sound_hurt(game_params_t game_params)
{
    if (game_params.mod == 0)
        play_sound("assets/sounds/hurt.ogg", 0);
    else
        play_sound("assets/sounds/hurt01.ogg", 0);
}
