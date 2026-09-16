# My_ls

> List Directory Content — Epitech

A reimplementation of the `ls` command: lists directory contents with support for the `-alRdt` options.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Usage](#usage)
- [Examples](#examples)

## Overview

```
./my_ls [OPTION]... [FILE]...
```

Supported options: `-a`, `-l`, `-R`, `-d`, `-t`, given in any order and combinable (e.g. `-alRdt`, `-ltaRd`, or `-d -t -a -d -l -R` all behave the same way). File arguments, if any, are handled after the options.

## Compilation

```bash
make          # builds the `my_ls` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

## Usage

```bash
./my_ls file1
./my_ls -l file1 file2
./my_ls file1 file2 /dev
./my_ls -l -a /usr/sbin
```

## Examples

```
$> ./my_ls .
bin include logs Makefile obj src tests todo
```

```
$> ./my_ls -ld /tmp
drwxrwxrwt 20 root root 20480 Sep 26 13:44 /tmp
```

```
$> ./my_ls -l /dev | tail -n 10
crw-rw---- 1 root tty 7, 71 Sep 26 09:49 vcsu7
drwxr-xr-x 2 root root 60 Sep 26 09:49 vfio
crw------- 1 root root 10, 127 Sep 26 09:49 vga_arbiter
crw------- 1 root root 10, 137 Sep 26 09:49 vhci
crw-rw---- 1 root kvm 10, 238 Sep 26 09:49 vhost-net
crw-rw---- 1 root kvm 10, 241 Sep 26 09:49 vhost-vsock
crw-rw---- 1 root video 81, 0 Sep 26 09:49 video0
crw-rw---- 1 root video 81, 1 Sep 26 09:49 video1
crw-rw-rw- 1 root root 1, 5 Sep 26 09:49 zero
crw------- 1 root root 10, 249 Sep 26 09:49 zfs
```

```
$> ./my_ls -lR
.:
total 32
drwxr-xr-x 2 user group 4096 Feb 7 2025 bin
drwxr-xr-x 2 user group 4096 Nov 6 2022 include
drwxr-xr-x 2 user group 4096 Nov 6 2022 logs
-rw-r--r-- 1 user group 1279 Nov 21 2023 Makefile
drwxr-xr-x 2 user group 4096 Sep 26 13:57 obj
drwxr-xr-x 2 user group 4096 Nov 6 2022 src
drwxr-xr-x 3 user group 4096 Nov 20 2022 tests
-rw-r--r-- 1 user group 470 Nov 20 2022 todo

./bin:
total 20
-rw-r--r-- 1 user group 17240 Feb 7 2025 my_ls

./include:
... etc
```