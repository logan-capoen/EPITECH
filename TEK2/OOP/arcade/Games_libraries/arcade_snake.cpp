/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** Snake
*/

#include "arcade_snake.hpp"
#include "Common.hpp"
#include <cstdlib>
#include <ctime>

Snake::Snake()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    _name = "snake";
    _type = LibType::GAME;
    _verticalDir = 0;
    _horizontalDir = 1;
    _nextVerticalDir = 0;
    _nextHorizontalDir = 1;
    _score = 0;
    _tickCounter = 0;
    _over = false;
    int midCol = GRID_COLS / 2;
    int midRow = GRID_ROWS / 2;
    for (int i = 0; i < 4; i++)
        _body.push_back({midCol - i, midRow});
    spawnFood();
}

bool Snake::isOver()
{
    return _over;
}

void Snake::update(InputEvent value)
{
    if (_over)
        return;
    if (value.event == UP_ARROW && _verticalDir != 1) {
        _nextVerticalDir = -1;
        _nextHorizontalDir = 0;
    } else if (value.event == DOWN_ARROW && _verticalDir != -1) {
        _nextVerticalDir = 1;
        _nextHorizontalDir = 0;
    } else if (value.event == LEFT_ARROW && _horizontalDir != 1) {
        _nextVerticalDir = 0;
        _nextHorizontalDir = -1;
    } else if (value.event == RIGHT_ARROW && _horizontalDir != -1) {
        _nextVerticalDir = 0;
        _nextHorizontalDir = 1;
    }
    _tickCounter++;
    if (_tickCounter < TICK_RATE)
        return;
    _tickCounter = 0;
    _verticalDir = _nextVerticalDir;
    _horizontalDir = _nextHorizontalDir;
 
    Cell newHead;
    newHead.col = _body[0].col + _horizontalDir;
    newHead.row = _body[0].row + _verticalDir;
 
    if (newHead.col <= 0 || newHead.col >= GRID_COLS - 1 ||
        newHead.row <= 0 || newHead.row >= GRID_ROWS - 1) {
        _over = true;
        return;
    }
    for (int i = 0; i < (int)_body.size() - 1; i++) {
        if (_body[i].col == newHead.col && _body[i].row == newHead.row) {
            _over = true;
            return;
        }
    }
    _body.insert(_body.begin(), newHead);
    if (newHead.col == _food.col && newHead.row == _food.row) {
        spawnFood();
    } else {
        _body.pop_back();
    }
}

std::vector<Sprite> Snake::getSprites()
{
    const int mapOffsetX = X_CENTER - (GRID_COLS);
    const int mapOffsetY = Y_CENTER - (GRID_ROWS);
    const int drawOffsetX = mapOffsetX + PADDING_MEDIUM;
    const int drawOffsetY = mapOffsetY + PADDING_NORMAL_TINY;

    _sprites.clear();
    for (int i = 0; i < (int)_body.size(); i++) {
        Sprite s;
        s.x = _body[i].col;
        s.y = _body[i].row;
        s.size = 1.0f;
        s.name = getBodySpriteName(i);
        if (i == 0) {
            s.rotation = getHeadRotation();
        } else if (i ==(int)_body.size() - 1) {
            s.rotation = getTailRotation(i);
        } else if (s.name == "snake_body") {
            s.rotation = getBodyRotation(i);
        } else {
            s.rotation = 0; 
        }
        _sprites.push_back(s);
    }
    for (int c = 0; c < GRID_COLS; c++) {
        _sprites.push_back({c, 0, 0, 1.20f, "snake_wall"});
        _sprites.push_back({c, (GRID_ROWS - 1), 0, 1.20f, "snake_wall"});
    }
    for (int r = 1; r < GRID_ROWS - 1; r++) {
        _sprites.push_back({0, r, 0, 1.20f, "snake_wall"});
        _sprites.push_back({(GRID_COLS - 1), r, 0, 1.20f, "snake_wall"});
    }
    _sprites.push_back({_food.col, _food.row, 0, 1.0f, "snake_food"});
    return _sprites;
}

