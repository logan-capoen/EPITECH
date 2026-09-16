# Arcade Project

Welcome to the **Arcade** project!

The goal of this project is to create a modular platform capable of running different **graphics libraries** with multiple **games**, interchangeably.

---

## Concept

The program acts as a **core engine** that dynamically loads:

- **graphics libraries** (rendering, input, sound…)
- **game libraries**

The objective is to:
- switch graphics engines on the fly
- launch different games without restarting the program
- easily add your own libraries

---

## Architecture

The project is based on two main types of modules:

---

## Add Your Own Libraries

The project is designed to be **extensible**.

You can add:

### A new game
- Implement the `IGame` interface
- Properly manage assets

More info: [GameLib](./doc/gamelib.md)

---

### A graphics library
- Implement the `IDisplay` interface
- Handle rendering, inputs, and assets

More info: [GraphicLib](./doc/graphiclib.md)

---

## Assets

Assets (images, sounds, ASCII…) must follow a specific structure.

See: [Assets](./doc/game/Assets.md)

---

## Usage

```bash
./arcade <graphic_library>
```

Example:

```bash
./arcade ./lib/arcade_sdl2.so
```

---

## Authors

- [Paul Ammeloot](https://github.com/PaulAmmeloot) paul.ammeloot@epitech.eu
- [Keryan Pollet Druelle](https://github.com/Keryan-pollet) keryan.pollet-druelle@epitech.eu
- [Logan Capoen](https://github.com/logan-capoen) logan.capoen@epitech.eu

## Contributors

- [Noam Bouillet](https://github.com/nomaisthere) noam.bouillet@epitech.eu
- [Louis Hector](https://github.com/MinFlag) louis.hector@epitech.eu