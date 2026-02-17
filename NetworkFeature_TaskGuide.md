# Network Feature Enablement & Investigation Guide

## Overview
This document outlines the key areas of the Oni codebase relevant to enabling and understanding the network (multiplayer) feature. It provides a roadmap for investigation, highlights important files and functions, and explains the flow of data for network play.

---

## 1. Frontend: Multiplayer UI and Logic
- **Files to Investigate:**
  - `OniProj/OniGameSource/Oni_Windows.h`
  - `OniProj/OniGameSource/Oni_Windows/Oni_Win_Multiplayer.c`
- **Why Relevant:**
  - These files define the user interface and logic for hosting and joining multiplayer games.
- **Key Actions:**
  - Review how multiplayer dialogs and menus are created and displayed.
  - Trace how user input (host name, server address, options) is collected and validated.
  - Follow the flow from UI actions to network calls (e.g., `OWiMP_JoinServer`).

---

## 2. Backend: Network Manager
- **Files to Investigate:**
  - `BungieFrameWork/BFW_Source/BFW_NetworkManager/NM_WinSock/NM_WinSock_Private.h` (and related source files)
- **Why Relevant:**
  - This is where low-level network communication is managed (sockets, events, packet queues).
- **Key Actions:**
  - Understand how sockets are created, managed, and closed.
  - Investigate how data is sent and received (queues, events).
  - Review error handling and cleanup logic.

---

## 3. Integration Points
- **What to Look For:**
  - Calls to functions like `ONrNet_Client_Start`, `ONrNet_Client_Join`, etc.
- **Why Relevant:**
  - These functions bridge the frontend UI/game logic and the backend networking code.
- **Key Actions:**
  - Identify what data is passed to these functions.
  - Check how errors are handled and reported to the UI.
  - Search for feature flags or conditionals that may disable network play.

---

## 4. Required Changes
- **Enable/Expose UI Elements:**
  - Ensure multiplayer menus and dialogs are visible and accessible in the game.
- **Remove/Bypass Feature Flags:**
  - Find and update any flags or compile-time options that disable network play.
- **Test Data Flow:**
  - Verify that user actions in the UI result in correct network operations.
  - Ensure errors are handled gracefully and reported to the user.
- **Backend Robustness:**
  - Confirm that sockets and network events are properly managed and cleaned up on disconnect.

---

## 5. Next Steps
- Enable any hidden/disabled multiplayer UI elements.
- Trace the flow from UI action (host/join) to backend network calls.
- Test hosting and joining a game, using logs to verify data movement.
- Investigate and fix any points where the network feature is blocked or incomplete.

---

**Tip:** Use this guide as a checklist while enabling and debugging the network feature. Document any additional findings or issues for future reference.
