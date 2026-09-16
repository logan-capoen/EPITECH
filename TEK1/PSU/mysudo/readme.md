# My_sudo

> Substitute User Do — Epitech

A reimplementation of the `sudo` command: authenticates a user by password, checks their authorization in `/etc/sudoers`, and runs a command as another user (and/or group).

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Usage](#usage)
- [Authentication](#authentication)
- [Sudoers policy](#sudoers-policy)
- [Examples](#examples)
- [Security](#security)

## Overview

```
./my_sudo [-ug] [command [args ...]]
```

```
$> ./my_sudo -h
usage: ./my_sudo -h
usage: ./my_sudo [-ug] [command [args ...]]
Flags:
-h,
Display a short help message to the standard output and exit.
-u user,
Run the command as a user other than the default target user (usually root)
-g group,
Run the command with the primary group set to group instead of the primary group specified by the target
user's password database entry
```

Exit status is `0` on success, `84` on failure. Error messages are written to the standard error output.

## Compilation

```bash
make          # builds the `my_sudo` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

The Makefile does not change the binary's ownership or set the SUID bit.

## Usage

```bash
./my_sudo printf "Hello world"
./my_sudo -u toto whoami
./my_sudo -u toto -g docker yes
./my_sudo -s
```

## Authentication

The user invoking `my_sudo` is authenticated with their password, read directly from stdin (instead of a pty). A wrong password allows two additional attempts before the program fails.

```
$> (echo "good_password") | ./my_sudo printf "Hello world"
Hello world
```

```
$> (echo "bad_password"; sleep 1; echo "good_password") | ./my_sudo printf "Hello world"
[my_sudo] password for current_user: Sorry, try again.
[my_sudo] password for current_user: Hello world
```

## Sudoers policy

Authorization is read from `/etc/sudoers`, handling User Aliases (everything after a User Alias is treated as `ALL=(ALL) ALL`):

```
$> cat /etc/sudoers
...
kc ALL=(ALL) ALL
%wheel ALL=(ALL) ALL
#1042 ALL=(ALL) ALL
%#4242 ALL=(ALL) ALL
...
```

A user not listed in the sudoers file is rejected:

```
$> whoami
tutu
$> ./my_sudo whoami
[my_sudo] password for tutu:
tutu is not in the my_sudoers file.
```

## Examples

```
$> whoami
kc
$> ./my_sudo /usr/bin/whoami
[my_sudo] password for kc:
root
```

```
$> whoami
kc
$> ./my_sudo -u toto whoami
[my_sudo] password for kc:
toto
$> ./my_sudo -u toto cat top_secret
42
```

```
$> ./my_sudo -u toto -g docker yes
[my_sudo] password for kc:
$> ps -C yes -o ruser,rgroup,euser,egroup
COMMAND RUSER RGROUP EUSER EGROUP
yes toto docker toto docker
```

`-s` launches the target user's shell (from `/etc/passwd`, or `$SHELL` if the current user runs it for themselves):

```
$> whoami
kc
$> ./my_sudo -s
[my_sudo] password for kc:
$> ps -p $$ -o cmd,user,group
CMD USER GROUP
/bin/bash root root
```

```
$> ./my_sudo -s -u toto
[my_sudo] password for kc:
$> ps -p $$ -o cmd,user,group
CMD USER GROUP
/bin/zsh toto admins
```

## Security

- No information about user credentials is disclosed while the password is being entered.
- User-controlled input (password, environment variables) is never trusted as-is.