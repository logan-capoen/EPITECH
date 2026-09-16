# My FTP

> File Transfer Protocol Server — Epitech

An RFC959-compliant FTP server in C/C++, handling multiple clients concurrently over TCP sockets.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Usage](#usage)
- [Authentication](#authentication)
- [Concurrency](#concurrency)
- [Data transfers](#data-transfers)

## Overview

The server implements the FTP protocol as described in RFC959, including its request sequences, over TCP sockets.

## Compilation

```bash
make          # builds the `myftp` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

## Usage

```bash
./myftp --help
USAGE: ./myftp port path
port is the port number on which the server socket listens
path is the path to the home directory for the Anonymous user
```

## Authentication

The server supports an `Anonymous` account with an empty password.

## Concurrency

Several clients are handled at the same time using `poll` for command management and `fork` for data transfers; the server is single-threaded by design.

## Data transfers

Data transfers support both active and passive mode, as described in the FTP protocol.