# 102Architect

> Home Planning and Homogeneous Coordinates — Epitech

A program computing the coordinates of a point after one or several geometric transformations, using homogeneous coordinates and matrix products built from scratch (no matrix calculus library such as numpy).

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Examples](#examples)

## Overview

Given a point `(x, y)`, the program applies a sequence of transformations, each centered on the origin `O`, and prints the resulting transformation matrix and the point's final coordinates:

- **Translation** — along a given vector
- **Scaling** — by given factors on each axis
- **Rotation** — centered at `O`, by a given angle
- **Reflection** — over any axis through `O`, at a given inclination angle
- **Any combination** of the above, applied in sequence

## Usage

```bash
$> ./102architect -h
USAGE
./102architect x y transfo1 arg11 [arg12] [transfo2 arg21 [arg22]] ...
DESCRIPTION
x abscissa of the original point
y ordinate of the original point
transfo arg1 [arg2]
-t i j translation along vector (i, j)
-z m n scaling by factors m (x-axis) and n (y-axis)
-r d rotation centered in O by a d degree angle
-s d reflection over the axis passing through O with an inclination
angle of d degrees
```

## Examples

```
$> ./102architect 5 0 -t -1 1
Translation along vector (-1, 1)
1.00 0.00 -1.00
0.00 1.00 1.00
0.00 0.00 1.00
(5.00, 0.00) => (4.00, 1.00)
```

```
$> ./102architect 2 2 -z -1 1
Scaling by factors -1 and 1
-1.00 0.00 0.00
0.00 1.00 0.00
0.00 0.00 1.00
(2.00, 2.00) => (-2.00, 2.00)
```

```
$> ./102architect 1 0 -r 90
Rotation by a 90 degree angle
0.00 -1.00 0.00
1.00 0.00 0.00
0.00 0.00 1.00
(1.00, 0.00) => (0.00, 1.00)
```

```
$> ./102architect 3 -1 -s 270
Reflection over an axis with an inclination angle of 270 degrees
-1.00 0.00 0.00
0.00 1.00 0.00
0.00 0.00 1.00
(3.00, -1.00) => (-3.00, -1.00)
```

```
$> ./102architect 1 2 -t 2 3 -z 1 -2 -r 45 -s 30
Translation along vector (2, 3)
Scaling by factors 1 and -2
Rotation by a 45 degree angle
Reflection over an axis with an inclination angle of 30 degrees
0.97 -0.52 0.38
0.26 1.93 6.31
0.00 0.00 1.00
(1.00, 2.00) => (0.31, 10.44)
```