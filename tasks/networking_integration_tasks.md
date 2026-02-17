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

## Example: Adding a Missing Field
Suppose the networking code expects an `inputState` field:

```c
// In Oni_Character.h, inside struct ONtCharacter
ONtInputState inputState; // Holds the current input state for networking
```
- **Type:** You may need to define `ONtInputState` if it does not exist, or use a suitable type representing input.
- **Usage:** This field will be read/written by networking code to synchronize player actions.

## Next Steps
1. Review all missing fields and constants referenced by the networking code.
2. Add them to `ONtCharacter` and related headers.
3. Ensure they are updated and used in both gameplay and networking logic.
4. Repeat for each missing field, using the example above as a template.

---

**This document is your guide for integrating multiplayer support. Start by adding one field (e.g., `inputState`) and build incrementally, testing as you go.**
