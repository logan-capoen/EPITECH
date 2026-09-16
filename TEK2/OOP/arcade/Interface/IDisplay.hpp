/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** IDisplay
*/

#ifndef IDisplay_HPP_
#define IDisplay_HPP_

#include "Common.hpp"
#include <string>
#include "ALib.hpp"

class IDisplay : public ALib {
    public:
        virtual ~IDisplay() = default;

        virtual int createWindow() = 0;
        virtual void closeWindow() = 0;
        virtual void clear() = 0;
        virtual void display() = 0;

        virtual InputEvent getInput() = 0;

        virtual void drawBackground(std::string background_name) = 0;
        virtual void drawText(pos position, float size, std::string text, Color color) = 0;
        virtual void drawSprite(pos position, int rotation, float size, std::string name) = 0;

        virtual int loadTexture(std::string game) = 0;
        virtual int loadSound(std::string game) = 0;
        virtual int playSound(std::string sound_name_in_map) = 0;
        virtual std::string loadName() = 0;
        virtual std::tuple<int, int> recoverWindowSize() = 0;
};

#endif /* !IDisplay_HPP_ */
