# Bug Break 🪲

> *"You just wanted a coffee. The office had other plans."*

A narrative top-down horror game made for the **Bug Game Jam**.
Made in **Godot 4**.

## Concept

You play as an office worker heading to the break room for coffee.
As you move through the building, something is wrong — certain objects
have been *replaced* by bugs. Find them all before the spider finds you.

- ✅ Find all bugged assets in a room → unlock the next room
- 🕷️ Spider is hunting you — hide in closets/under desks to lose it
- ☕ Reach the coffee machine → you wake up, coffee in hand
- 💀 Get caught → you wake up, no coffee, back to the start

## How to Run

1. Open the project in **Godot 4.2+**
2. Open `project.godot`
3. Create the `.tscn` scene files described in `scenes/README.md`
4. Add your art assets to `assets/` (see `assets/README.md`)
5. Set up the Input Map as described in `input_map.md`
6. Hit **Play**

## Scripts Overview

| Script | Purpose |
|---|---|
| `game_manager.gd` | Global state: win/lose, room progression |
| `room_manager.gd` | Tracks bug-find progress per room |
| `player.gd` | Movement, hiding, interaction |
| `spider_ai.gd` | WANDER/CHASE/SEARCH state machine |
| `swappable_asset.gd` | Office prop that may be a secret bug |
| `hiding_spot.gd` | Area where player can hide from spider |
| `coffee_machine.gd` | Final win-trigger interactable |
| `main_menu.gd` | Menu with coffee/no-coffee state display |

## Team

<!-- Add your team members here -->
