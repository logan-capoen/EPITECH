# Robot Factory

> Elementary Programming in C — Epitech

An assembler that translates Corewar champion plans, written in a human-readable assembly language (`.s` files), into bytecode (`.cor` files) that the Corewar virtual machine can execute.

## Table of Contents

- [Goal](#goal)
- [Compilation](#compilation)
- [Project parts](#project-parts)
- [op.c and op.h](#opc-and-oph)
- [Champions](#champions)
- [Usage](#usage)
- [Parameters](#parameters)
- [Example](#example)
- [Transcription](#transcription)

## Goal

The Corewar tournament is a game in which several programs, called Champions, fight to be the last one alive by sharing and fighting over memory in a virtual machine. Robot Factory is the assembler that turns a champion's plans, written in assembly, into a tournament-ready bytecode file.

## Compilation

```bash
make          # builds the `robot-factory` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

## Project parts

The full Corewar project is split into three separate parts, with only one to develop here:

- **Champions** (given) — `.s` files written in the virtual machine's assembly language, describing when a champion attacks, defends, or signals it is still alive.
- **The Assembler (Robot Factory)** — translates champion source files (`.s`) into bytecode (`.cor`), byte by byte, understandable by the Corewar virtual machine.
- **The Virtual Machine (Corewar, the next project)** — executes the translated instructions of every champion in a shared memory arena.

## op.c and op.h

Two files, `op.c` and `op.h`, are provided and must be integrated into the delivery directory. Every value written in UPPERCASE in this project refers to a variable defined in these files. They may be modified as needed. Coding style is checked on all delivered files, including `op.c` and `op.h`.

## Champions

A champion (`.s` file) looks like this:

```
.name "Jon Snow"
.comment "Winter is coming"
sti r1, %:crow, %1
crow:live %234
ld %0, r3
zjmp %:crow
```

- **Header** — a `.name` and a `.comment`, stored in a binary header starting with the `COREWAR_EXEC_MAGIC` magic number once compiled.
- **Body** — a succession of instructions, each made of an opcode (e.g. `sti`, `live`, `ld`, `zjmp`) and its parameters.
- **Labels** — strings composed of `LABEL_CHARS` characters, followed by `LABEL_CHAR` (e.g. `crow:`), used as coordinate points to jump to or store data relative to.

Champions are provided as attachments and do not need to be written for this project.

## Usage

```bash
./robot-factory file_name[.s]
```

Converts `file_name.s` into `file_name.cor`, an executable for the virtual machine.

## Parameters

An instruction can take from 0 to `MAX_ARGS_NUMBER` parameters, of 3 possible types:

- **Register** — one of `r1` to `rREG_NUMBER` (`r1` holds the champion's identifier).
- **Direct** — the `DIRECT_CHAR` character followed by a value or a `LABEL_CHAR`-prefixed label (e.g. `%4` or `%:label`).
- **Indirect** — a value or label representing the value found at the parameter's address, relative to the PC.

Each instruction is encoded as:

1. **Opcode** — the instruction code, found in `op_tab` (`op.h`), written on one byte.
2. **Coding byte** — describes the type of each parameter on 2 bits (`01` register, `10` direct, `11` indirect, `00` otherwise), omitted for `live`, `zjmp`, `fork` and `lfork`.
3. **Parameters** — written directly: 1 byte for a register, `DIR_SIZE` bytes for a direct, `IND_SIZE` bytes for an indirect. Indexed parameters are always written on `IND_SIZE` bytes, even when direct.

The virtual machine is **big endian**, which affects the byte order used when transcribing values.

## Example

```
$> ./robot-factory jon.s && hexdump -C jon.cor
00000000  00 ea 83 f3 4a 6f 6e 20 53 6e 6f 77 00 00 00 00  |....Jon Snow....|
00000010  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |................|
*
00000080  00 00 00 00 00 00 00 00 00 00 00 16 57 69 6e 74  |............Wint|
00000090  65 72 20 69 73 20 63 6f 6d 69 6e 67 00 00 00 00  |er is coming....|
000000a0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |................|
*
00000890  0b 68 01 00 07 00 01 01 00 00 00 ea 02 90 00 00  |.h..............|
000008a0  00 00 03 09 ff f4                                |......|
```

- `0b 68 01 00 07 00 01` → `sti r1, %:crow, %1`
- `01 00 00 00 ea` → `live %234`
- `02 90 00 00 00 00 03` → `ld %0, r3`
- `09 ff f4` → `zjmp %:crow` (no coding byte, indexed direct parameter on `IND_SIZE` bytes)

## Transcription

- The header (name and comment) is transcribed first, using the `header_t` structure from `op.h`, before any instruction.
- Comparing a `.s` file to its compiled `.cor` file byte by byte (with `hexdump -C`) is the most reliable way to understand edge cases in the transcription.