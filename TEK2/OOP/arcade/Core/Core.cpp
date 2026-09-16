/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** Core
*/

#include "Core.hpp"
#include "ArcadeException.hpp"
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <ILib.hpp>
#include <thread>
#include <chrono>

Core::Core()
{
}

Core::~Core()
{
}

int Core::loadLibs(const std::string &directory)
{

    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        throw ArcadeException("libs directory not found: " + directory);
    }
    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
        if (!entry.is_regular_file() || entry.path().extension() != ".so")
            continue;

        std::string path = entry.path().string();
        LibLoader loader;

        if (!loader.loadLib(path))
            continue;

        auto loaded_lib = loader.getFunction<ILib *(*)()>("entryPoint");
        if (!loaded_lib) {
            std::cerr << "Unknown lib (no entryPoint): " << path << std::endl;
            continue;
        }

        std::unique_ptr<ILib> lib(loaded_lib());

        if (lib->get_type() == LibType::DISPLAY) {
            _displayLibs.push_back(path);
        } else if (lib->get_type() == LibType::GAME) {
            _gameLibs.push_back(path);
        } else {
            throw ArcadeException("Fail to load: '" + path + "' lib type unknown");
        }
    }
    return 0;
}

bool Core::isInside(const pos &mouse, const Rect &box) const
{
    return mouse.x >= box.x && mouse.x <= box.x + box.width && mouse.y >= box.y && mouse.y <= box.y + box.height;
}

void Core::moveLeft(Carousel &carousel)
{
    if (carousel.values.empty())
        return;
    carousel.index--;
    if (carousel.index < 0)
        carousel.index = static_cast<int>(carousel.values.size()) - 1;
}

void Core::moveRight(Carousel &carousel)
{
    if (carousel.values.empty())
        return;
    carousel.index++;
    if (carousel.index >= static_cast<int>(carousel.values.size()))
        carousel.index = 0;
}

std::string Core::getCurrentItem(const Carousel &carousel) const
{
    if (carousel.values.empty())
        return "";
    return carousel.values[carousel.index];
}

void Core::initCarousels()
{
    _displayCarousel.values = _displayLibs;
    _gameCarousel.values = _gameLibs;
    _displayCarousel.index = 0;
    _gameCarousel.index = 0;
}

void Core::switchDisplay(const std::string &lib_display)
{
    _display = nullptr;
    _displayLoader.closeLib();
    _display = loadTypedLib<IDisplay>(_displayLoader, lib_display);

    if (!_display)
        std::cerr << "fail to load: '" << lib_display << "' as display lib" << std::endl;
}

void Core::switchGame(const std::string &lib_game)
{
    _game = nullptr;
    _gameLoader.closeLib();
    _game = loadTypedLib<IGame>(_gameLoader, lib_game);

    if (!_game)
        std::cerr << "fail to load: '" << lib_game << "' as game lib" << std::endl;
}

std::string Core::getName(const std::string &path)
{
    return std::filesystem::path(path).stem().string();
}

pos Core::getRectCenter(const Rect &rect) const
{
    return {rect.x + rect.width / 2, rect.y + rect.height / 2};
}

Core::MenuButtons Core::getMenuButtons() const
{
    return {
        {"<", {X_CENTER - 5, Y_CENTER - 4, 1, 1}},
        {">", {X_CENTER + 4, Y_CENTER - 4, 1, 1}},
        {"VALIDER", {X_CENTER - 3, Y_CENTER - 2, 6, 1}},
        {"<", {X_CENTER - 5, Y_CENTER + 4, 1, 1}},
        {">", {X_CENTER + 4, Y_CENTER + 4, 1, 1}},
        {"JOUER", {X_CENTER - 2, Y_CENTER + 6, 4, 1}}
    };
}

