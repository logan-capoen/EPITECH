/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "Common.hpp"
#include <string>
#include "ALib.hpp"
#include "IDisplay.hpp"
#include <string>
#include <vector>

struct Texte {
    int x = 0;
    int y = 0;
    float size = 1.0f;
    std::string text = "";
    Color color = WHITE;
};

struct Sprite {
    int x = 0;
    int y = 0;
    int rotation = 0;
    float size = 1.0f;
    std::string name = "";
};

class IGame : public ALib {
    public:
        virtual ~IGame() = default;
        virtual void update(InputEvent key) = 0;
        virtual bool isOver() = 0;
        virtual std::size_t getScore() = 0;
        virtual std::vector<Sprite> getSprites() = 0;
        virtual std::vector<Texte> getTextes() = 0;
        virtual std::vector<std::string> getSounds() = 0;
    protected:
        std::vector<Sprite> _sprites;
        std::vector<Texte>  _textes;
        std::vector<std::string> _sounds;
        std::size_t _score;
};

#endif /* !IGAME_HPP_ */
