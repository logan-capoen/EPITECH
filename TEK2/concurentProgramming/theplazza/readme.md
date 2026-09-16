# Plazza

> Who Said Anything About Pizzas? — Epitech

A pizzeria simulation in C++: a reception process takes orders and dispatches them, pizza by pizza, to kitchens that spawn dynamically and cook with a pool of threaded cooks.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Usage](#usage)
- [Ordering pizzas](#ordering-pizzas)
- [Kitchens and cooks](#kitchens-and-cooks)
- [Menu](#menu)

## Overview

The reception is an interactive shell that takes pizza orders and reports on the state of every kitchen. Kitchens are separate processes, spawned as needed, each running a thread pool of cooks that bake pizzas. Reception and kitchens communicate over IPC.

## Compilation

```bash
make          # builds the `plazza` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

Also buildable via CMake.

## Usage

```bash
./plazza <cooking_time_multiplier> <cooks_per_kitchen> <restock_time_ms>
```

```bash
$> ./plazza 2 5 2000
```

- `cooking_time_multiplier` — multiplies (or, between 0 and 1, divides) every pizza's cooking time
- `cooks_per_kitchen` — number of cooks assigned to each kitchen
- `restock_time_ms` — time, in milliseconds, between each ingredient restock in a kitchen's stock

From the reception shell:

- placing an order, e.g. `regina XXL x7`
- `status` — displays every kitchen's current occupancy and ingredient stock

## Ordering pizzas

```
S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*
TYPE := [a..zA..Z]+
SIZE := S|M|L|XL|XXL
NUMBER := x[1..9][0..9]*
```

```
regina XXL x2; fantasia M x3; margarita S x1
```

Orders can be placed at any time while the program is running. Each pizza in an order is dispatched individually to a kitchen, keeping kitchen occupancy as balanced as possible. When every kitchen is saturated, a new one is started. Once an order is ready, it is reported to the user and logged.

## Kitchens and cooks

- A kitchen is a child process of the reception, spawned only when needed.
- Cooks are threads, scheduled by a thread pool local to their kitchen; a cook only ever works on one pizza at a time.
- A kitchen can hold at most `2 × N` pizzas at once (cooking or waiting), `N` being its number of cooks; beyond that, it refuses further pizzas.
- A kitchen that stays idle for more than 5 seconds shuts down.
- A kitchen's ingredient stock starts at 5 units of each ingredient, and regenerates 1 unit of each ingredient every `restock_time_ms` milliseconds.

## Menu

| Pizza | Ingredients | Base cooking time |
|---|---|---|
| Margarita | dough, tomato, gruyere | 1 sec × multiplier |
| Regina | dough, tomato, gruyere, ham, mushrooms | 2 secs × multiplier |
| Americana | dough, tomato, gruyere, steak | 2 secs × multiplier |
| Fantasia | dough, tomato, eggplant, goat cheese, chef's love | 4 secs × multiplier |