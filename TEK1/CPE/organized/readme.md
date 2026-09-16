# Organized

> Elementary Programming in C — Epitech

A shell-driven workshop manager that stores hardware in a linked list and lets you add, delete, display and sort it by type, name or id.

## Table of Contents

- [Goal](#goal)
- [Compilation](#compilation)
- [Materials](#materials)
- [Shell](#shell)
- [Add](#add)
- [Delete](#delete)
- [Display](#display)
- [Sort](#sort)
- [Testing](#testing)

## Goal

The workshop is a mess of hardware that needs to be stored, handled and sorted efficiently, even when dealing with a large amount of items. The project has two parts:

- storing and handling hardware
- sorting it by tags

## Compilation

```bash
make          # builds the `organized` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

## Materials

All hardware belongs to one of 5 categories:

- **Actuators** — buttons, levers, ...
- **Devices** — radios, watches, recorders, ...
- **Processors** — intel, amd, ...
- **Sensors** — movement sensor, sound sensor, thermal sensor, ...
- **Wires** — type-c, hdmi, jack, ...

Every material has a type, a name and a unique id. The first registered id is `0` and increments with each new material.

## Shell

The workshop is driven through a shell provided as `libshell.a` and `shell.h`:

```c
int workshop_shell(void *data);
```

`shell.h`:

```c
int add(void *data, char **args);
int del(void *data, char **args);
int sort(void *data, char **args);
int disp(void *data, char **args);
int workshop_shell(void *data);
```

The `exit` command is already implemented. `add`, `del`, `disp` and `sort` must be implemented. `libshell.a` and `shell.h` must be included in the delivery, as the tester does not provide them.

## Add

```
Workshop >> add WIRE usb
WIRE n°0 - "usb" added.
Workshop >> add ACTUATOR button, DEVICE recorder
ACTUATOR n°1 - "button" added.
DEVICE n°2 - "recorder" added.
```

Hardware is stored as a linked list, in reverse insertion order: adding items #0, #1 and #2 stores them as #2, #1, #0.

## Delete

```
Workshop >> del 1
ACTUATOR n°1 - "button" deleted.
Workshop >> del 0, 2
WIRE n°0 - "usb" deleted.
DEVICE n°2 - "recorder" deleted.
```

The `args` parameter holds the command's arguments. Any malformed command must stop the program and return exit code 84.

## Display

```
Workshop >> disp
DEVICE n°2 - "recorder"
ACTUATOR n°1 - "button"
WIRE n°0 - "usb"
```

## Sort

Hardware can be sorted by 3 tags:

- `TYPE` (ascii)
- `NAME` (ascii)
- `ID` (ascending, numeric)

Each tag can take a `-r` flag to reverse its order.

```
Workshop >> sort NAME
Workshop >> disp
ACTUATOR n°1 - "button"
DEVICE n°2 - "recorder"
WIRE n°0 - "usb"
```

Several tags can be combined; hardware is then sorted by the first tag, and by the following ones to break ties:

```
Workshop >> sort TYPE -r NAME ID -r
Workshop >> disp
WIRE n°1 - "type-c"
WIRE n°2 - "usb"
WIRE n°0 - "usb"
ACTUATOR n°3 - "button"
```

## Testing

The test server feeds pre-filled prompt files instead of typing commands one by one:

```
add WIRE a, WIRE b, WIRE c, WIRE d, SENSOR e, SENSOR f, WIRE a
disp
sort TYPE -r
disp
exit
```

```bash
cat example_test | ./organized
```