void Core::drawMenu()
{
    MenuButtons layout = getMenuButtons();
    
    std::string currentDisplay = getCurrentItem(_displayCarousel);
    std::string currentGame = getCurrentItem(_gameCarousel);
    
    pos displayLeftCenter  = getRectCenter(layout.displayLeft.rect);
    pos displayRightCenter = getRectCenter(layout.displayRight.rect);
    pos gameLeftCenter = getRectCenter(layout.gameLeft.rect);
    pos gameRightCenter = getRectCenter(layout.gameRight.rect);
    
    _display->drawText({-1, 1}, FONT_NORMAL, "ARCADE", MAGENTA);
    _display->drawText({-1, Y_CENTER - 6}, FONT_NORMAL, "GRAPHICAL LIBRARY", WHITE);
    _display->drawText({X_CENTER - 7, Y_CENTER - 4}, FONT_NORMAL, std::to_string(_displayCarousel.index + 1) + "/" + std::to_string(_displayCarousel.values.size()), YELLOW);
    _display->drawText(displayLeftCenter, FONT_NORMAL, "<", WHITE);
    _display->drawText({-1, Y_CENTER - 4}, FONT_NORMAL, getName(currentDisplay), currentDisplay == _selectedDisplayLib ? MAGENTA : WHITE);
    _display->drawText(displayRightCenter, FONT_NORMAL, ">", WHITE);
    _display->drawText({-1, Y_CENTER - 2}, FONT_NORMAL, "VALIDER", GREEN);
    _display->drawText({-1, Y_CENTER + 3}, FONT_NORMAL, "GAME", WHITE);
    _display->drawText({X_CENTER - 7, Y_CENTER + 4}, FONT_NORMAL, std::to_string(_gameCarousel.index + 1) + "/" + std::to_string(_gameCarousel.values.size()), YELLOW);
    _display->drawText(gameLeftCenter, FONT_NORMAL, "<", WHITE);
    _display->drawText({-1, Y_CENTER + 4}, FONT_NORMAL, getName(currentGame), currentGame == _selectedGameLib ? MAGENTA : WHITE);
    _display->drawText(gameRightCenter, FONT_NORMAL, ">", WHITE);
    _display->drawText({-1, Y_CENTER + 6}, FONT_NORMAL, "JOUER", GREEN);
    
    drawScores();
}

void Core::drawScores()
{
    int x = X_CENTER + 7;
    int y = Y_CENTER - 3;

    if (!_display)
        return;
    _display->drawText({x, y}, FONT_NORMAL, "-- Scores --", WHITE);
    y += 2;
    for (size_t i = 0; i < _scores.size() && i < 3; i++) {
        std::string line = std::to_string(i + 1) + ". " + _scores[i].name + " -> " + std::to_string(_scores[i].score) + "pts";
        _display->drawText({x, y}, FONT_NORMAL, line, YELLOW);
        y += 1;
    }
}

void Core::getScore()
{
    std::string name;
    int score;
    std::string gameName = getName(getCurrentItem(_gameCarousel)).substr(7);
    std::string filePath = "./assets/" + gameName + "/highScores.txt";
    std::ifstream file(filePath);

    _scores.clear();
    if (!file.is_open()) {
        std::filesystem::create_directories("./assets/" + gameName);
        std::ofstream newFile(filePath);
        if (newFile.is_open()) {
            newFile << "000 000\n";
            newFile << "000 000\n";
            newFile << "000 000\n";
        }
        _scores = {{"000", 0}, {"000", 0}, {"000", 0}};
        return;
    }
    while (file >> name >> score)
        _scores.push_back({name, score});
    while (_scores.size() < 3)
        _scores.push_back({"000", 0});
}

void Core::updateScores(int score)
{
    std::string gameName = getName(getCurrentItem(_gameCarousel)).substr(7);

    if (_name.empty())
        _name = "000";
    if (_scores.size() == 3 && score <= _scores[2].score)
        return;
    _scores.push_back({_name, score});
    std::sort(_scores.begin(), _scores.end(), [](const ScoreEntry &a, const ScoreEntry &b) {
        return a.score > b.score;
    });
    if (_scores.size() > 3)
        _scores.resize(3);

    std::string filePath = "./assets/" + gameName + "/highScores.txt";
    std::filesystem::create_directories("./assets/" + gameName);
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to write scores: " << filePath << std::endl;
        return;
    }
    for (const auto &entry : _scores)
        file << entry.name << " " << entry.score << "\n";
}

void Core::handleMenuClick(const pos &mouse)
{
    MenuButtons layout = getMenuButtons();

    if (isInside(mouse, layout.displayLeft.rect)) {
        moveLeft(_displayCarousel);
    } else if (isInside(mouse, layout.displayRight.rect)) {
        moveRight(_displayCarousel);
    } else if (isInside(mouse, layout.validateDisplay.rect)) {
        validateSelectedDisplay();
    } else if (isInside(mouse, layout.gameLeft.rect)) {
        moveLeft(_gameCarousel);
        getScore();
    } else if (isInside(mouse, layout.gameRight.rect)) {
        moveRight(_gameCarousel);
        getScore();
    } else if (isInside(mouse, layout.playButton.rect)) {
        startSelectedGame();
    }
}

void Core::validateSelectedDisplay()
{
    _selectedDisplayLib = getCurrentItem(_displayCarousel);
    if (_display)
        _display->closeWindow();
    switchDisplay(_selectedDisplayLib);
    if (_display && _display->createWindow() == 84)
        throw ArcadeException("Error createWindow");
}

