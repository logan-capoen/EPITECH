# InputEvent Structure

Documentation for the `InputEvent` structure for input event management.

---

## Overview

```cpp
enum EventType {
    UP_ARROW,
    DOWN_ARROW,
    LEFT_ARROW,
    RIGHT_ARROW,
    LEFT_CLICK,
    RIGHT_CLICK,
    SWITCH_DISPLAY,
    SWITCH_GAME,
    RESTART_GAME,
    CALL_MENU,
    ENTER,
    SPACE,
    QUIT,
    ROAR,
    UNKNOWN
};

struct InputEvent {
    EventType event = UNKNOWN;
    pos mouse = {0, 0};
};
```

---

## EventType Enumeration

The `EventType` enumeration defines all possible event types within the system.

### Movement Events

| Event | Description |
|-----------|-------------|
| `UP_ARROW` | Up arrow pressed |
| `DOWN_ARROW` | Down arrow pressed |
| `LEFT_ARROW` | Left arrow pressed |
| `RIGHT_ARROW` | Right arrow pressed |

**Typical usage:** Player movement, menu navigation.

---

### Mouse Events

| Event | Description |
|-----------|-------------|
| `LEFT_CLICK` | Mouse left click |
| `RIGHT_CLICK` | Mouse right click |

**Note:** The mouse position is stored in `InputEvent.mouse`.

---

### Special Keyboard Events

| Event | Description |
|-----------|-------------|
| `ENTER` | Enter key pressed |
| `SPACE` | Space key pressed |

**Typical usage:** Validation, shooting, jumping, pausing.

---

### System Events

| Event | Description |
|-----------|-------------|
| `SWITCH_DISPLAY` | Change graphical library |
| `SWITCH_GAME` | Change game |
| `RESTART_GAME` | Restart current game |
| `CALL_MENU` | Open the menu |
| `QUIT` | Quit the application |

**Note:** These events are handled by the core, not directly by the games.

---

### Special Events

| Event | Description |
|-----------|-------------|
| `ROAR` | Special event that loads a sound |
| `UNKNOWN` | Unrecognized or uninitialized event |

**Default value:** `UNKNOWN` is the default value for an `InputEvent`.

---

## InputEvent Structure

### Attributes

```cpp
struct InputEvent {
    EventType event = UNKNOWN;
    pos mouse = {0, 0};
};
```

| Attribute | Type | Default Value | Description |
|----------|------|-------------------|-------------|
| `event` | `EventType` | `UNKNOWN` | The type of detected event |
| `mouse` | `pos` | `{0, 0}` | Mouse position during the event |
