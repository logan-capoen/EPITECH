/*
** EPITECH PROJECT, 2024
** bird.c
** File description:
** all function for handle birds
*/

#include "include/myhunter.h"
#include <stdlib.h>
#include <stdio.h>


static void create_bird(bird_t **bird, sfTexture *texture_bird)
{
    sfSprite *bird_sprite = sfSprite_create();
    sfVector2f position = {-50.0, rand() % 1000};
    bird_t *new_bird = malloc(sizeof(bird_t));
    sfIntRect rect = {0, 0, 140, 140};

    sfSprite_setTexture(bird_sprite, texture_bird, sfTrue);
    sfSprite_setPosition(bird_sprite, position);
    new_bird->sprite = bird_sprite;
    new_bird->position = position;
    new_bird->rect = rect;
    new_bird->next = *bird;
    new_bird->clock = create_clock();
    new_bird->isdead = 0;
    *bird = new_bird;
}

static sfTexture *get_texture_bird(game_params_t game_params)
{
    int random = rand() % 5;

    switch (random) {
    case 0:
        return game_params.bird_texture[0];
    case 1:
        return game_params.bird_texture[1];
    case 2:
        return game_params.bird_texture[2];
    case 3:
        return game_params.bird_texture[3];
    case 4:
        return game_params.bird_texture[4];
    }
}

void create_bird_after_lapstime(game_params_t *game_params)
{
    game_params->clock_create_bird.time =
        sfClock_getElapsedTime(game_params->clock_create_bird.clock);
    game_params->clock_create_bird.seconds =
        game_params->clock_create_bird.time.microseconds / 1000000.0;
    if (game_params->clock_create_bird.seconds > 1) {
        create_bird(&game_params->bird, get_texture_bird(*game_params));
        sfClock_restart(game_params->clock_create_bird.clock);
    }
}

void display_bird(game_params_t game_params)
{
    while (game_params.bird != NULL) {
        sfSprite_setTextureRect(game_params.bird->sprite,
            game_params.bird->rect);
        sfRenderWindow_drawSprite(game_params.window,
            game_params.bird->sprite, NULL);
        animation_bird(game_params);
        game_params.bird = game_params.bird->next;
    }
}

static void change_sprite_bird(bird_t *bird)
{
    if (bird->rect.left == 420 - 140) {
        bird->rect.left = 0;
    } else {
        bird->rect.left += 140;
    }
}

static void move_bird(game_params_t game_params)
{
    game_params.bird->position.x += 15 + game_params.score_game;
    sfSprite_setPosition(game_params.bird->sprite, game_params.bird->position);
}

void animation_bird(game_params_t game_params)
{
    game_params.bird->clock.time = sfClock_getElapsedTime
        (game_params.bird->clock.clock);
    game_params.bird->clock.seconds =
        game_params.bird->clock.time.microseconds / 1000000.0;
    if (game_params.bird->clock.seconds > 0.05)
        move_bird(game_params);
    if (game_params.bird->clock.seconds > 0.1) {
        change_sprite_bird(game_params.bird);
        sfClock_restart(game_params.bird->clock.clock);
    }
}

static void delete_bird(bird_t **bird)
{
    bird_t *tmp = *bird;
    bird_t *prev = *bird;

    if (tmp->isdead) {
        *bird = tmp->next;
        free(tmp);
        return;
    }
    tmp = tmp->next;
    while (tmp != NULL) {
        if (tmp->isdead) {
            prev->next = tmp->next;
            sfClock_destroy(tmp->clock.clock);
            sfSprite_destroy(tmp->sprite);
            free(tmp);
        }
        tmp = tmp->next;
        prev = prev->next;
    }
}

void click_on_bird(game_params_t *game_params, sfVector2f mouse_pos)
{
    sfFloatRect hitbox;
    bird_t *tmp = game_params->bird;

    while (tmp != NULL) {
        hitbox = sfSprite_getGlobalBounds(tmp->sprite);
        if (sfFloatRect_contains(&hitbox, mouse_pos.x, mouse_pos.y)) {
            play_sound("assets/sounds/dead_sound.ogg", 0);
            tmp->isdead = 1;
            delete_bird(&game_params->bird);
            game_params->score_game += 1;
        }
        tmp = tmp->next;
    }
}

void verify_position_bird(game_params_t *game_params)
{
    bird_t *tmp = game_params->bird;

    while (tmp != NULL) {
        if (tmp->position.x > 1950) {
            tmp->isdead = 1;
            play_sound_hurt(*game_params);
            game_params->life -= 1;
            game_params->life_sprite[game_params->life]->rect.left += 108;
            delete_bird(&game_params->bird);
        }
        tmp = tmp->next;
    }
}
