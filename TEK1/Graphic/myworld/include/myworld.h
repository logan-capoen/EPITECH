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
    #include <unistd.h>
    #include "my.h"
    #include <fcntl.h>
    #include "printf.h"
    #include <string.h>
    #include <sys/stat.h>
    #include <pthread.h>
    #include <math.h>
    #define PATH_MAX_LEN 2048
    #define FILE_HEADER 6

typedef struct game_clock {
    sfClock *clock;
    sfTime time;
    float seconds;
}game_clock_t;

typedef struct world {
    int **map;
    int size;
    int zoom;
    float offset_x;
    float offset_y;
    float rotation_horizontal;
    float rotation_vertical;
    int brush;
    int radius;
    sfView *camera;
    sfSprite *background;
    sfFont *font;
    sfSound *up;
    sfSound *down;
} world_t;

typedef struct game_params {
    sfEvent event;
    sfRenderWindow *window;
    sfSprite *background;
    sfFont *font;
    int scene;
    sfSprite *background_menu;
    world_t world;
    sfVector2f camera_position;
    sfVector2u window_size;
    sfView *ui;
    sfTexture **textures;
    sfSprite *menu_size;
    game_clock_t clock;
} game_params_t;

typedef struct button {
    sfSprite *button;
    sfTexture *button_texture;
    sfTexture *button_texture_hover;
    sfText *help;
    int scene;
} button_t;

typedef struct button_params {
    char *image_path;
    char *hover_image_path;
    sfVector2f position;
    sfVector2f size;
    char *help_message;
    int scene;
} button_params_t;

typedef struct vertex_s {
    sfRenderStates state;
    sfVector2f **points;
    sfVertexArray *square;
    sfVector2f **map2d;
} vertex_t;

// WINDOW
int handle_game(void);
sfRenderWindow *create_window(void);
sfSprite *create_background(char *pathfile);
game_clock_t create_clock(void);
void play_music(char *pathfile, int loop);
void set_cursor(game_params_t game_params, char *pathfile);
sfText *create_text(game_params_t *game_params,
    sfVector2f position, char *str, int size);
button_t *create_struct_button(void);
void display_world(game_params_t *game_params);
int display_help(button_t *button, game_params_t *game_params);
sfSound *create_sound(char *pathfile);
void limit_bordure(int i, int j,
    game_params_t *game_params, vertex_t *vertex);

//EVENTS
int analyse_events(game_params_t *game_params,
    button_t *buttons);
void keypressed_event(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void handle_event_world(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void keyboard_pressed(game_params_t *game_params, button_t *buttons);
int hover_button(button_t *button, sfVector2f mouse_pos,
    game_params_t *game_params);

// CLICK BUTTON
void click_on_quit(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void click_on_world(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void click_on_load(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void click_on_back(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void click_on_save(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void click_on_up(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void click_on_empty(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void click_on_down(game_params_t *game_params,
    button_t *buttons, sfVector2f mouse_pos);
void click_on_map(game_params_t *game_params);

// SCENES AND MAPS
void handle_scene_menu(game_params_t *game_params, button_t *buttons);
void handle_scene_world(game_params_t *game_params, button_t *buttons);
int **create_3d_map(int size);
sfVector2f **create_2d_map(int **map3d, game_params_t *game_params);
void reset_map(game_params_t *game_params);

// SAVE LOAD
int save_map(world_t *world);
int **load(game_params_t *game_params);
char *file_explorer_load(char *path, size_t path_len);
char *file_explorer_save(char *path, size_t path_len);

// UTILITIES
unsigned int revbytes(unsigned int num);
char *int_to_str_two(int num);
int get_size(char *path);


// BROWSE
void load_top_left(game_params_t *game_params, vertex_t vertex);
void load_top_right(game_params_t *game_params, vertex_t vertex);
void load_bottom_right(game_params_t *game_params, vertex_t vertex);
void load_bottom_left(game_params_t *game_params, vertex_t vertex);

// DESTROY
void destroy_game_params(game_params_t *game_params);
void destroy_buttons(button_t *buttons);
void destroy_map(sfVector2f **map2d, int size);

#endif
