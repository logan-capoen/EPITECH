# NanoTekSpice

> Digital Electronics — Epitech

A digital logic circuit simulator in C++: it builds a graph of electronic components from a configuration file and simulates it tick by tick, injecting and reading values interactively.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Configuration file](#configuration-file)
- [Components](#components)
- [Undefined state](#undefined-state)
- [Usage](#usage)
- [Examples](#examples)

## Overview

Circuits are made of chipsets — small components with input and output pins, built from boolean logic gates — linked together into a graph. The simulator loads such a graph from a configuration file, then lets the user set input values, run simulation ticks, and inspect the resulting state interactively.

## Compilation

```bash
make          # builds the `nanotekspice` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

Also buildable via CMake.

## Configuration file

A circuit file has two sections:

- `.chipsets:` — declares and names the components used in the circuit.
- `.links:` — declares links between component pins. Links are bidirectional.

```
# three inputs and gate
.chipsets:
input i0
input i1
input i2
4081 and0
output out
.links:
i0:1 and0:1
i1:1 and0:2
and0:3 and0:5
i2:1 and0:6
and0:4 out:1
```

Comments start with `#` and run to the end of the line.

## Components

Every component implements a common `IComponent` interface, letting simple and complex components (gates, counters, memory, ...) be combined the same way.

**Special components** — `input`, `output`, `true`, `false`, `clock`, `logger`

**Elementary gates** — `and`, `or`, `xor`, `not`

**Gate chipsets** — `4001` (four NOR), `4011` (four NAND), `4030` (four XOR), `4069` (six inverters), `4071` (four OR), `4081` (four AND)

**Advanced components** — `4008` (4-bit adder), `4013` (dual flip-flop), `4017` (10-bit Johnson decade counter), `4040` (12-bit counter), `4094` (8-bit shift register), `4512` (8-channel data selector), `4514` (4-bit decoder), `4801` (RAM), `2716` (ROM, initialized from `./rom.bin`)

The `logger` component appends the character computed from its inputs to `./log.bin` on the clock's positive edge, when not inhibited.

## Undefined state

Alongside `true` and `false`, every pin can hold a third, **undefined** state — used when a value hasn't been computed yet — so logic gates operate on a three-value truth table rather than plain booleans.

## Usage

```bash
./nanotekspice circuit_file.nts
```

Interactive commands (read from standard input, prompted with `> `):

- `exit` — close the program
- `display` — print the current tick and every input/output value, sorted by name
- `input=value` — set an input (or clock) to `0`, `1` or `U`
- `simulate` — run one simulation tick
- `loop` — repeatedly simulate and display until interrupted (`Ctrl+C`)

Reaching end of input (`Ctrl+D`) stops the program.

## Examples

```
$> cat -e or_gate.nts
.chipsets:$
input a$
input b$
4071 or$
output s$
.links:$
a:1 or:1$
b:1 or:2$
or:3 s:1$

$> ./nanotekspice or_gate.nts
> b=0
> a=1
> simulate
> display
tick: 1
input(s):
a: 1
b: 0
output(s):
s: 1
> exit
```

```
$> cat -e clock.nts
.chipsets:$
clock cl$
output out$
.links:$
out:1 cl:1$

$> ./nanotekspice clock.nts
> display
tick: 0
input(s):
cl: U
output(s):
out: U
> cl=0
> display
tick: 0
input(s):
cl: U
output(s):
out: U
> simulate
> display
tick: 1
input(s):
cl: 0
output(s):
out: 0
> simulate
> display
tick: 2
input(s):
cl: 1
output(s):
out: 1
> simulate
> simulate
> simulate
> display
tick: 5
input(s):
cl: 0
output(s):
out: 0
> (CTRL+D)
```