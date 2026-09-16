# Texte Structure

Documentation for the `Texte` structure.

---

## Definition

```cpp
struct Texte {
    int x = 0;
    int y = 0;
    float size = 1.0f;
    std::string text = "";
    Color color = WHITE;
};
```

---

## Attributes

| Attribute | Type | Default | Description |
|-----------|------|---------|-------------|
| `x` | `int` | `0` | Horizontal position in pixels |
| `y` | `int` | `0` | Vertical position in pixels |
| `size` | `float` | `1.0f` | Font size (1.0 = normal size) |
| `text` | `std::string` | `""` | Text content to be displayed |
| `color` | `Color` | `WHITE` | Text color |

---

## Colors

```cpp
enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
    WHITE,
    MAGENTA,
    CYAN
};
```