std::vector<Texte> Snake::getTextes()
{
    _textes.clear();
    _textes.push_back({2, 1, FONT_LARGE_MEDIUM, "Score: " + std::to_string((int)_body.size() - 4)});
    if (_over)
        _textes.push_back({(GRID_COLS / 2 - 5), (GRID_ROWS / 2), 2, "GAME OVER\n\nFinal Score: " + std::to_string((int)_body.size() - 4)});
    return _textes;
}

bool Snake::cellIsFree(int col, int row) const
{
    for (int i = 0; i < (int)_body.size(); i++)
        if (_body[i].col == col && _body[i].row == row)
            return false;
    return true;
}

void Snake::spawnFood()
{
    std::vector<Cell> freeCells;
    for (int r = 1; r < GRID_ROWS - 1; r++) {
        for (int c = 1; c < GRID_COLS - 1; c++) {
            if (cellIsFree(c, r)) {
                freeCells.push_back({c, r});
            }
        }
    }
    if (freeCells.empty()) {
        _over = true;
        return;
    }
    int index = std::rand() % (int)freeCells.size();
    _food = freeCells[index];
}

Dir Snake::dirBetween(const Cell &from, const Cell &to) const
{
    if (to.col > from.col)
        return Dir::RIGHT;
    if (to.col < from.col)
        return Dir::LEFT;
    if (to.row > from.row)
        return Dir::DOWN;
    return Dir::UP;
}

std::string Snake::getBodySpriteName(int index) const
{
    if (index == 0)
        return "snake_head";
    if (index == (int)_body.size() - 1)
        return "snake_tail";
    Dir toHead = dirBetween(_body[index], _body[index - 1]);
    Dir toTail = dirBetween(_body[index], _body[index + 1]);
 
    bool straightHorizontal = (toHead == Dir::LEFT && toTail == Dir::RIGHT) || (toHead == Dir::RIGHT && toTail == Dir::LEFT);
    bool straightVertical = (toHead == Dir::UP && toTail == Dir::DOWN) || (toHead == Dir::DOWN && toTail == Dir::UP);
    if (straightHorizontal || straightVertical)
        return "snake_body";

    bool connectsUp = (toHead == Dir::UP || toTail == Dir::UP);
    bool connectsDown = (toHead == Dir::DOWN || toTail == Dir::DOWN);
    bool connectsLeft = (toHead == Dir::LEFT || toTail == Dir::LEFT);
    bool connectsRight = (toHead == Dir::RIGHT || toTail == Dir::RIGHT);
 
    if (connectsUp && connectsLeft)
        return "snake_turn_bottom_to_left";
    if (connectsUp && connectsRight)
        return "snake_turn_bottom_to_right";
    if (connectsDown && connectsLeft)
        return "snake_turn_top_to_left";
    if (connectsDown && connectsRight)
        return "snake_turn_top_to_right";
    return "snake_body";
}

int Snake::getHeadRotation() const
{
    if (_horizontalDir == 1) {
        return 180;
    } else if (_horizontalDir == -1) {
        return 0;
    } else if (_verticalDir == 1) {
        return 270;
    } else if (_verticalDir == -1) {
        return 90;
    }
    return 0;
}

int Snake::getBodyRotation(int index) const
{
    Dir toHead = dirBetween(_body[index], _body[index - 1]);
 
    if (toHead == Dir::LEFT || toHead == Dir::RIGHT)
        return 0;
    return 90;
}

int Snake::getTailRotation(int index) const
{
    Dir toBody = dirBetween(_body[index], _body[index - 1]);
 
    if (toBody == Dir::RIGHT)
        return 180;
    if (toBody == Dir::LEFT)
        return 0;
    if (toBody == Dir::DOWN)
        return 270;
    return 90;
}

std::size_t Snake::getScore()
{
    return (int)_body.size() - 4;
}

std::vector<std::string> Snake::getSounds()
{
    return _sounds;
}

extern "C" ILib* entryPoint()
{
    return new Snake();
}
