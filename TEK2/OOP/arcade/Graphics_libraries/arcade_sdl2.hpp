/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** SDL2
*/

#ifndef SDL2_HPP_
#define SDL2_HPP_

#include "IDisplay.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <unordered_map>
#include <filesystem>

class SDL2 : public IDisplay {
    public:
        SDL2();
        ~SDL2();
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
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        TTF_Font *_font;
        std::unordered_map<std::string, SDL_Texture *> _textures;
        std::unordered_map<std::string, Mix_Chunk *> _sounds;
        std::unordered_map<Color, SDL_Color> _colors;
};

#endif /* !SDL2_HPP_ */
