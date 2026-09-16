# IGame Interface

Documentation for the `IGame` interface for the gaming system.

---

## Overview

```cpp
class IGame : public ALib {
public:
    virtual ~IGame() = default;
    virtual void update(InputEvent key) = 0;
    virtual bool isOver() = 0;
    virtual std::size_t getScore() = 0;
    virtual std::vector<Sprite> getSprites() = 0;
    virtual std::vector<Texte> getTextes() = 0;
    virtual std::vector<std::string> getSounds() = 0;
    
protected:
    std::vector<Sprite> _sprites;
    std::vector<Texte>  _textes;
    std::vector<std::string> _sounds;
    std::size_t _score;
};
```

---

## Public Methods

### Destructor

```cpp
virtual ~IGame() = default;
```

**Description:** Default virtual destructor allowing memory to be freed when the library is destroyed.

---

### update

```cpp
virtual void update(InputEvent key) = 0;
```

**Description:** Updates the game state based on the received input event.

**Reference:** See [InputEvent](./StructInfo/InputEvent.md) for more details on the structure.

---

### isOver

```cpp
virtual bool isOver() = 0;
```

**Description:** Checks if the game is over.

---

### getScore

```cpp
virtual std::size_t getScore() = 0;
```

**Description:** Retrieves the player's current score.

---

### getSprites

```cpp
virtual std::vector<Sprite> getSprites() = 0;
```

**Description:** Retrieves all sprites to be displayed from the game to the core.

**Reference:** See [Sprite](./StructInfo/Sprite.md) for more details on the structure.

---

### getTextes

```cpp
virtual std::vector<Texte> getTextes() = 0;
```

**Description:** Retrieves all texts to be displayed from the game to the core.

**Reference:** See [Texte](./StructInfo/Texte.md) for more details on the structure.

---

### getSounds

```cpp
virtual std::vector<std::string> getSounds() = 0;
```

**Description:** Retrieves the list of sounds to be played from the game to the core.

**Note:** Each string corresponds to the name of a sound file to be loaded and played.

---

## Protected Attributes

The following attributes are stored as `protected` and correspond to the data returned by the getters:

| Attribute | Type | Description |
|-----------|------|-------------|
| `_sprites` | `std::vector<Sprite>` | List of game sprites |
| `_textes`  | `std::vector<Texte>`  | List of texts to display |
| `_sounds`  | `std::vector<std::string>` | List of sound names to play |
| `_score`   | `std::size_t`         | Player's current score |

```cpp
protected:
    std::vector<Sprite> _sprites;
    std::vector<Texte>  _textes;
    std::vector<std::string> _sounds;
    std::size_t _score;
```
