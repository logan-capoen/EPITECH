# My Radar

> The Air Traffic Control Panel — Epitech

A 2D air traffic simulation panel, rendered with CSFML, displaying aircrafts and control towers moving and interacting according to a script file.

## Table of Contents

- [Simulation](#simulation)
- [Compilation](#compilation)
- [Usage](#usage)
- [Script format](#script-format)
- [Controls](#controls)
- [Rendering](#rendering)

## Simulation

The panel simulates two kinds of entities:

- **Aircrafts** — fly in a straight line, at a constant speed, from a departure point to an arrival point. They appear on the panel when they take off and disappear when they land. Two aircrafts colliding are destroyed and removed from the panel, unless the collision happens inside a control tower's area, in which case they simply continue on their way.
- **Control towers** — static entities, present on the panel from launch, each with a circular control area in which aircrafts can cross paths safely.

## Compilation

```bash
make          # builds the `my_radar` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

Bonus files (and a potential dedicated Makefile) are kept in a `bonus/` directory.

## Usage

```bash
./my_radar path_to_script
./my_radar -h
```

```
$> ./my_radar; echo $?
./my_radar: bad arguments: 0 given but 84 is required
retry with -h
84

$> ./my_radar -h
Air traffic simulation panel
USAGE
./my_radar [OPTIONS] path_to_script
path_to_script The path to the script file.
OPTIONS
-h print the usage and quit.
USER INTERACTIONS
'L' key enable/disable hitboxes and areas.
'S' key enable/disable sprites.
```

The window opens at 1920x1080 and closes through window events. An error message is displayed if the script file is missing or malformed.

## Script format

The script describes every entity of the simulation, one per line, separated by `#cr`, with fields separated by tabs or spaces.

**Aircraft** — `A departure_x departure_y arrival_x arrival_y speed delay`

- departure and arrival coordinates (integers)
- speed, in pixels per second
- delay, in seconds, before takeoff

**Control tower** — `T x y radius`

- coordinates of the tower
- radius of its control area

```
$> cat scripts/example.rdr
A 815 321 1484 166 5 0
A 1589 836 811 936 2 0
A 202 894 103 34 3 0
T 93 47 19
T 49 56 25
```

## Controls

- **L** — toggle hitbox and control-area visibility
- **S** — toggle entity sprite visibility

A timer, in seconds, is displayed in the top-right corner of the window and the simulation stops once every aircraft has landed or been destroyed.

## Rendering

- Aircrafts have 20x20 square hitboxes, axis-aligned with their sprite.
- Control towers have circular control areas.
- Aircrafts and control towers are displayed using sprites, with hitboxes and control areas drawn alongside them.