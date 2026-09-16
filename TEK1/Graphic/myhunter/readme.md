# My Hunter

> The Duck Hunt Legacy — Epitech

A small Duck Hunt–inspired video game written in C with the CSFML library. The player is a hunter who shoots ducks flying across the screen.

## Table of Contents

- [Gameplay](#gameplay)
- [Compilation](#compilation)
- [Usage](#usage)
- [Features](#features)
- [Assets](#assets)

## Gameplay

Ducks appear on screen and move across it. The player aims with the mouse and clicks to shoot them. The window closes cleanly through window events (e.g. clicking the close button).

## Compilation

```bash
make          # builds the `my_hunter` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
./my_hunter    # start the project
```

Bonus files (and a potential dedicated Makefile) are kept in a `bonus/` directory.

## Usage

```bash
./my_hunter
./my_hunter -h   # shows a short description of the game and the available inputs
```

Controls:

- **Mouse click** — shoot at the ducks

## Features

- Animated sprites, rendered from sprite sheets, for the ducks and other game elements.
- Moving elements (translation, rotation and/or scaling) driven by `sfClock`, so animations and movement stay consistent regardless of the machine's speed.
- A window sized between 800x600 and 1920x1080, with a capped frame rate to keep the game smooth.
- Mouse click handling to shoot ducks, and window-event handling to close the game.

## Assets

Images and sound files are kept lightweight (compressed formats, reasonable resolutions) to keep the repository's total size small.