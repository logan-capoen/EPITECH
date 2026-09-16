/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** main
*/

#include "Core.hpp"
#include "ArcadeException.hpp"
#include "Parse.hpp"
#include <iostream>

int main(int ac, char **av, char **env)
{
    try {
        Parse parser;
        parser.isTTY(env);
        parser.parse(ac, av);
        Core core;
        core.loadLibs("lib");
        core.run(av[1]);
    } catch (const ArcadeException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}