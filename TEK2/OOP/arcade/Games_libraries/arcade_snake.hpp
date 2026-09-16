/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "IGame.hpp"
#include <vector>

#define GRID_COLS 30
#define GRID_ROWS 20
#define TICK_RATE 8

#define KEY_UP 265
#define KEY_DOWN 264
#define KEY_LEFT 263
#define KEY_RIGHT 262

struct Cell {
    int col;
    int row;
};

enum class Dir {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake : public IGame {
    public:
        Snake();
        ~Snake() override = default;
        void update(InputEvent key) override;
        bool isOver() override;
        std::size_t getScore() override;
        std::vector<Sprite> getSprites() override;
        std::vector<Texte> getTextes() override;
        std::vector<std::string> getSounds() override;
    private:
        std::vector<Cell> _body;
        int _verticalDir;
        int _horizontalDir;
        int _nextVerticalDir;
        int _nextHorizontalDir;
        Cell _food;
        int  _tickCounter;
        bool _over;
    
        void spawnFood();
        bool cellIsFree(int col, int row) const;
        Dir dirBetween(const Cell &from, const Cell &to) const;
        std::string getBodySpriteName(int index) const;
        int getHeadRotation() const;
        int getBodyRotation(int index) const;
        int getTailRotation(int index) const;
};

#endif
