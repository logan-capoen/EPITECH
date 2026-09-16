// /*
// ** EPITECH PROJECT, 2025
// ** corewar
// ** File description:
// ** handle_menu
// */

// #include "../../include_csfml/op.h"

// static int check_assets(void)
// {
//     if (access(FONT_PATH, F_OK) == -1)
//         return 0;
//     if (access(BACK_PATH, F_OK) == -1)
//         return 0;
//     return 1;
// }

// static void analyze_events(graph_t *core)
// {
//     while (sfRenderWindow_pollEvent(core->window, core->event)) {
//         if (core->event->type == sfEvtClosed)
//             sfRenderWindow_close(core->window);
//         if (core->event->type == sfEvtMouseButtonPressed) {
//             act_buttons(core, core->event->mouseButton);
//         }
//     }
// }

// static void refresh_frames(graph_t *core)
// {
//     sfRenderWindow_clear(core->window, sfBlack);
//     sfRenderWindow_drawSprite(core->window, core->background, NULL);
//     sfRenderWindow_drawText(core->window, core->title, NULL);
//     for (int i = 0; i < MAX_CHAMPS + 1; i++) {
//         sfRenderWindow_drawRectangleShape(core->window,
//             core->buttons[i]->rect, NULL);
//         sfRenderWindow_drawText(core->window, core->buttons[i]->text, NULL);
//     }
//     sfRenderWindow_display(core->window);
// }

// static int run_warloop(graph_t *core)
// {
//     fill_text(core);
//     create_buttons(core);
//     while (sfRenderWindow_isOpen(core->window)) {
//         analyze_events(core);
//         refresh_frames(core);
//     }
// }

// static int handle_game(void)
// {
//     sfVideoMode mode[] = {1920, 1080, 32};
//     sfRenderWindow *window = sfRenderWindow_create(*mode, "Corewar",
//         sfDefaultStyle, NULL);
//     sfEvent event;
//     sfText *title_text = sfText_create();
//     graph_t core = {mode, window, &event, title_text, NULL, NULL, NULL};
//     sfTexture *texture = sfTexture_createFromFile(BACK_PATH, NULL);
//     sfSprite *background = sfSprite_create();
//     int exit = 0;

//     sfSprite_setTexture(background, texture, sfTrue);
//     core.background = background;
//     sfRenderWindow_setFramerateLimit(core.window, 60);
//     exit = run_warloop(&core);
//     sfSprite_destroy(background);
//     sfTexture_destroy(texture);
//     destroy_all(&core);
//     return exit;
// }