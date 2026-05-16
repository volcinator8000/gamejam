# Bug Break 🪲

> *"You just wanted a coffee. The office had other plans."*

Hybrid **Unreal Engine 5.4** project. Core gameplay logic is in **C++**; visuals, UI, audio, and level scripting are done in **Blueprints**.

---

## Gameplay loop

- You play as an office worker heading to the break room for coffee.
- Each room has office props — some are secretly **bugged** (replaced by insects).
- Find all bugged props in a room to unlock the next one.
- A spider is hunting you. Hide in closets or under desks to lose it.
- Reach the coffee machine → you wake up at your desk with coffee ✅
- Get caught by the spider → you wake up without coffee ❌

---

## Project structure

```
Source/BugBreak/
├── Game/
│   ├── BugBreakGameInstance   — persistent run state (coffee, room index)
│   ├── BugBreakGameMode       — room flow, win/lose, map loading
│   └── RoomManager            — tracks bug find progress per room
├── Player/
│   └── BugBreakPlayerCharacter — movement, interact, hiding
├── AI/
│   └── SpiderAICharacter      — WANDER / CHASE / SEARCH state machine
├── Interactables/
│   ├── SwappableActor         — office prop that may be a bug
│   ├── HidingSpot             — volume that enables hiding
│   └── CoffeeMachine          — final win interactable
└── UI/
    └── MainMenuWidgetBase     — base class for the main menu widget
```

---

## Blueprint classes to create in the editor

| Blueprint | Parent C++ class | Purpose |
|---|---|---|
| `BP_PlayerCharacter` | `ABugBreakPlayerCharacter` | Assign mesh, camera, animations |
| `BP_SpiderAICharacter` | `ASpiderAICharacter` | Assign mesh, AI Controller |
| `BP_SwappableActor` | `ASwappableActor` | Assign normal/bugged meshes |
| `BP_HidingSpot` | `AHidingSpot` | Resize the box volume as needed |
| `BP_CoffeeMachine` | `ACoffeeMachine` | Assign mesh |
| `WBP_MainMenu` | `UMainMenuWidgetBase` | Design UI, bind Start/Quit buttons |

---

## Maps to create

| Map name | Purpose |
|---|---|
| `LV_MainMenu` | Title screen |
| `LV_Room00` | First gameplay room |
| `LV_Room01` | Second room |
| `LV_Room02` | Third room |
| `LV_CoffeeRoom` | Final room with coffee machine |

---

## C++ class reference

### UBugBreakGameInstance
Stores run-wide state that persists across map loads.
Assign this class in **Project Settings → Maps & Modes → Game Instance Class**.

| Function | Input | Output | Does |
|---|---|---|---|
| `ResetRunState()` | — | — | Resets coffee state and room index to defaults |
| `SetHasCoffee(bool)` | `bInHasCoffee` | — | Stores whether the player ended the run with coffee |
| `GetHasCoffee()` | — | `bool` | Returns current coffee possession state |
| `SetCurrentRoomIndex(int32)` | `InRoomIndex` | — | Saves current room progression |
| `GetCurrentRoomIndex()` | — | `int32` | Returns stored room index |

---

### ABugBreakGameMode
Controls room progression and win/lose flow.
Assign as the Game Mode in each gameplay level's **World Settings**.

| Function | Input | Output | Does |
|---|---|---|---|
| `AdvanceToNextRoom()` | — | — | Increments room index and loads the next map, or the coffee room if all rooms are cleared |
| `HandlePlayerCaught()` | — | — | Triggers lose flow, returns to main menu without coffee |
| `HandleCoffeeReached()` | — | — | Triggers win flow, returns to main menu with coffee |
| `LoadMainMenu(bool)` | `bWithCoffee` | — | Stores coffee state in GameInstance and opens main menu map |
| `LoadRoomByIndex(int32)` | `RoomIndex` | — | Opens a gameplay level by zero-based index |

---

### ARoomManager
Place one actor per room level. Tracks bug-find progress.

| Function | Input | Output | Does |
|---|---|---|---|
| `InitializeRoom(int32)` | `InRequiredBugCount` | — | Resets progress and sets the win condition for this room |
| `RegisterFoundBug()` | — | — | Increments found count; triggers room clear when target is reached |
| `IsRoomCleared()` | — | `bool` | Returns true when all required bugs are found |
| `GetFoundBugCount()` | — | `int32` | Returns how many bugs have been found so far |
| `GetRequiredBugCount()` | — | `int32` | Returns total bugs needed to clear the room |

