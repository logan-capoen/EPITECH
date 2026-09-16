/*
** EPITECH PROJECT, 2024
** handle_buttons.c
** File description:
** handling for buttons
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/printf.h"
#include "include/my.h"

button_t create_struct_button_two(button_t buttons)
{
    buttons.button_back = create_button
        ("assets/images/button_back.png", (sfVector2f){1550, 800});
    buttons.button_skin_mouse = create_button
        ("assets/images/button_skin_mouse.png", (sfVector2f){1050, 800});
    buttons.button_srx = create_button
        ("assets/images/button_srx.png", (sfVector2f){250, 800});
    buttons.button_fun = create_button
        ("assets/images/button_fun.png", (sfVector2f){950, 800});
    return buttons;
}

button_t create_struct_button(void)
{
    button_t buttons;

    buttons.button_go_menu = create_button
        ("assets/images/button_menu.png", (sfVector2f){450, 700});
    buttons.button_go_restart = create_button
        ("assets/images/button_restart.png", (sfVector2f){1050, 700});
    buttons.button_play = create_button
        ("assets/images/button_play.png", (sfVector2f){50, 800});
    buttons.button_skin = create_button
        ("assets/images/button_skin.png", (sfVector2f){550, 800});
    buttons.button_mod = create_button
        ("assets/images/button_mod.png", (sfVector2f){1050, 800});
    buttons.button_quit = create_button
        ("assets/images/button_quit.png", (sfVector2f){1550, 800});
    buttons.button_skin_crosshair = create_button
        ("assets/images/button_skin_crosshair.png", (sfVector2f){50, 800});
    buttons.button_skin_landing_net = create_button
        ("assets/images/button_skin_landing_net.png", (sfVector2f){550, 800});
    return create_struct_button_two(buttons);
}

sfSprite *create_button(char *pathfile, sfVector2f position)
{
    sfTexture *button_texture = sfTexture_createFromFile(pathfile, NULL);
    sfSprite *button_sprite = sfSprite_create();

    sfSprite_setTexture(button_sprite, button_texture, sfTrue);
    sfSprite_setPosition(button_sprite, position);
    sfSprite_setScale(button_sprite, (sfVector2f){1.5, 1.5});
    return button_sprite;
}
