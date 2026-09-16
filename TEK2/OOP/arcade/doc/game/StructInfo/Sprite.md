# Sprite Structure

Documentation for the `Sprite` structure.

---

## Definition

```cpp
struct Sprite {
    int x = 0;
    int y = 0;
    int rotation = 0;
    float size = 1.0f;
    std::string name = "";
};
```

---

## Attributes

| Attribute | Type | Default | Description |
|-----------|------|---------|-------------|
| `x` | `int` | `0` | Horizontal position in pixels |
| `y` | `int` | `0` | Vertical position in pixels |
| `rotation` | `int` | `0` | Rotation angle in degrees (0-359) |
| `size` | `float` | `1.0f` | Sprite scale (1.0 = normal size) |
| `name` | `std::string` | `""` | Path to the texture |
