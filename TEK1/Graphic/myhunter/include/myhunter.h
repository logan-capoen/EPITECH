/*
** EPITECH PROJECT, 2024
** myhunter.h
** File description:
** header for myhunter
*/

#ifndef MYHUNTER
    #define MYHUNTER
    #include <SFML/Graphics/RenderWindow.h>
    #include <stdlib.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdio.h>
typedef struct game_clock {
    sfClock *clock;
    sfTime time;
    float seconds;
}game_clock_t;
typedef struct bird {
    sfSprite *sprite;
    sfVector2f position;
    struct bird *next;
    sfIntRect rect;
    game_clock_t clock;
    int isdead;
}bird_t;
typedef struct life {
    sfSprite *life;
    sfIntRect rect;
}life_t;
typedef struct game_params {
    sfEvent event;
    sfRenderWindow *window;
    sfSprite *background;
    bird_t *bird;
    sfTexture **bird_texture;
    game_clock_t clock_create_bird;
    int score_game;
    sfFont *font;
    int life;
    int scene;
    sfSprite *background_menu;
    life_t **life_sprite;
    int mod;
    sfText *game_over;
}game_params_t;
typedef struct button {
    sfSprite *button_go_restart;
    sfSprite *button_go_menu;
    sfSprite *button_play;
    sfSprite *button_skin;
    sfSprite *button_mod;
    sfSprite *button_quit;
    sfSprite *button_skin_crosshair;
    sfSprite *button_skin_landing_net;
    sfSprite *button_back;
    sfSprite *button_skin_mouse;
    sfSprite *button_srx;
    sfSprite *button_fun;
} button_t;
int handle_game(void);
sfRenderWindow *create_window(void);
sfSprite *create_background(char *pathfile);
void display_bird(game_params_t game_params);
void create_bird_after_lapstime(game_params_t *game_params);
game_clock_t create_clock(void);
void animation_bird(game_params_t game_params);
void click_on_bird(game_params_t *game_params, sfVector2f mouse_pos);
void play_sound(char *pathfile, int loop);
void set_cursor(game_params_t game_params, char *pathfile);
void sound_shoot_mod1(void);
sfText *create_text(game_params_t game_params,
    sfVector2f position, char *str, int size);
void set_score(game_params_t game_params, sfText *score);
void verify_position_bird(game_params_t *game_params);
void is_game_over(game_params_t *game_params);
sfSprite *create_button(char *pathfile, sfVector2f position);
button_t create_struct_button(void);
void click_on_restart(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void click_on_menu(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void click_on_play(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
int analyse_events(game_params_t *game_params,
    button_t buttons);
void click_on_quit(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
sfTexture **set_texture_bird(void);
void click_on_skin(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void click_on_skin_landing_net(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void click_on_skin_crosshair(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void click_on_back(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void click_on_skin_mouse(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
life_t **create_all_life(void);
void display_lifes(game_params_t game_params);
void click_on_mod(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void click_on_modsrx(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void click_on_modfun(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void play_sound_hurt(game_params_t game_params);
void keypressed_event(game_params_t *game_params,
    button_t buttons, sfVector2f mouse_pos);
void handle_scene_0(game_params_t *game_params, button_t buttons);
void handle_scene_1(game_params_t *game_params, button_t buttons,
    sfText *score, sfText *text_score);
void handle_scene_2(game_params_t *game_params, button_t buttons,
    sfText *text_game_over);
void handle_scene_3(game_params_t *game_params, button_t buttons);
void handle_scene_4(game_params_t *game_params, button_t buttons);
#endif
