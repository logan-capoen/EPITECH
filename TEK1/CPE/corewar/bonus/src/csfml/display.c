/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** display
*/

#include "../../include_csfml/op.h"

void display_vm(arena_t *arena)
{
    sfText **vm = arena->params->vm;
    int x = 0;
    int y = 0;

    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % 96 == 0) {
            y += 15;
            x = 10;
        }
        sfText_setPosition(vm[i], (sfVector2f){x, y});
        x += 15;
        sfRenderWindow_drawText(arena->params->window, vm[i], NULL);
    }
}

void display_pc(arena_t *arena)
{
    proc_t *tmp_proc = NULL;

    for (int i = 0; i < arena->nb_champions; i++) {
        tmp_proc = arena->champions[i]->procs;
        while (tmp_proc != NULL) {
            sfRectangleShape_setPosition(tmp_proc->pc_display,
                (sfVector2f){tmp_proc->pc % 96 * 15 + 10,
                tmp_proc->pc % MEM_SIZE / 96 * 15 + 15});
            sfRenderWindow_drawRectangleShape(arena->params->window,
                tmp_proc->pc_display, NULL);
            tmp_proc = tmp_proc->next;
        }
    }
}

static char *my_itoa(int num)
{
    int len = snprintf(NULL, 0, "%d", num);
    char *str = NULL;

    if (len < 0)
        return NULL;
    str = malloc(len + 1);
    if (!str)
        return NULL;
    snprintf(str, len + 1, "%d", num);
    return str;
}

void display_cycle(arena_t *arena, int cycle)
{
    char *str = malloc(sizeof(char) * 100);

    if (!str)
        return;
    strcpy(str, "Cycle: ");
    strcat(str, my_itoa(cycle));
    sfText_setPosition(arena->cycle_display,
        (sfVector2f){50, 1000});
    sfText_setString(arena->cycle_display, str);
    sfRenderWindow_drawText(arena->params->window,
        arena->cycle_display, NULL);
    strcpy(str, "Cycle to die: ");
    strcat(str, my_itoa(cycle % CYCLE_TO_DIE));
    strcat(str, " / ");
    strcat(str, my_itoa(CYCLE_TO_DIE - (CYCLE_DELTA * (arena->nb_live_signals / NBR_LIVE))));
    sfText_setPosition(arena->cycle_display,
        (sfVector2f){200, 1000});
    sfText_setString(arena->cycle_display, str);
    sfRenderWindow_drawText(arena->params->window,
        arena->cycle_display, NULL);
    free(str);
}

void display_champions(arena_t *arena)
{
    for (int i = 0; i < arena->nb_champions; i++) {
        if (arena->alive_champions[i] == false)
            sfSprite_setTexture(arena->champion_display[i],
                arena->champion_texture[2], sfTrue);
        else if (arena->live_signals[i] == true)
            sfSprite_setTexture(arena->champion_display[i],
                arena->champion_texture[0], sfTrue);
        else
            sfSprite_setTexture(arena->champion_display[i],
                arena->champion_texture[1], sfTrue);
        sfSprite_setScale(arena->champion_display[i],
            (sfVector2f){4, 4});
        sfText_setPosition(arena->champion_name[i],
            (sfVector2f){1635, 50 + i * 250 - 50});
        sfSprite_setPosition(arena->champion_display[i],
            (sfVector2f){1575, 50 + i * 250});
        sfRenderWindow_drawSprite(arena->params->window,
            arena->champion_display[i], NULL);
        sfRenderWindow_drawText(arena->params->window,
            arena->champion_name[i], NULL);
    }
}
