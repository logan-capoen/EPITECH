/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** Common
*/

#ifndef COMMON_HPP_
#define COMMON_HPP_

#define WINDOW_WIDTH 30
#define WINDOW_HEIGHT 20

#define POS_TOP_LEFT pos {0, 0}
#define POS_TOP_CENTER pos {WINDOW_WIDTH / 2, 0}
#define POS_TOP_RIGHT pos {WINDOW_WIDTH, 0}
#define POS_CENTER_LEFT pos {0, WINDOW_HEIGHT / 2}
#define POS_CENTER pos {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}
#define POS_CENTER_RIGHT pos {WINDOW_WIDTH, WINDOW_HEIGHT / 2}
#define POS_BOTTOM_LEFT pos {0, WINDOW_HEIGHT}
#define POS_BOTTOM_CENTER pos {WINDOW_WIDTH / 2, WINDOW_HEIGHT}
#define POS_BOTTOM_RIGHT pos {WINDOW_WIDTH, WINDOW_HEIGHT}

#define X_LEFT 0
#define X_CENTER WINDOW_WIDTH / 2
#define X_RIGHT WINDOW_WIDTH
#define Y_TOP 0
#define Y_CENTER WINDOW_HEIGHT / 2
#define Y_BOTTOM WINDOW_HEIGHT

#define PADDING_TINY 0.1
#define PADDING_MEDIUM_TINY 0.125
#define PADDING_MEDIUM 0.25
#define PADDING_NORMAL_TINY 0.5
#define PADDING_NORMAL_MEDIUM 1
#define PADDING_NORMAL 1.5
#define PADDING_LARGE_TINY 2
#define PADDING_LARGE_MEDIUM 2.5
#define PADDING_LARGE 3

#define FONT_TINY 0.25
#define FONT_MEDIUM_TINY 0.3
#define FONT_MEDIUM 0.5
#define FONT_NORMAL_TINY 0.8
#define FONT_NORMAL_MEDIUM 1
#define FONT_NORMAL 1.3
#define FONT_LARGE_TINY 1.5
#define FONT_LARGE_MEDIUM 2
#define FONT_LARGE 2.5

#define FONT_PATH "assets/font/Nasa21.ttf"

struct pos {
    int x;
    int y;
};

struct Rect {
    int x;
    int y;
    int width;
    int height;
};

enum EventType {
    UP_ARROW,
    DOWN_ARROW,
    LEFT_ARROW,
    RIGHT_ARROW,
    LEFT_CLICK,
    RIGHT_CLICK,
    SWITCH_DISPLAY,
    SWITCH_GAME,
    RESTART_GAME,
    CALL_MENU,
    ENTER,
    SPACE,
    QUIT,
    ROAR,
    UNKNOWN
};

struct InputEvent {
    EventType event = UNKNOWN;
    pos mouse = {0, 0};
};

enum LibType {
    GAME,
    DISPLAY,
    UNDEFINE
};

enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
    WHITE,
    MAGENTA,
    CYAN
};

#endif /* !COMMON_HPP_ */
