# A-maze-d

> Elementary Programming in C — Epitech

A C program that moves one or several robots through a maze, from the entrance (`##start`) to the exit (`##end`), taking the fastest possible path while avoiding collisions between robots.

## Table of Contents

- [Goal](#goal)
- [Compilation](#compilation)
- [Usage](#usage)
- [Input format](#input-format)
- [Output format](#output-format)
- [Example](#example)
- [Movement rules](#movement-rules)

## Goal

The program reads a maze description from its standard input:

- the number of robots at the entrance
- all the rooms and their positions
- the tunnels linking the rooms together

It must first check whether the terrain configuration is valid, then compute the shortest route(s) to get as many robots as possible to the exit in as few laps as possible.

## Compilation

```bash
make          # builds the `amazed` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

Bonus files (and a potential dedicated Makefile) must be placed in a `bonus/` directory.

## Usage

The maze is read from standard input:

```bash
./amazed < labyrinth
```

## Input format

```
34
##start
1 23 3
2 16 7
#comment
3 16 3
...
##end
0 9 5
0-4
0-6
1-3
...
```

- The first line gives the number of robots.
- Each room is defined by a name and coordinates (whole numbers).
- `##start` indicates that the next room is the maze entrance.
- `##end` indicates that the next room is the maze exit.
- Lines starting with `#` are comments; lines starting with `##` are commands (unknown commands are ignored).
- Tunnels are described as `roomA-roomB`.
- Room names are not necessarily numbers, and not necessarily consecutive.
- The first non-conforming or empty line stops the parsing: the program must still have printed every line it correctly processed before the error occurred.

## Output format

The program prints, in this order, the following sections (each preceded by its comment header):

```
#number_of_robots
#rooms
#tunnels
#moves
```

Each lap of movement is represented by a series of `Pn-r`, where `n` is the robot's number and `r` the name of the room it moves into.

## Example

```
$> cat labyrinth
3
##start
0 1 0
##end
1 13 0
2 5 0
3 9 0
0-2
2-3
3-1

$> ./amazed < labyrinth
#number_of_robots
3
#rooms
##start
0 1 0
##end
1 13 0
2 5 0
3 9 0
#tunnels
0-2
2-3
3-1
#moves
P1-2
P1-3 P2-2
P1-1 P2-3 P3-2
P2-1 P3-3
P3-1
```

## Movement rules

- At the start of the game, all robots are in the entrance room.
- On each lap, every robot can move at most once, through a tunnel, provided the destination room is free.
- A room can hold only one robot at a time, except `##start` and `##end`, which can hold as many as needed.
- Each robot must take the shortest route, without walking on its peers or causing a traffic jam.
