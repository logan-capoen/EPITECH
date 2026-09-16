# IDisplay

Documentation for the `IDisplay` interface which inherits from your class.

---

## Definition

```cpp
class IDisplay : public ALib {
    public:
        virtual ~IDisplay() = default;

        virtual int createWindow() = 0;
        virtual void closeWindow() = 0;
        virtual void clear() = 0;
        virtual void display() = 0;

        virtual InputEvent getInput() = 0;

        virtual void drawBackground(std::string background_name) = 0;
        virtual void drawText(pos position, float size, std::string text, Color color) = 0;
        virtual void drawSprite(pos position, int rotation, float size, std::string name) = 0;

        virtual int loadTexture(std::string game) = 0;
        virtual int loadSound(std::string game) = 0;
        virtual int playSound(std::string sound_name_in_map) = 0;
        virtual std::string loadName() = 0;
        virtual std::tuple<int, int> recoverWindowSize() = 0;
};
```

---

## Description

The `IDisplay` interface defines the functions necessary to manage graphical display, user inputs, as well as resources (textures and sounds).

Every graphical library must implement this interface.

---

## Window Management

| Method | Return | Description |
|--------|--------|-------------|
| `createWindow()` | `int` | Creates the window |
| `closeWindow()` | `void` | Closes the window |
| `clear()` | `void` | Clears the window content |
| `display()` | `void` | Displays the rendering |

---

## Input Management

| Method | Return | Description |
|--------|--------|-------------|
| `getInput()` | `InputEvent` | Retrieves a user input |

**Reference:** See [InputEvent](./StructInfo/InputEvent.md) for more details on the structure.

---

## Graphical Rendering

| Method | Parameters | Description |
|--------|-----------|-------------|
| `drawBackground()` | `std::string background_name` | Displays a background |
| `drawText()` | `pos position`, `float size`, `std::string text`, `Color color` | Displays text |
| `drawSprite()` | `pos position`, `int rotation`, `float size`, `std::string name` | Displays a sprite |

---

## Resource Management

| Method | Return | Description |
|--------|--------|-------------|
| `loadTexture()` | `int` | Loads textures for a game |
| `loadSound()` | `int` | Loads sounds for a game |
| `playSound()` | `int` | Plays a sound |


For this, refer to the asset management [Assets](./game/Assets.md)

---

## Utilities

| Method | Return | Description |
|--------|--------|-------------|
| `loadName()` | `std::string` | Retrieves the player name |
| `recoverWindowSize()` | `std::tuple<int, int>` | Returns the window size |
