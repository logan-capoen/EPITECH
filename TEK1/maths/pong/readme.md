# 101Pong

> Vectors and Video Games — Epitech

A Python program simulating the motion of a Pong ball in 3D space, computing its velocity vector, its position after a given time, and the angle at which it hits the paddle.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Output](#output)
- [Examples](#examples)

## Overview

The paddle lies in the `(Oxy)` plane (`z = 0`). Only the ball's motion is considered — paddle bounces and game-over conditions are out of scope. Given the ball's position at two consecutive instants, the program computes:

- the ball's velocity vector
- the ball's coordinates after a given time shift
- the angle at which the ball hits the paddle, if it does

## Usage

```bash
$> ./101pong -h
USAGE
./101pong x0 y0 z0 x1 y1 z1 n
DESCRIPTION
x0 ball abscissa at time t - 1
y0 ball ordinate at time t - 1
z0 ball altitude at time t - 1
x1 ball abscissa at time t
y1 ball ordinate at time t
z1 ball altitude at time t
n time shift (greater than or equal to zero, integer)
```

## Output

The program prints, in order:

1. The ball's velocity vector.
2. The ball's coordinates at time `t + n`.
3. Either the incidence angle (between 0 and 90 degrees) if the ball reaches the paddle, or a message stating that it won't.

## Examples

```
$> ./101pong 1 3 5 7 9 -2 4
The velocity vector of the ball is:
(6.00, 6.00, -7.00)
At time t + 4, ball coordinates will be:
(31.00, 33.00, -30.00)
The ball won't reach the paddle.
```

```
$> ./101pong 1.1 3 5 -7 9 2 4
The velocity vector of the ball is:
(-8.10, 6.00, -3.00)
At time t + 4, ball coordinates will be:
(-39.40, 33.00, -10.00)
The incidence angle is:
16.57 degrees
```