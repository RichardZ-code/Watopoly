# Watopoly

A terminal-based, University of Waterloo-themed property-trading game in C++14.

## Project background

This was an undergraduate **team project**, not a solo implementation. This repository
is Richard Zhu's uploaded copy; its upload history does not represent the original
team's individual contributions. The original collaboration was hosted in the private
`IceLake32/Watopoly` repository. Specific personal contributions should be described
only after checking the original team records. Publication permissions and the course
policy must be checked separately; this maintenance work does not grant permission.

## Build and run

Requires a C++14 compiler and Make. Run from the repository root:

```sh
make -C Watopoly
./Watopoly/watopoly
```

Enter 2 to 7 players, then choose the character letters requested by the program.
For manual deterministic dice input, use `./Watopoly/watopoly -testing`.
The game accepts commands such as `roll`, `next`, `assets`, `trade`, `save`, and `quit`.
To load a previously saved game: `./Watopoly/watopoly -load path/to/save.txt`.

## Structure

- `Watopoly/Watopoly.cc`: board setup, game operations, save/load, terminal display.
- `Watopoly/player.*`: player balances, inventories, and property acquisition.
- `Watopoly/building.*`, `property.*`, and derived types: board-square behavior.
- `design.pdf` and `uml-final.pdf`: historical team design documents.
- `tests/`: targeted, executable regression checks.

## Correctness maintenance

The current fixes initialize academic improvement levels, accept purchases when the
player has exactly the required cash, and prevent an unaffordable purchase from
accidentally selling a level. Property acquisition now updates both the stored owner
and the player inventories, including all three supported trade forms. Repeated
acquisition of the same property does not duplicate it.

Players that acquire properties must be managed with `std::make_shared<Player>`;
this matches the game's existing creation paths. `shared_from_this()` reuses the
existing ownership control block rather than creating a second one.

## Tests

```sh
make -C tests test
```

The suite checks improvement initialization/bounds, exact and insufficient cash,
accepted and rejected trades, ownership lists, rent after transfer, and a fresh-game
save/load round trip after a trade. A single case can be run, for example:
`./tests/regressions money_for_property`.
CI builds the application and runs these checks on Linux with GCC and Clang.

## Scope and limitations

These are focused maintenance fixes, not a complete audit of every game rule. Legacy
command parsing, malformed-save handling, bankruptcy edge cases, and shared-pointer
lifetime cycles need further review. The regression suite does not establish that
every gameplay path is correct. Existing PDF diagrams describe the historical design,
not a separately verified specification for every current implementation detail.
