# Panoramix

> One Refill at a Time! — Epitech

A multithreaded simulation of Panoramix's magic potion cauldron: villagers drink potion to fight Romans, and the druid refills the pot when it runs dry, all synchronized with threads, semaphores and mutexes.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Usage](#usage)
- [Behavior](#behavior)
- [Example](#example)

## Overview

Each villager and the druid run in their own thread. The cauldron starts full. A villager drinks a serving of potion before every fight; when the pot runs empty, the villager wakes the druid and waits for a refill. The druid refills the pot until it has no ingredients left, at which point it goes back to sleep for good. The program exits gracefully once every villager has finished fighting.

## Compilation

```bash
make          # builds the `panoramix` binary
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # fclean then rebuild
```

## Usage

```bash
./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
```

- `nb_villagers` — number of villagers
- `pot_size` — maximum number of servings the pot can hold
- `nb_fights` — number of fights each villager goes through
- `nb_refills` — number of times the druid can refill the pot

```
$> ./panoramix -1 3 2 1 >/dev/null; echo $?
USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
Values must be >0.
84
```

## Behavior

Each villager fights `nb_fights` times, drinking a serving of potion before every fight. The druid wakes up when called, refills the pot with `pot_size` servings, and stops for good once `nb_refills` refills have been done.

## Example

```
$> ./panoramix 3 5 3 1
Druid: I'm ready... but sleepy...
Villager 2: Going into battle!
Villager 1: Going into battle!
Villager 0: Going into battle!
Villager 2: I need a drink... I see 5 servings left.
Villager 0: I need a drink... I see 4 servings left.
Villager 0: Take that roman scum! Only 2 left.
Villager 1: I need a drink... I see 3 servings left.
Villager 2: Take that roman scum! Only 2 left.
Villager 1: Take that roman scum! Only 2 left.
Villager 0: I need a drink... I see 2 servings left.
Villager 0: Take that roman scum! Only 1 left.
Villager 2: I need a drink... I see 1 servings left.
Villager 1: I need a drink... I see 0 servings left.
Villager 1: Hey Pano wake up! We need more potion.
Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only make 0 more refills after this one.
Druid: I'm out of viscum. I'm going back to... zZz
Villager 1: Take that roman scum! Only 1 left.
Villager 2: Take that roman scum! Only 1 left.
Villager 0: I need a drink... I see 4 servings left.
Villager 1: I need a drink... I see 3 servings left.
Villager 0: Take that roman scum! Only 0 left.
Villager 2: I need a drink... I see 2 servings left.
Villager 1: Take that roman scum! Only 0 left.
Villager 2: Take that roman scum! Only 0 left.
Villager 0: I'm going to sleep now.
Villager 1: I'm going to sleep now.
Villager 2: I'm going to sleep now.
```

Threads run asynchronously, so the exact output order can vary between runs.