/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main for my_hunter
*/

#include "myworld.h"
#include "assets.h"

static int display_flag_h(void)
{
    printf("Hello and welcome,\n");
    printf("We hope you enjoy our world creator software !\n");
    printf("To know how to use it, you can hover each "
        "button to get its goal.\n");
    printf("For the keyboard controls, you have :\n"
        "\tU ==> To set tye brush effect on 'up'\n"
        "\tI ==> To set the brush effect on 'down'\n"
        "\tB ==> To set the brush effect on 'reset'\n"
        "\tR ==> To reset the whole map\n"
        "\t+ ==> To set a larger brush zone\n"
        "\t- ==> To set a smaller brush zone\n");
    printf("Have fun, and don't hesitate to save your map !\n");
    return 0;
}

static int check_assets(void)
{
    for (int i = 0; i < 31; i++) {
        if (access(assets_paths[i], F_OK) != 0)
            return 0;
    }
    return 1;
}

int main(int argc, char **argv, char **env)
{
    int istty = 1;

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strcmp(env[i], "DISPLAY=:0") == 0 ||
        my_strcmp(env[i], "DISPLAY=:1") == 0)
            istty = 0;
    }
    if (istty){
        write(2, "You're not in a graphical interface ;)\n", 40);
        return 84;
    }
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        display_flag_h();
    else if (check_assets())
        return handle_game();
    return 84;
}

world_t create_world(game_params_t *game_params)
{
    world_t world;

    world.map = NULL;
    world.size = 30;
    world.zoom = 1.0 / (world.size) * 850;
    world.offset_x = game_params->window_size.x / 2.25 -
        (world.size * world.zoom) / 2.0;
    world.offset_y = game_params->window_size.y / 5.0 -
        (world.size * world.zoom) / 1.5;
    world.rotation_horizontal = 60.0;
    world.rotation_vertical = 20.0;
    world.camera = sfView_createFromRect((sfFloatRect){0, 0, 1920, 1080});
    sfRenderWindow_setView(game_params->window, world.camera);
    world.brush = 0;
    world.background = create_background("assets/images/background_world.jpg");
    world.radius = 15;
    world.down = create_sound("assets/sounds/down_sound.ogg");
    world.up = create_sound("assets/sounds/up_sound.ogg");
    return world;
}

static sfTexture **create_all_texture(void)
{
    sfTexture **textures = malloc(sizeof(sfTexture *) * 7);

    if (textures == NULL)
        return NULL;
    textures[0] = sfTexture_createFromFile
        ("assets/images/texture_dirt.jpg", NULL);
    textures[1] = sfTexture_createFromFile
        ("assets/images/texture_water.jpg", NULL);
    textures[2] = sfTexture_createFromFile
        ("assets/images/texture_grass.jpg", NULL);
    textures[3] = sfTexture_createFromFile
        ("assets/images/texture_snow.jpg", NULL);
    textures[4] = sfTexture_createFromFile
        ("assets/images/texture_stone.png", NULL);
    textures[5] = sfTexture_createFromFile
        ("assets/images/texture_obsi.png", NULL);
    textures[6] = sfTexture_createFromFile
        ("assets/images/texture_lava.jpg", NULL);
    return textures;
}

game_params_t create_game_params(void)
{
    game_params_t game_params;
    sfEvent event;

    game_params.event = event;
    game_params.window = create_window();
    game_params.background = create_background
        ("assets/images/background_menu.png");
    game_params.font = sfFont_createFromFile("assets/fonts/font.ttf");
    game_params.scene = 0;
    game_params.background_menu = create_background
        ("assets/images/background_menu.png");
    game_params.window_size = sfRenderWindow_getSize(game_params.window);
    game_params.ui = sfView_createFromRect((sfFloatRect){0, 0, 1920, 1080});
    game_params.textures = create_all_texture();
    game_params.font = sfFont_createFromFile("assets/fonts/font01.ttf");
    game_params.menu_size = create_background("assets/images/menu_size.png");
    game_params.clock = create_clock();
    return game_params;
}

int display_help(button_t *button, game_params_t *game_params)
{
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(game_params->window,
        sfMouse_getPositionRenderWindow(game_params->window), game_params->ui);
    sfFloatRect button_rect;

    for (int i = 0; i < 8; i++) {
        button_rect = sfSprite_getGlobalBounds(button[i].button);
        if (sfFloatRect_contains(&button_rect, mouse_pos.x, mouse_pos.y) &&
            game_params->scene == button[i].scene) {
            sfText_setPosition(button[i].help,
                (sfVector2f){button_rect.left, button_rect.top - 40});
            sfRenderWindow_drawText(game_params->window, button[i].help, NULL);
            return 1;
        }
    }
    return 0;
}

int handle_game(void)
{
    game_params_t game_params = create_game_params();
    button_t *buttons = create_struct_button();
    sfMusic *music = sfMusic_createFromFile("assets/sounds/music.ogg");

    sfMusic_setVolume(music, 20);
    sfMusic_setLoop(music, sfTrue);
    sfMusic_play(music);
    game_params.world = create_world(&game_params);
    while (sfRenderWindow_isOpen(game_params.window)) {
        while (sfRenderWindow_pollEvent(game_params.window,
            &game_params.event))
            analyse_events(&game_params, buttons);
        handle_scene_menu(&game_params, buttons);
        handle_scene_world(&game_params, buttons);
        display_help(buttons, &game_params);
    }
    destroy_game_params(&game_params);
    destroy_buttons(buttons);
    sfMusic_destroy(music);
    return 0;
}
