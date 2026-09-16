# My World

> The World Is Mine — Epitech

A terrain editor built with C and CSFML: a wireframed, tile-based map that can be edited at runtime by raising, lowering or tilting its tiles.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Controls](#controls)
- [Editing tools](#editing-tools)
- [Map](#map)

## Overview

The map is made of square tiles of equal size, rendered with a 3D projection (isometric, parallel, or another projection). Tiles are textured, and the ground can be reshaped live: raising, lowering and tilting tiles to sculpt the terrain. The window closes through window events, and every animation runs independently of the machine's frame rate.

## Compilation

```bash
make          # builds the `my_world` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
./my_world    # start the project
```

## Controls

- **Mouse click** — select tiles on the map, interact with the toolbar
- **Keyboard** — used for editing interactions and navigation
- **Arrow keys** — move around the map
- **Scroll wheel / keyboard** — zoom in and out

The window stays between 800x600 and 1920x1080 pixels.

## Editing tools

Tiles are selected with the mouse, and at least three effects are available through a toolbar in the window, including altitude modification. Other toolbar effects include resetting tile altitude and adjusting the size of the area of effect. Hovering over toolbar elements shows help boxes, and buttons have idle, hover and clicked visual states.

The map size can be set through editable textboxes in the window.

## Map

The map can include additional layers (water, lava, etc.) on top of the terrain. Maps are saved in the `.legend` file format.