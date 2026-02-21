# Oni Multiplayer Networking Integration Tasks

## High-Level Design Overview

The Oni networking/multiplayer code is designed to synchronize player state and actions across multiple game clients. This requires sharing detailed information about each character's state, such as movement, actions, aiming, and weapon status. The networking code expects the `ONtCharacter` struct to contain various fields that represent this state, but these fields are currently missing from your codebase.

### What is Missing in `ONtCharacter`?
The networking code references fields like `inputState`, `animFrame`, `physics`, `animation`, `actionFlags`, `weapon`, `isAiming`, `aimingLR`, `aimingUD`, `aimingTarget`, `aimingVector`, `inAirControl`, `targetThrow`, `throwing`, `throwTarget`, `fightFramesRemaining`, `validTarget`, and `pleaseFire`. These are not present in the current struct definition.

#### Why Are These Needed?
- **Purpose:** These fields represent the real-time state of a character that must be communicated to other players for multiplayer synchronization.
- **Mechanism:** The networking code serializes/deserializes these fields to send/receive updates over the network. Without them, the game cannot accurately represent remote players' actions or state.
- **Examples:**
  - `inputState`: Captures player input (movement, actions).
  - `animFrame`/`animation`: Tracks current animation for smooth playback.
  - `actionFlags`: Indicates actions like firing, jumping, etc.
  - `aimingLR`/`aimingUD`: Represents aiming direction for shooting.

## Overall Goal
To enable multiplayer/networking, you must:
- Extend `ONtCharacter` to include all fields required by the networking code.
- Ensure these fields are updated during gameplay and correctly serialized/deserialized for network communication.
- Define any missing constants or enums referenced by the networking code.

## Data Requirements
- **Supplied Data:** Player input, animation state, weapon status, aiming direction, action flags, etc.
- **Why:** This data is essential for synchronizing character behavior and appearance across all clients in a multiplayer session.
- **Mechanism:** The networking system reads/writes these fields to network packets, ensuring all players see consistent game state.


## Best Practices: Tracking Network-Controlled Characters

### How Are Characters Tracked?
All characters (player, AI, and network-controlled) are typically tracked in a global array or list, such as in a main game state struct (e.g., `ONgGameState`).

### Distinguishing Control Types
- Add a field to `ONtCharacter` to indicate control type:

```c
typedef enum {
  ONcControlType_Player,
  ONcControlType_AI,
  ONcControlType_Network
} ONtControlType;

typedef struct {
    ONtInputState inputState;
    float aimingLR;
    float aimingUD;
    // ...add all other fields needed for network sync...
} ONtNetCharacterState;

typedef struct {
  // ...existing fields...
  ONtControlType controlType;
  ONtNetCharacterState* netState; // NULL unless network-controlled
} ONtCharacter;
```

- This allows you to easily distinguish between local player, AI, and network-controlled characters.

### How Is Network Data Used?
- For network-controlled characters, their state is updated from network packets.
- For AI or local player, state is updated from input or AI logic.
- The rest of the game logic (physics, rendering, etc.) should treat all characters the same, regardless of control source.

### Unified Update Path
In the main update loop:
- If `controlType == ONcControlType_Network`, update from network data.
- Else, update from input or AI.
- Then, run the rest of the game logic as usual.

### Why This Approach?
- Keeps networking logic separate from core game logic (separation of concerns).
- Only adds networking state when needed.
- Maintains a clean, maintainable, and modular codebase.

## Example: Adding a Missing Field (Networking State)
Suppose the networking code expects an `inputState` field:

```c
// In Oni_NetCharacterState.h (new file)
typedef struct {
  ONtInputState inputState; // Holds the current input state for networking
  // ...other networking fields...
} ONtNetCharacterState;

// In Oni_Character.h, inside struct ONtCharacter
ONtNetCharacterState* netState; // NULL unless network-controlled
```
- **Type:** You may need to define `ONtInputState` if it does not exist, or use a suitable type representing input.
- **Usage:** This field will be read/written by networking code to synchronize player actions.

## Next Steps
1. Review all missing fields and constants referenced by the networking code.
2. Add them to a new networking state struct (e.g., `ONtNetCharacterState`).
3. Add a pointer to this struct in `ONtCharacter` and a control type field.
4. Ensure the update loop injects network data for network-controlled characters, and otherwise uses input or AI.
5. Repeat for each missing field, using the example above as a template.

---

**This document is your guide for integrating multiplayer support. Start by adding the control type and networking state pointer, then incrementally add fields and logic, testing as you go.**
