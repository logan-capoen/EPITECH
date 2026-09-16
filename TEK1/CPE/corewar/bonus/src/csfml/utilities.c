/*
** EPITECH PROJECT, 2025
** tmp_core
** File description:
** utilities
*/

#include "../../include_csfml/op.h"

int check_launch_condition(game_params_t *params)
{
    int activated_champs = 0;

    for (int i = 0; i < MAX_CHAMPS; i++) {
        if (params->buttons[i]->file) {
            activated_champs++;
        }
    }
    return activated_champs >= 2;
}

// void destroy_all(graph_t *core)
// {
//     for (int i = 0; i < MAX_CHAMPS + 1; i++) {
//         sfRectangleShape_destroy(core->buttons[i]->rect);
//         sfText_destroy(core->buttons[i]->text);
//         if (core->buttons[i]->file)
//             free(core->buttons[i]->file);
//         free(core->buttons[i]);
//     }
//     free(core->buttons);
//     sfText_destroy(core->title);
//     sfFont_destroy(core->font);
//     sfRenderWindow_destroy(core->window);
// }

// void fill_text(graph_t *core)
// {
//     core->font = sfFont_createFromFile(FONT_PATH);
//     sfText_setFont(core->title, core->font);
//     sfText_setString(core->title, "Select your champions");
//     sfText_setPosition(core->title, (sfVector2f){520, 25});
//     sfText_setScale(core->title, (sfVector2f){2, 2});
// }

static char *read_file_path(FILE *fp)
{
    size_t len = 0;
    char *path = malloc(sizeof(char) * MAX_PATH);

    if (fgets(path, MAX_PATH, fp) != NULL) {
        len = strlen(path);
        if (len > 0 && path[len - 1] == '\n')
            path[len - 1] = '\0';
        return path;
    }
    free(path);
    return NULL;
}

char *file_explorer_load(void)
{
    const char *command = "zenity --file-selection --title='Corewar' "
        "--file-filter='Compiled champions (.cor) | *.cor' 2>/dev/null";
    FILE *fp = popen(command, "r");
    char *path = NULL;

    if (fp == NULL) {
        dprintf(2, "Failed to run Zenity\n");
        return NULL;
    }
    path = read_file_path(fp);
    pclose(fp);
    return path;
}
