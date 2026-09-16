#include "arcade_centipede.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

CentipedeSnake::CentipedeSnake(int startCol, int startRow, int dir, int length)
    : _dir(dir), _moveTimer(0)
{
    for (int i = 0; i < length; i++)
        _segs.push_back({startCol - i * dir, startRow});
}

const std::deque<GridPos>& CentipedeSnake::segs() const {
    return _segs;
}

int CentipedeSnake::dir() const {
    return _dir;
}

bool CentipedeSnake::empty() const {
    return _segs.empty();
}

bool CentipedeSnake::hasMushroom(int col, int row, const std::vector<Mushroom>& mushrooms) const
{
    for (const auto& m : mushrooms)
        if (m.col == col && m.row == row) return true;
    return false;
}

void CentipedeSnake::move(const std::vector<Mushroom>& mushrooms)
{
    if (++_moveTimer < MOVE_SPEED || _segs.empty())
        return;
    _moveTimer = 0;

    GridPos head = _segs.front();
    int nextCol = head.col + _dir;
    int nextRow = head.row;

    if (nextCol < 0 || nextCol >= GRID_COLS || hasMushroom(nextCol, head.row, mushrooms)) {
        nextRow += 1;
        nextCol = head.col;
        _dir = -_dir;
    }
    _segs.push_front({nextCol, nextRow});
    _segs.pop_back();
}

CentipedeSnake CentipedeSnake::split(int index)
{
    std::deque<GridPos> tailSegs;
    if (index + 1 < (int)_segs.size()) {
        tailSegs.assign(_segs.begin() + index + 1, _segs.end());
    }
    _segs.erase(_segs.begin() + index, _segs.end());
    
    CentipedeSnake tail(0, 0, -_dir, 0);
    tail._segs = tailSegs;
    return tail;
}

Centipede::Centipede()
    : _px(GRID_COLS / 2.0f), _py(GRID_ROWS - 2.0f), _lives(3), 
      _over(false), _won(false), _wavesCleared(0)
{
    _name = "centipede";
    _type = LibType::GAME;
    _bullet = {0.f, 0.f, false};
    _score = 0;
    std::srand(std::time(nullptr));
    resetMap();
}

void Centipede::spawnCentipede()
{
    _snakes.clear();
    _snakes.emplace_back(0, 0, 1, 12);
}

void Centipede::initMushrooms()
{
    _mushrooms.clear();
    for (int i = 0; i < 35; i++) {
        _mushrooms.push_back({std::rand() % GRID_COLS, 1 + std::rand() % (GRID_ROWS - 6), 5});
    }
}

void Centipede::resetMap()
{
    initMushrooms();
    spawnCentipede();
    _bullet.active = false;
}

void Centipede::handleInput(InputEvent value)
{
    const float speed = 1.0f;
    if (value.event == UP_ARROW && _py > (GRID_ROWS - 6))
        _py -= speed;
    if (value.event == DOWN_ARROW && _py < (GRID_ROWS - 1))
        _py += speed;
    if (value.event == LEFT_ARROW && _px > 0)
        _px -= speed;
    if (value.event == RIGHT_ARROW && _px < (GRID_COLS - 1))
        _px += speed;
    if (value.event == SPACE && !_bullet.active)
        _bullet = {_px, _py - 0.5f, true};
    if (value.event == QUIT)
        _over = true;
}

void Centipede::checkCollisions()
{
    if (!_bullet.active) return;

    int bc = static_cast<int>(std::round(_bullet.x));
    int br = static_cast<int>(std::round(_bullet.y));

    for (auto it = _mushrooms.begin(); it != _mushrooms.end(); ++it) {
        if (it->col == bc && it->row == br) {
            if (--it->health <= 0) { 
                _score += 1; 
                _mushrooms.erase(it); 
            }
            _bullet.active = false; 
            return;
        }
    }

    std::vector<CentipedeSnake> toAdd;
    for (auto it = _snakes.begin(); it != _snakes.end(); ) {
        bool hit = false;
        const auto &segs = it->segs();
        for (int i = 0; i < (int)segs.size(); i++) {
            if (segs[i].col == bc && segs[i].row == br) {
                _mushrooms.push_back({bc, br, 5}); 
                CentipedeSnake tail = it->split(i);
                if (!tail.empty()) toAdd.push_back(tail);
                _score += 10;
                _bullet.active = false;
                hit = true;
                break;
            }
        }
        if (it->empty())
            it = _snakes.erase(it); 
        else
            ++it;
        if (hit)
            break;
    }
    for (auto &s : toAdd)
        _snakes.push_back(s);
    if (_snakes.empty()) { 
        _wavesCleared++;
        resetMap();
    }
}

void Centipede::checkPlayerCollision()
{
    int pc = static_cast<int>(std::round(_px));
    int pr = static_cast<int>(std::round(_py));
    for (const auto &s : _snakes) {
        for (const auto &seg : s.segs()) {
            if (seg.col == pc && seg.row == pr) {
                if (--_lives <= 0)
                    _over = true;
                else
                    resetMap();
                return;
            }
        }
    }
}

void Centipede::update(InputEvent key)
{
    if (_over)
        return;
    handleInput(key);
    for (auto &s : _snakes)
        s.move(_mushrooms);
    if (_bullet.active) {
        _bullet.y -= 1.0f;
        if (_bullet.y < 0)
            _bullet.active = false;
    }
    checkCollisions();
    checkPlayerCollision();
    _sprites.clear();
    _textes.clear();
    for (auto &m : _mushrooms)
        _sprites.push_back({m.col, m.row, 0, 1.0f, "mushroom"});
    for (auto &s : _snakes) {
        const auto &segs = s.segs();
        for (int i = 0; i < (int)segs.size(); i++)
            _sprites.push_back({segs[i].col, segs[i].row, (s.dir() > 0 ? 0 : 180), 1.2f, (i == 0 ? "head" : "body")});
    }
    if (_bullet.active)
        _sprites.push_back({static_cast<int>(std::round(_bullet.x)), static_cast<int>(std::round(_bullet.y)), 0, 0.4f, "bullet"});
    _sprites.push_back({static_cast<int>(std::round(_px)), static_cast<int>(std::round(_py)), 0, 1.0f, "invader"});
    _textes.push_back({1, 0, FONT_NORMAL_TINY, "Score: " + std::to_string(_score), WHITE});
    _textes.push_back({10, 0, FONT_NORMAL_TINY, "Lives: " + std::to_string(_lives), WHITE});
}

bool Centipede::isOver() {
    return _over;
}

std::vector<Sprite> Centipede::getSprites() {
    return _sprites;
}

std::vector<Texte> Centipede::getTextes() {
    return _textes;
}

std::size_t Centipede::getScore() {
    return _score;
}

std::vector<std::string> Centipede::getSounds() {
    return _sounds;
}

extern "C" IGame* entryPoint() {
    return new Centipede();
}
