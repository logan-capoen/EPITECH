/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** NCURSE
*/

#ifndef NCURSE_HPP_
#define NCURSE_HPP_

#include "IDisplay.hpp"
#include "ArcadeException.hpp"
#include <ncurses.h>
#include <unordered_map>
#include <filesystem>
#include <iostream>
#include <string>

class Ncurses : public IDisplay {
    public:
        Ncurses();
        ~Ncurses();
        int createWindow() override;
        void closeWindow() override;
        void clear() override;
        void display() override;
        InputEvent getInput() override;
        void drawText(pos position, float size, std::string Text, Color color) override;
        void drawSprite(pos position, int rotation, float size, std::string) override;
        int loadTexture(std::string game) override;
        int loadSound(std::string game) override;
        int playSound(std::string sound_name) override;
        std::string loadName() override;
        std::tuple<int, int> recoverWindowSize() override;
        void drawBackground(std::string background_name) override;

    private:
        WINDOW *_win = nullptr;
        std::unordered_map<std::string, char> _asciiSprites;
        std::unordered_map<Color, int> _colorPairs;
        bool _initialized = false;
        void initColors();
};

#endif