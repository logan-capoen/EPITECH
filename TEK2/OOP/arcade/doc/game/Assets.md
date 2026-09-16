# Assets

Documentation regarding the organization and management of project assets.

---

## Folder Structure

Assets are organized by game within the `assets/` directory.  
Each game has its own internal structure, containing different types of resources.

### Example Structure

```bash
assets/
├── centipede/
│   ├── ascii/
│   │   ├── body.txt
│   │   ├── bullet.txt
│   │   ├── head.txt
│   │   ├── invader.txt
│   │   └── mushroom.txt
│   ├── images/
│   │   ├── body.png
│   │   ├── bullet.png
│   │   ├── head.png
│   │   ├── invader.png
│   │   └── mushroom.png
│   ├── sounds/
│   │   └── shoot.mp3
│   └── highScores.txt
│
├── snake/
│   ├── ascii/
│   │   ├── snake_body.txt
│   │   ├── snake_food.txt
│   │   ├── snake_head.txt
│   │   ├── snake_tail.txt
│   │   ├── snake_turn_bottom_to_left.txt
│   │   ├── snake_turn_bottom_to_right.txt
│   │   ├── snake_turn_top_to_left.txt
│   │   ├── snake_turn_top_to_right.txt
│   │   └── snake_wall.txt
│   ├── images/
│   │   ├── apple.png
│   │   ├── background.png
│   │   ├── snake_head.png
│   │   ├── snake_body.png
│   │   ├── snake_tail.png
│   │   └── snake_wall.png
│   ├── sounds/
│   │   ├── eat.mp3
│   │   ├── game_over.mp3
│   │   └── snake_death.mp3
│   └── highScores.txt
│
└── font/
    └── Nasa21.ttf
```

---

## Game Organization

Each game must follow the following structure:

```bash
<game_name>/
├── ascii/
├── images/
├── sounds/
└── highScores.txt
```

### `ascii/`
Contains the ASCII representations of game elements (`.txt` format).

Examples:
- `snake_head.txt`
- `body.txt`
- `mushroom.txt`

---

### `images/`
Contains the textures used for graphical rendering (`.png` format).

Examples:
- `snake_head.png`
- `bullet.png`
- `background.png`

---

### `sounds/`
Contains the game's sound effects (`.mp3` format).

Examples:
- `shoot.mp3`
- `eat.mp3`
- `game_over.mp3`

---

### `highScores.txt`
File containing the game scores.

---

### `font/`
Global folder containing the fonts used in the project.

Example:
- `Nasa21.ttf`
