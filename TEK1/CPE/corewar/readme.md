# Corewar

> Elementary Programming in C — Epitech

A virtual machine in which several programs, called Champions, fight over shared memory until only one remains capable of proving it is still alive.

## Table of Contents

- [Goal](#goal)
- [Compilation](#compilation)
- [Project parts](#project-parts)
- [op.c and op.h](#opc-and-oph)
- [Usage](#usage)
- [Virtual machine](#virtual-machine)
- [Output](#output)
- [Scheduling](#scheduling)
- [Dump example](#dump-example)

## Goal

Corewar is a computer simulation in which several Champions, written in an assembly language specific to this project's virtual machine, share a memory zone and fight for survival by all means available. The last champion able to execute the `live` instruction is declared the winner.

## Compilation

```bash
make          # builds the `corewar` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

Bonus files (and a potential dedicated Makefile) must be placed in a `bonus/` directory.

## Project parts

The project is split into three parts, only one of which is to be developed:

- **Champions** (given) — `.s` files written in the virtual machine's assembly language, describing when a champion attacks, defends, or signals it is still alive.
- **The Assembler** — translates champion source files (`.s`) byte by byte into the language the Corewar virtual machine understands.
- **The Virtual Machine** — executes the translated instructions of every champion in a shared memory arena, respecting timing and cycle constraints.

## op.c and op.h

Two files, `op.c` and `op.h`, are provided and must be integrated into the delivery directory. Every value written in UPPERCASE in this project refers to a variable defined in these files. Coding style is checked on all delivered files, including `op.c` and `op.h`.

## Usage

```bash
./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...
```

| Option              | Description                                                                                                   |
|---------------------|-----------------------------------------------------------------------------------------------------------------|
| `-dump nbr_cycle`   | Dumps the state of the virtual machine after `nbr_cycle` executions                                             |
| `-n prog_number`    | Sets the next program's number (default: first free number, in parameter order)                                |
| `-a load_address`   | Sets the next program's loading address (default: addresses spread out as far apart as possible, modulo `MEM_SIZE`) |

## Virtual machine

The machine is a multi-program machine. Each program has:

- **`REG_NUMBER` registers** of `REG_SIZE` bytes each (fast-access memory embedded in the processor).
- **A PC (Program Counter)** — holds the address of the next instruction to decode and execute.
- **A `carry` flag** — set to 1 if and only if the last operation returned zero.

The machine runs every champion given as a parameter and checks that each one calls `live` at least once every `CYCLE_TO_DIE` cycles. Once `NBR_LIVE` calls to `live` have occurred with several processes still alive, `CYCLE_TO_DIE` is decreased by `CYCLE_DELTA`. This repeats until no process is left alive. The last champion to call `live` wins.

The virtual machine must be able to build and run without a graphical environment.

## Output

Each player is assigned a number, given to their program in register `r1` at startup (every other register starts at 0, except the PC).

- Every time the `live` instruction is executed:
  `The player NB_OF_PLAYER(NAME_OF_PLAYER) is alive.`
- When a player wins:
  `The player NB_OF_PLAYER(NAME_OF_PLAYER) has won.`

These messages must match exactly for the autograder to pass.

## Scheduling

Each instruction is considered to execute entirely at the end of its last cycle, and the program waits throughout its whole duration. Instructions starting on the same cycle execute in ascending order of program number.

## Dump example

```
Cycle: 10
Registers:
Abel(1): alive
r1 : 00000001 r2 : 00000000 r3 : 00000000 r4 : 00000000 r5 : 00000000 r6 : 00000000
r7 : 00000000 r8 : 00000000 r9 : 00000000 r10: 00000000 r11: 00000000 r12: 00000000
r13: 00000000 r14: 00000000 r15: 00000000 r16: 00000000
PC : 00000000 carry: 0
Tyron(2): alive
r1 : 00000002 r2 : 00000000 r3 : 00000000 r4 : 00000000 r5 : 00000000 r6 : 00000000
r7 : 00000000 r8 : 00000000 r9 : 00000000 r10: 00000000 r11: 00000000 r12: 00000000
r13: 00000000 r14: 00000000 r15: 00000000 r16: 00000000
PC : 00000C00 carry: 0
Memory:
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F
...
```

The `-dump` flag is mandatory for the correction, and the whole memory must be printed (the example above only shows an excerpt).
