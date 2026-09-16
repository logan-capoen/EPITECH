##
## EPITECH PROJECT, 2026
## G-OOP-400-LIL-4-1-arcade-6
## File description:
## Makefile
##

CC = clang++
CFLAGS  = -Wall -Wextra -Werror -ICore -IInterface -ICommon -IExceptions -IParse
SOFLAGS = -shared -fPIC -IInterface -ICommon -IExceptions -IParse -lsfml-graphics -lsfml-audio -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lncurses

GAME_SRCS = \
	Games_libraries/arcade_snake.cpp \
	Games_libraries/arcade_centipede.cpp

GAME_SO   = $(GAME_SRCS:Games_libraries/%.cpp=lib/%.so)

GRAPH_SRCS = \
	Graphics_libraries/arcade_sfml.cpp \
	Graphics_libraries/arcade_ncurses.cpp \
	Graphics_libraries/arcade_sdl2.cpp

GRAPH_SO = $(GRAPH_SRCS:Graphics_libraries/%.cpp=lib/%.so)

CORE_SRC = main.cpp \
    Core/Core.cpp \
    Interface/ALib.cpp \
	Common/LibLoader.cpp \
	Parse/Parse.cpp

ALIB_SRC = Interface/ALib.cpp
AGAME_SRC = Interface/AGame.cpp
ADisplay_SRC = Interface/ADisplay.cpp

BIN = arcade

all: core games graphicals
core: $(BIN)
games: $(GAME_SO)
graphicals: $(GRAPH_SO)

lib:
	mkdir -p lib

$(GAME_SO): lib/%.so: Games_libraries/%.cpp $(ALIB_SRC) | lib
	$(CC) $(SOFLAGS) -o $@ $^

$(GRAPH_SO): lib/%.so: Graphics_libraries/%.cpp $(ALIB_SRC) | lib
	$(CC) $(SOFLAGS) -o $@ $^

$(BIN): $(CORE_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(GAME_SO)
	rm -f $(GRAPH_SO)

fclean: clean
	rm -f $(BIN)

re: fclean all
