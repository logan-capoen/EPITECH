/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** buttons
*/

#ifndef BUTTONS
    #define BUTTONS
    #include "myworld.h"

const button_params_t params[] = {
    {"assets/images/new.png", "assets/images/new_hover.png",
        {375, 100}, {1.5, 1.5}, "Generates a plain world", 0},
    {"assets/images/quit.png", "assets/images/quit_hover.png",
        {650, 800}, {1.5, 1.5}, "Quit the world creator software", 0},
    {"assets/images/back.png", "assets/images/back_hover.png",
        {1500, 900}, {1, 1}, "Go back on the menu screen", 4},
    {"assets/images/load.png", "assets/images/load_hover.png",
        {638, 450}, {1.5, 1.5}, "Load a map form a '.legend' file", 0},
    {"assets/images/save.png", "assets/images/save_hover.png",
        {10, 900}, {1, 1}, "Save the current map to a '.legend' file", 4},
    {"assets/images/button_up.png", "assets/images/button_up_hover.png",
        {500, 40}, {0.7, 0.7},
        "Change the default brush motion to 'up' (U)", 4},
    {"assets/images/empty_button.png", "assets/images/empty_button_hover.png",
        {800, 40}, {0.7, 0.7},
        "Reset 'z' coordinates to 0 (B)", 4},
    {"assets/images/button_down.png", "assets/images/button_down_hover.png",
        {1100, 40}, {0.7, 0.7},
        "Change the default brush motion to 'down' (I)", 4}};


#endif
