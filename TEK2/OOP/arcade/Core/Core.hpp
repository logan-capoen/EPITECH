/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <map>
#include <memory>
#include <vector>
#include <string>
#include "Common.hpp"
#include "LibLoader.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"
#include <fstream>
#include <algorithm>

class Core {
    protected:
        std::string string = "";
    public:
        Core();
        ~Core();

        int loadLibs(const std::string &directory);
        void run(const std::string &lib_display);

    private:
        template <typename T>
        std::unique_ptr<T> loadTypedLib(LibLoader &loader, const std::string &path);

        struct Button {
            std::string label;
            Rect rect;
        };

        struct Carousel {
            std::vector<std::string> values;
            int index = 0;
        };

        struct MenuButtons {
            Button displayLeft;
            Button displayRight;
            Button validateDisplay;
            Button gameLeft;
            Button gameRight;
            Button playButton;
        };

        std::vector<std::string> _displayLibs;
        std::vector<std::string> _gameLibs;

        LibLoader _displayLoader;
        LibLoader _gameLoader;

        std::unique_ptr<IDisplay> _display;
        std::unique_ptr<IGame> _game;

        Carousel _displayCarousel;
        Carousel _gameCarousel;

        std::string _selectedDisplayLib;
        std::string _selectedGameLib;

        struct ScoreEntry {
            std::string name;
            int score;
        };

        std::vector<ScoreEntry> _scores;
        std::string _name;

        bool _canStartGame = false;

        void switchDisplay(const std::string &lib_display);
        void switchGame(const std::string &lib_game);

        void initCarousels();

        bool isInside(const pos &mouse, const Rect &box) const;
        void moveLeft(Carousel &carousel);
        void moveRight(Carousel &carousel);
        std::string getCurrentItem(const Carousel &carousel) const;
        MenuButtons getMenuButtons() const;
        std::string getName(const std::string &path);
        pos getRectCenter(const Rect &rect) const;

        void drawMenu();
        void handleMenuClick(const pos &mouse);
        void validateSelectedDisplay();
        void startSelectedGame();
        void changeDisplayInGame();
        void changeGameInGame();
        void runMenu();
        int runGame();
        void getScore();
        void drawScores();
        void updateScores(int score);
};

template <typename T>
std::unique_ptr<T> Core::loadTypedLib(LibLoader &loader, const std::string &path)
{
    if (!loader.loadLib(path))
        return nullptr;

    auto loadedLib = loader.getFunction<ILib *(*)()>("entryPoint");
    if (!loadedLib)
        return nullptr;

    ILib *newLib = loadedLib();
    T *castedLib = dynamic_cast<T *>(newLib);
    if (!castedLib) {
        delete newLib;
        return nullptr;
    }
    return std::unique_ptr<T>(castedLib);
}

#endif /* !CORE_HPP_ */
