#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include "IGame.hpp"
#include <vector>
#include <deque>
#include <string>

#define GRID_COLS   30
#define GRID_ROWS   20
#define PLAYER_ROW  21 
#define MOVE_SPEED  4
#define MAX_WAVES   20

struct Bullet {
    float x, y;
    bool  active;
};

struct Mushroom {
    int col, row;
    int health;
};

struct GridPos {
    int col, row;
};

class CentipedeSnake {
    public:
        CentipedeSnake(int startCol, int startRow, int dir, int length);
        void move(const std::vector<Mushroom>& mushrooms);
        CentipedeSnake split(int index);
        bool empty() const;
        int size() const;
        int dir() const;
        bool atBottom() const;
        const std::deque<GridPos>& segs() const;
    private:
        std::deque<GridPos> _segs;
        int _dir;
        int _moveTimer;

        bool hasMushroom(int col, int row, const std::vector<Mushroom>& mushrooms) const;
};

class Centipede : public IGame {
    public:
        Centipede();
        ~Centipede() override = default;
        void update(InputEvent key) override;
        bool isOver() override;
        std::size_t getScore() override;
        std::vector<Sprite> getSprites() override;
        std::vector<Texte> getTextes() override;
        std::vector<std::string> getSounds() override;

        private:
        float _px, _py;
        int _lives;
        bool _over;
        bool _won;
        int _shootCooldown;
        int _wavesCleared;
        std::vector<CentipedeSnake> _snakes;
        Bullet _bullet;
        std::vector<Mushroom>  _mushrooms;

        void getRenderList();
        void handleInput(InputEvent key);
        void updateBullet();
        void checkCollisions();
        void checkPlayerCollision();
        void checkBottomCollision();
        void spawnCentipede();
        void initMushrooms();
        void resetMap();
        int px(int col) const;
        int py(int row) const;
        bool hasMushroom(int col, int row) const;
};

#endif
