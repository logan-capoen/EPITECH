/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main for my_hunter
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"
#include "include/printf.h"
#include <unistd.h>

static int display_flag_h(void)
{
    my_printf("Hello and welcome,\n");
    my_printf("I hope you enjoy playing my game!\n");
    my_printf("It's inspired by Duck Hunt with a Stardew Valley theme.\n");
    my_printf("The 'Skin' button lets you change the appearance ");
    my_printf("of your cursor,\n");
    my_printf("and the 'Mod' button allows you to modify sound effects.\n");
    my_printf("\n");
    my_printf("Have fun!\n");
    return 0;
}

int main(int argc, char **argv, char **env)
{
    int istty = 1;

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "DISPLAY", 7) == 0)
            istty = 0;
    }
    if (istty){
        write(2, "you're not in a graphical interface ;)", 39);
        return 84;
    }
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        display_flag_h();
    else
        handle_game();
    return 0;
}

game_params_t create_game_params(void)
{
    game_params_t game_params;
    sfEvent event;

    game_params.event = event;
    game_params.window = create_window();
    game_params.background = create_background("assets/images/background.png");
    game_params.bird = (bird_t *)NULL;
    game_params.bird_texture = set_texture_bird();
    game_params.clock_create_bird = create_clock();
    game_params.score_game = 0;
    game_params.font = sfFont_createFromFile("assets/fonts/font.ttf");
    game_params.life = 3;
    game_params.scene = 0;
    game_params.background_menu = create_background
        ("assets/images/background_menu.png");
    game_params.life_sprite = create_all_life();
    game_params.mod = 1;
    game_params.game_over = create_text(game_params,
        (sfVector2f){350, 250}, "GAME OVER", 300);
    return game_params;
}

static void destroy_game_params(game_params_t game_params)
{
    sfSprite_destroy(game_params.background);
    sfSprite_destroy(game_params.background_menu);
    sfClock_destroy(game_params.clock_create_bird.clock);
    sfRenderWindow_destroy(game_params.window);
}

int handle_game(void)
{
    game_params_t game_params = create_game_params();
    button_t buttons = create_struct_button();
    sfText *text_score = create_text(game_params,
        (sfVector2f){0, -40}, "score : ", 100);
    sfText *score = create_text(game_params, (sfVector2f){250, -30}, "0", 90);

    play_sound("assets/sounds/music.ogg", 1);
    while (sfRenderWindow_isOpen(game_params.window)) {
        while (sfRenderWindow_pollEvent(game_params.window,
            &game_params.event))
            analyse_events(&game_params, buttons);
        handle_scene_0(&game_params, buttons);
        handle_scene_1(&game_params, buttons, score, text_score);
        handle_scene_2(&game_params, buttons, game_params.game_over);
        handle_scene_3(&game_params, buttons);
        handle_scene_4(&game_params, buttons);
    }
    destroy_game_params(game_params);
    return 0;
}

void is_game_over(game_params_t *game_params)
{
    if (game_params->life == 0) {
        game_params->scene = 2;
        game_params->score_game = 0;
        game_params->life = 3;
        game_params->bird = NULL;
        for (int i = 0; i < 3; i++)
            game_params->life_sprite[i]->rect.left = 0;
        if (game_params->mod == 0)
            play_sound("assets/sounds/game_over.ogg", 0);
        else
            play_sound("assets/sounds/game_over01.ogg", 0);
    }
}

sfTexture **set_texture_bird(void)
{
    sfTexture **bird = malloc(sizeof(sfTexture *) * 5);
    sfTexture *bird_01 = sfTexture_createFromFile
        ("assets/images/bird_01.png", NULL);
    sfTexture *bird_02 = sfTexture_createFromFile
        ("assets/images/bird_02.png", NULL);
    sfTexture *bird_03 = sfTexture_createFromFile
        ("assets/images/bird_03.png", NULL);
    sfTexture *bird_04 = sfTexture_createFromFile
        ("assets/images/bird_04.png", NULL);
    sfTexture *bird_05 = sfTexture_createFromFile
        ("assets/images/bird_05.png", NULL);

    bird[0] = bird_01;
    bird[1] = bird_02;
    bird[2] = bird_03;
    bird[3] = bird_04;
    bird[4] = bird_05;
    return bird;
}
