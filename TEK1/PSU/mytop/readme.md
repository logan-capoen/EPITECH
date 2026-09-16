# My_top

> Let's Take a Look at Unix Processes! — Epitech

A reimplementation of the `top` command: an ncurses-based terminal UI monitoring system information and live process statistics.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Usage](#usage)
- [System information](#system-information)
- [Process information](#process-information)
- [Keyboard interactions](#keyboard-interactions)

## Overview

The program retrieves system information and process statistics directly (no `system`, `exec*`, `popen`, `getloadavg`, `getrusage`, `getrlimit`, or similar helper functions), and displays them in an ncurses window: a system information section at the top, and a live table of process statistics below.

## Compilation

```bash
make          # builds the `my_top` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

## Usage

```bash
./my_top [-U username] [-d seconds[.cents]] [-n frames]
```

- `-U username` — only show processes owned by `username`
- `-d seconds[.cents]` — delay between refreshes, in seconds (default: `3.0`)
- `-n frames` — number of frames to display before exiting (default: unlimited)

```bash
$> ./my_top -U clery -n 10 -d 1.5
$> ./my_top -U clery
```

## System information

The upper section displays:

- time of day
- uptime (e.g. `up 2 days, 30 min` after 48h30, `up 2:30` if hours but no days, `up 30 min` if under an hour)
- number of users currently logged in
- load average
- task counts: total, running, sleeping, stopped, zombie
- CPU usage
- memory usage
- swap usage

## Process information

The lower section displays, per process:

- PID
- USER owning the process
- PRiority
- NIce value
- VIRTual memory size
- RESident memory size
- SHaRed memory size
- process status
- CPU percent usage
- MEMory percent usage
- TIME since the process started
- COMMAND name

Every column header matches a corresponding value, aligned underneath it. The system statistics section uses the same wording as `top` for anything that isn't a value.

## Keyboard interactions

- **E** — cycle through memory units for processes (KiB, MiB, GiB, TiB, PiB)
- **Shift+E** — cycle through memory units for the system section (KiB, MiB, GiB, TiB, PiB, EiB)
- **↑ / ↓** — scroll through the process list
- **K** — open a prompt to send a signal to a process (defaults to the highest process in the list and the `SIGTERM` signal; no line editing provided)