void Core::startSelectedGame()
{
    _selectedGameLib = getCurrentItem(_gameCarousel);
    switchGame(_selectedGameLib);
    if (!_game || !_display)
        return;
    if (_display->loadTexture(_game->get_name()) == 84)
        return;
    if (_display->loadSound(_game->get_name()) == 84)
        return;
    _canStartGame = true;
}

void Core::changeDisplayInGame()
{
    moveRight(_displayCarousel);
    _selectedDisplayLib = getCurrentItem(_displayCarousel);

    if (_display)
        _display->closeWindow();

    switchDisplay(_selectedDisplayLib);
    if (!_display)
        return;

    if (_display->createWindow() == 84)
        return;

    if (_game) {
        _display->loadTexture(_game->get_name());
        _display->loadSound(_game->get_name());
    }
}

void Core::changeGameInGame()
{
    moveRight(_gameCarousel);
    _selectedGameLib = getCurrentItem(_gameCarousel);

    switchGame(_selectedGameLib);
    if (!_game || !_display)
        return;

    if (_display->loadTexture(_game->get_name()) == 84)
        return;
    if (_display->loadSound(_game->get_name()) == 84)
        return;
}

int Core::runGame()
{
    if (!_game || !_display)
        return 0;
    while (!_game->isOver()) {
        _display->clear();
        InputEvent input = _display->getInput();
        if (input.event == QUIT) {
            updateScores(_game->getScore());
            _display->closeWindow();
            return 1;
        }
        if (input.event == SWITCH_DISPLAY) {
            changeDisplayInGame();
            continue;
        }
        if (input.event == SWITCH_GAME) {
            changeGameInGame();
            updateScores(_game->getScore());
            continue;
        }
        if (input.event == CALL_MENU) {
            updateScores(_game->getScore());
            return 0;
        }
        if (input.event == RESTART_GAME) {
            switchGame(_selectedGameLib);
        }
        _game->update(input);
        for (const auto &s : _game->getSprites()) {
            if (s.name == "background")
                _display->drawBackground(s.name);
            else
                _display->drawSprite({s.x, s.y}, s.rotation, s.size, s.name);
        }
        for (const auto &t : _game->getTextes())
            _display->drawText({t.x, t.y}, t.size, t.text, t.color);
        _display->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    updateScores(_game->getScore());
    return 0;
}

void Core::runMenu()
{
    _canStartGame = false;
    getScore();
    _name = _display->loadName();
    if (_name.empty())
        return;

    while (true) {
        try {
            if (!_display)
                return;
            _display->clear();
            InputEvent input = _display->getInput();
            if (input.event == QUIT) {
                _display->closeWindow();
                return;
            }
            if (input.event == LEFT_CLICK)
                handleMenuClick(input.mouse);
            if (_canStartGame) {
                _canStartGame = false;
                if (runGame() == 1) {
                    _display->closeWindow();
                    return;
                }
            }
            if (!_display)
                return;
            drawMenu();
            _display->display();
        } catch (const ArcadeException &e) {
            std::cerr << "Menu Error: " << e.what() << std::endl;
            _canStartGame = false;
            _game = nullptr;
            _gameLoader.closeLib();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void Core::run(const std::string &lib_display)
{
    if (_displayLibs.empty()) {
        throw ArcadeException("No graphic lib found");
    }
    if (_gameLibs.empty()) {
        throw ArcadeException("No game lib found");
    }
    std::string truncatedLib = lib_display;
    if (lib_display.length() >= 2 && lib_display.compare(0, 2, "./") == 0)
        truncatedLib = lib_display.substr(2);
    if (std::find(_displayLibs.begin(), _displayLibs.end(), truncatedLib) == _displayLibs.end()) {
        if (std::find(_gameLibs.begin(), _gameLibs.end(), truncatedLib) != _gameLibs.end())
            throw ArcadeException("'" + lib_display + "' not a graphical library");
        throw ArcadeException("'" + lib_display + "' not a valid library");
    }
    initCarousels();
    _selectedDisplayLib = lib_display;
    _selectedGameLib = getCurrentItem(_gameCarousel);
    for (size_t i = 0; i < _displayCarousel.values.size(); i++) {
        if (_displayCarousel.values[i] == lib_display) {
            _displayCarousel.index = static_cast<int>(i);
            break;
        }
    }
    switchDisplay(_selectedDisplayLib);
    if (!_display)
        return;
    if (_display->createWindow() == 84) {
        throw ArcadeException("fail create window");
    }
    runMenu();
}
