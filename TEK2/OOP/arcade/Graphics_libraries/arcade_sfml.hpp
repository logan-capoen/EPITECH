/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IDisplay.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <filesystem>

class SFML : public IDisplay {
    public:
        SFML();
        ~SFML();
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
        std::unique_ptr<sf::RenderWindow> _window;
        sf::Font _font;
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::Sound> _sounds;
        std::unordered_map<std::string, sf::SoundBuffer> _soundBuffers;
        std::unordered_map<Color, sf::Color> _colors;
};

#endif /* !SFML_HPP_ */
