/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** NCURSE
*/

#include "arcade_ncurses.hpp"
#include <fstream>

Ncurses::Ncurses()
{
    _name = "ncurses";
    _type = LibType::DISPLAY;
}

Ncurses::~Ncurses()
{
    if (_initialized)
        closeWindow();
}

int Ncurses::createWindow()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    mouseinterval(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
    if (has_colors()) {
        start_color();
        initColors();
    }
    int rows = 0;
    int cols = 0;
    getmaxyx(stdscr, rows, cols);
    _win = newwin(rows, cols, 0, 0);
    keypad(_win, TRUE);
    nodelay(_win, TRUE);
    wrefresh(_win);
    _initialized = true;
    return 0;
}

void Ncurses::closeWindow()
{
    if (_initialized) {
        if (_win) {
            delwin(_win);
            _win = nullptr;
        }
        endwin();
        _initialized = false;
    }
    return;
}

void Ncurses::clear()
{
    if (!_initialized || !_win)
        return;
    werase(_win);
    wrefresh(_win);
    return;
}

void Ncurses::display()
{
    if (!_initialized || !_win)
        return;
    wrefresh(_win);
    return;
}

InputEvent Ncurses::getInput()
{
    int ch = wgetch(_win);
 
    if (ch == ERR)
        return {UNKNOWN, {0, 0}};
    switch (ch) {
        case KEY_UP:
            return {UP_ARROW, {0, 0}};
        case KEY_DOWN:
            return {DOWN_ARROW, {0, 0}};
        case KEY_LEFT:
            return {LEFT_ARROW, {0, 0}};
        case KEY_RIGHT:
            return {RIGHT_ARROW, {0, 0}};
        case ' ':
            return {SPACE, {0, 0}};
        case 27:
            return {QUIT, {0, 0}};
        case 'm': case 'M':
            return {CALL_MENU, {0, 0}};
        case 'd': case 'D':
            return {SWITCH_DISPLAY, {0, 0}};
        case 'g': case 'G':
            return {SWITCH_GAME, {0, 0}};
        case 'r': case 'R':
            return {RESTART_GAME, {0, 0}};
        case KEY_MOUSE: {
            MEVENT me;
            if (getmouse(&me) == OK) {
                int rows;
                int cols;
                getmaxyx(_win, rows, cols);
                int gridX = (me.x) * 30 / cols + 1;
                int gridY = (me.y) * 20 / rows + 1;
                if ((me.bstate & BUTTON1_PRESSED))
                    return {LEFT_CLICK, {gridX, gridY}};
                if ((me.bstate & BUTTON3_PRESSED))
                    return {RIGHT_CLICK, {gridX, gridY}};
            }
            break;
        }
        default:
            break;
    }
    return {UNKNOWN, {0, 0}};
}

void Ncurses::drawText(pos position, float size, std::string str, Color color)
{
    (void)size;
    if (!_initialized)
        return;
    int rows;
    int cols;
    getmaxyx(_win, rows, cols);
    int row = position.y * rows / 20;
    int col;
    if (position.x == -1)
        col = (cols - static_cast<int>(str.size())) / 2;
    else
        col = position.x * cols / 30;
    if (col < 0)
        col = 0;
    auto it = _colorPairs.find(color);
    if (it != _colorPairs.end())
        wattron(_win, COLOR_PAIR(it->second));
    mvwprintw(_win, row, col, "%s", str.c_str());
    if (it != _colorPairs.end())
        wattroff(_win, COLOR_PAIR(it->second));
}

void Ncurses::drawSprite(pos position, int rotation, float size, std::string name)
{
    (void)rotation;
    (void)size;
    if (!_initialized)
        return;
    int rows, cols;
    getmaxyx(_win, rows, cols);
    int row = position.y * rows / 20;
    int col = position.x * cols / 30;
    auto it = _asciiSprites.find(name);
    if (it == _asciiSprites.end()) {
        mvwprintw(_win, row, col, "?");
        return;
    }
    mvwprintw(_win, row, col, "%c", it->second);
    return;
}

int Ncurses::loadTexture(std::string game)
{
    std::string path = "assets/" + game + "/ascii";

    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path))
        throw ArcadeException("ascii assets directory not found: " + path);
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (!entry.is_regular_file())
            continue;
        std::ifstream file(entry.path());
        if (!file.is_open()) {
            throw ArcadeException("failed to open ascii sprite file: " + entry.path().string());
            continue;
        }
        char c;
        if (!(file >> c)) {
            throw ArcadeException("empty sprite file: " + entry.path().string());
            continue;
        }
        _asciiSprites[entry.path().stem().string()] = c;
    }
    return 0;
}

int Ncurses::loadSound(std::string game)
{
    return 0;
}

int Ncurses::playSound(std::string sound_name)
{
    return 0;
}

void Ncurses::initColors()
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_CYAN, COLOR_BLACK);
    _colorPairs.insert({RED, 1});
    _colorPairs.insert({GREEN, 2});
    _colorPairs.insert({BLUE, 3});
    _colorPairs.insert({YELLOW, 4});
    _colorPairs.insert({BLACK, 5});
    _colorPairs.insert({WHITE, 6});
    _colorPairs.insert({MAGENTA, 7});
    _colorPairs.insert({CYAN, 8});
}

std::string Ncurses::loadName()
{
    std::string name;
    int ch;

    nodelay(_win, TRUE);
    while (true) {
        ch = wgetch(_win);
        if (ch != ERR) {
            if (ch == 27)
                return "";
            if (ch == '\n' || ch == KEY_ENTER || ch == 10 || ch == 13) {
                return name.empty() ? "aaa" : name;
            }
            else if ((ch == KEY_BACKSPACE || ch == 127 || ch == '\b') && !name.empty()) {
                name.pop_back();
            }
            else if (ch >= 32 && ch < 128 && name.size() < 20) {
                name += static_cast<char>(ch);
            }
        }
        this->clear();
        drawText({POS_CENTER.x - 8, POS_CENTER.y - 4}, 1.0f, "Choisissez votre nom :", WHITE);
        drawText({POS_CENTER.x - 8, POS_CENTER.y - 3}, 1.0f, name + "|", CYAN);
        this->display();
        napms(10); 
    }
    return name.empty() ? "Player1" : name;
}

std::tuple<int, int> Ncurses::recoverWindowSize()
{
    int rows = 0;
    int cols = 0;

    if (_win)
        getmaxyx(_win, rows, cols);
    return {cols, rows};
}

void Ncurses::drawBackground(std::string background_name)
{
    return;
}

extern "C" ILib* entryPoint()
{
    return new Ncurses();
}