---

### ABugBreakPlayerCharacter
The player pawn. Handles movement, interaction, and hiding.

| Function | Input | Output | Does |
|---|---|---|---|
| `SetupPlayerInputComponent(UInputComponent*)` | Input component | — | Binds axis and action mappings |
| `MoveForward(float)` | Axis value | — | Moves character forward or backward |
| `MoveRight(float)` | Axis value | — | Moves character right or left |
| `Interact()` | — | — | Triggers interaction on the focused interactable |
| `BeginHide()` | — | — | Enters hiding state if inside a valid HidingSpot (toggles off if already hidden) |
| `EndHide()` | — | — | Exits hiding state and re-enables movement |
| `SetCanHide(bool)` | `bInCanHide` | — | Enables or disables the ability to hide, called by HidingSpot overlap |
| `IsHiddenState()` | — | `bool` | Returns whether the player is currently hidden |
| `Die()` | — | — | Notifies GameMode that the player was caught |

---

### ASpiderAICharacter
Enemy AI using a WANDER / CHASE / SEARCH state machine.

| Function | Input | Output | Does |
|---|---|---|---|
| `BeginPlay()` | — | — | Finds the player and picks an initial wander target |
| `Tick(float)` | DeltaSeconds | — | Updates the active state every frame |
| `SetTargetPlayer(ABugBreakPlayerCharacter*)` | Player ref | — | Assigns the player reference used by chase and detection |
| `Wander()` | — | — | Moves toward a random nav point, transitions to Chase if player spotted |
| `Chase()` | — | — | Moves toward the player; transitions to Search if player hides, calls Die() if caught |
| `Search(float)` | DeltaSeconds | — | Counts down search timer then returns to Wander |
| `CanSeePlayer()` | — | `bool` | True if player is within detection radius and not hidden |
| `HasCaughtPlayer()` | — | `bool` | True if spider is within catch radius of the player |
| `PickNewWanderTarget()` | — | — | Gets a random reachable nav mesh point and moves there |

---

### ASwappableActor
An office prop that may be secretly bugged.

| Function | Input | Output | Does |
|---|---|---|---|
| `BeginPlay()` | — | — | Swaps mesh to bugged version if `bIsBugged` is true |
| `Interact(ABugBreakPlayerCharacter*)` | Player ref | `bool` | Marks as found and notifies RoomManager; returns false if not bugged or already found |
| `IsBugged()` | — | `bool` | Returns whether this is a required bugged prop |
| `WasFound()` | — | `bool` | Returns whether this prop was already discovered |

---

### AHidingSpot
A trigger volume that lets the player hide.

| Function | Input | Output | Does |
|---|---|---|---|
| `NotifyActorBeginOverlap(AActor*)` | Overlapping actor | — | If player, calls `SetCanHide(true)` |
| `NotifyActorEndOverlap(AActor*)` | Leaving actor | — | If player, calls `SetCanHide(false)` |

---

### ACoffeeMachine
The final win-state interactable.

| Function | Input | Output | Does |
|---|---|---|---|
| `Interact(ABugBreakPlayerCharacter*)` | Player ref | `bool` | Calls `HandleCoffeeReached()` on the GameMode; returns true on success |

---

### UMainMenuWidgetBase
Base C++ class for the main menu UI widget.

| Function | Input | Output | Does |
|---|---|---|---|
| `GetHasCoffee()` | — | `bool` | Reads coffee state from GameInstance for showing win/lose UI |
| `StartNewRun()` | — | — | Resets GameInstance and opens the first room map |
| `QuitGame()` | — | — | Quits the application |

---

## Input bindings

| Action / Axis | Key | Purpose |
|---|---|---|
| `MoveForward` | W / Z (AZERTY) / Arrow Up | Move forward |
| `MoveForward` (negative) | S / Arrow Down | Move backward |
| `MoveRight` | D / Arrow Right | Move right |
| `MoveRight` (negative) | A / Q (AZERTY) / Arrow Left | Move left |
| `Interact` | E | Examine prop / use coffee machine |
| `Hide` | F | Enter or exit a hiding spot |

---

## Source control notes

- Commit `Source/`, `Config/`, `.uproject`, and docs.
- `.uasset` and `.umap` files are tracked with **Git LFS** (see `.gitattributes`).
- Never commit `Binaries/`, `Intermediate/`, `Saved/`, or `DerivedDataCache/`.
