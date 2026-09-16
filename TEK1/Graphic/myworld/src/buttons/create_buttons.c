/*
** EPITECH PROJECT, 2024
** create_buttons.c
** File description:
** handling for buttons
*/

#include "myworld.h"
#include <stdlib.h>
#include <stdio.h>
#include "printf.h"
#include "my.h"
#include "buttons.h"

sfSprite *create_button(char *pathfile, sfVector2f position, sfVector2f size)
{
    sfTexture *button_texture = sfTexture_createFromFile(pathfile, NULL);
    sfSprite *button_sprite = sfSprite_create();

    sfSprite_setTexture(button_sprite, button_texture, sfTrue);
    sfSprite_setPosition(button_sprite, position);
    sfSprite_setScale(button_sprite, size);
    return button_sprite;
}

static void init_button(button_t *button, button_params_t params, sfFont *font)
{
    button->button = create_button(params.image_path, params.position,
        params.size);
    button->button_texture = sfTexture_createFromFile(params.image_path, NULL);
    button->button_texture_hover =
        sfTexture_createFromFile(params.hover_image_path, NULL);
    button->help = sfText_create();
    button->scene = params.scene;
    sfText_setString(button->help, params.help_message);
    sfText_setFont(button->help, font);
    sfText_setCharacterSize(button->help, 35);
    sfText_setColor(button->help, sfWhite);
}

button_t *create_struct_button(void)
{
    button_t *buttons = malloc(sizeof(button_t) * 8);
    sfFont *font = sfFont_createFromFile("assets/fonts/font.ttf");

    if (buttons == NULL)
        return NULL;
    for (int i = 0; i < 8; i++)
        init_button(&buttons[i], params[i], font);
    return buttons;
}
