# Setting Up

> Elementary Programming in C — Epitech

A dynamic-programming program that finds the largest free square area on a board, avoiding obstacles.

## Table of Contents

- [Goal](#goal)
- [Compilation](#compilation)
- [Usage](#usage)
- [File format](#file-format)
- [Generating a board](#generating-a-board)
- [Examples](#examples)

## Goal

Given a board, the program must find the largest possible square made only of free spaces, avoiding obstacles, and print the board with the found square marked. If several squares of the same (largest) size exist, the highest one is chosen; if there are still several, the leftmost one is chosen.

## Compilation

```bash
make          # builds the `setting_up` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

## Usage

The board can be obtained in two ways:

- read from a file passed as the program's argument
- generated from given parameters

```bash
./setting_up file_name
./setting_up size pattern
```

## File format

```bash
./setting_up example_file
```

A board file is valid if:

- its first line contains only the number of lines on the board
- `.` (empty space) and `o` (obstacle) are the only two characters allowed on the other lines
- all lines have the same length (except the first one)
- the file contains at least one line
- each line is terminated by `\n`

The program prints the board with the cells of the largest found square replaced by `x`.

## Generating a board

The second way to obtain a board is to generate one from:

- a number, giving both the width and height of the board
- a pattern, repeated line by line along the board

The solved board (with the largest square marked) is printed directly.

## Examples

```
$> cat -e example_file
9$
...........................$
....o......................$
............o..............$
...........................$
....o......................$
..............o............$
...........................$
......o..............o.....$
..o.......o................$
```

Classic execution:

```
$> ./setting_up example_file | cat -e
.....xxxxxxx................$
....oxxxxxxx................$
.....xxxxxxxo...............$
.....xxxxxxx................$
....oxxxxxxx................$
.....xxxxxxx...o............$
.....xxxxxxx................$
......o...............o.....$
..o.......o.................$
```

Generating execution:

```
$> ./setting_up 6 "..o.." | cat -e
..oxx.$
.o.xx.$
o....o$
....o.$
...o..$
..o...$
```