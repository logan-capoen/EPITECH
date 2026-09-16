# 42sh

> You Know the Answer — Epitech

A full Unix shell (`42sh`), based on TCSH, extending Minishell1 and Minishell2 with a wider range of interactive shell features.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Usage](#usage)
- [Features](#features)

## Overview

Building on top of the minishell, `42sh` follows `tcsh` as its reference for command syntax and compatibility. Error messages are written to the standard error output, and the exit code matches what `tcsh` would return.

## Compilation

```bash
make          # builds the `42sh` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

## Usage

```bash
./42sh
```

## Features

- **Inhibitors** — `' '`
- **Globbing** — `*`, `?`, `[`, `]`
- **Job control** — `&`, `fg`, `bg`
- **Backticks** — `` ` ``
- **Parentheses** — `(` and `)`
- **Variables** — local and environment
- **Special variables** — e.g. `term`, `precmd`, `cwdcmd`, `cwd`, `ignoreof`
- **History** — `!`
- **Aliases** — e.g. `alias ls "ls --color"`
- **Line edition** — multiline input, dynamic rebinding, auto-completion
- **Dynamic scripting**