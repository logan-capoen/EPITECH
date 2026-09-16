/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** Parse
*/

#include "Parse.hpp"
#include "ArcadeException.hpp"
#include "iostream"
#include <filesystem>

Parse::Parse() : _argc(0), _argv(nullptr)
{
}

Parse::~Parse()
{
}

bool Parse::isValidLibFormat(const std::string &libPath) const
{
    std::filesystem::path lib(libPath);

    return lib.extension() == ".so";
}

void Parse::parse(int ac, char **av)
{
    _argc = ac;
    _argv = av;
    if (_argc != 2)
        throw ArcadeException("Usage:\n\t./arcade ./lib/arcade_ncurses.so");
    if (!isValidLibFormat(_argv[1]))
        throw ArcadeException("The graphical library provided isn't in the expected format: .so");
    return;
}

void Parse::isTTY(char **env) const
{
    if (!env)
        throw ArcadeException("Env not found");
    for (int i = 0; env[i]; i++) {
        std::string current = env[i];
        if (current == "DISPLAY=:0" || current == "DISPLAY=:1")
            return;
    }
    throw ArcadeException("Graphical env not found");
}