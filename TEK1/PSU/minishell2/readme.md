# Minishell2

> This Isn't Flying. This Is Falling With Style! — Epitech

An extension of Minishell1 (`mysh`) adding command chaining with semicolons, pipes, and input/output redirections.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Usage](#usage)
- [Examples](#examples)

## Overview

On top of the base command interpreter, the shell handles:

- **Semicolons (`;`)** — chaining several commands on a single line.
- **Pipes (`|`)** — passing the output of one command as the input of the next.
- **Redirections** — `>`, `<`, `>>`, `<<`.

Operator priority between these is correctly handled.

## Compilation

```bash
make          # builds the `mysh` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

## Usage

```bash
./mysh
echo "command" | ./mysh
```

## Examples

```
$> ./mysh
$> ls -l; ls -l | wc -l
total 4
drwxr-xr-x 2 johan johan 4096 Mar 17 16:28 tata
-rw-r--r-- 1 johan johan 0 Mar 17 16:28 toto
3
```

```
$> ./mysh
$> mkdir test ; cd test ; ls -a ; ls | cat | wc -c > tutu ; cat tutu
. ..
5
2
```