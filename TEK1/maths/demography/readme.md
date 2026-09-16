# 105Demography

> Population and Regression — Epitech

A program computing linear least-squares regressions on population data, to predict a country's (or group of countries') population from historical census data.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Examples](#examples)

## Overview

Using `105demography_data.csv`, which gives an estimation of every country's population from 1960 onwards, the program establishes two linear fits between the year (`X`) and the population in millions (`Y`):

- `Y = aX·X + bX`
- `X = aY·Y + bY`

For one or several given country codes, it prints:

1. the `aX` and `bX` coefficients of the `Y = aX·X + bX` fit
2. the root-mean-square deviation of that fit
3. the population prediction for 2050 from that fit
4. the `aY` and `bY` coefficients of the `X = aY·Y + bY` fit
5. the root-mean-square deviation of that fit
6. the population prediction for 2050 from that fit
7. the correlation coefficient between `X` and `Y`

All the core computations (RMS deviation, linear fits, correlation) are implemented from scratch — no function or library performing them is used.

## Usage

```bash
$> ./105demography -h
USAGE
./105demography [code]+
DESCRIPTION
code country code
```

Several country codes can be given at once, in which case their populations are combined.

## Examples

```
$> ./105demography EUU
Country: European Union
Fit1
Y = 1.62 X - 2749.67
Root-mean-square deviation: 5.22
Population in 2050: 570.85
Fit2
X = 0.60 Y + 1707.97
Root-mean-square deviation: 5.32
Population in 2050: 574.54
Correlation: 0.9820
```

```
$> ./105demography BRA BOL PER
Country: Bolivia, Brazil, Peru
Fit1
Y = 3.06 X - 5906.34
Root-mean-square deviation: 2.22
Population in 2050: 359.35
Fit2
X = 0.33 Y + 1932.53
Root-mean-square deviation: 2.22
Population in 2050: 359.70
Correlation: 0.9991
```