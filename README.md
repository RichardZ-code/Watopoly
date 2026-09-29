# Watopoly

A terminal-based, University of Waterloo-themed Monopoly game in C++14.

Originally developed collaboratively as an undergraduate team project. This
repository was imported as a snapshot, so its upload history does not represent
the original team's individual contributions. The original design documents
are retained at the repository root.

## Build and run

Use a C++14-capable compiler and Make, from the repository root:

```sh
make -C Watopoly
cd Watopoly
./watopoly
```

Enter 2 to 7 players and choose the character IDs shown by the program.
The game implements property purchases, trades, improvements, mortgages,
auctions, bankruptcy, and text-file save/load. It uses polymorphic building
types and shared pointers for game objects.

For deterministic dice input, start `./watopoly -testing`. A saved game can be
loaded with `./watopoly -load path/to/save.txt`, or
`./watopoly -testing -load path/to/save.txt`. Follow the in-game command prompts.

## Regression tests

```sh
make -C tests test
```

The tests exercise the actual game classes, with deterministic input replacing
interactive prompts. They cover initial improvement state, exact-cost and
unaffordable purchases, improvement bounds and cash accounting, all three
trade directions, rejected trades, traded ownership across save/load, and
unmortgaging both owned and unowned properties.

Run with undefined-behavior instrumentation:

```sh
make -C tests clean
make -C tests test CXXFLAGS='-std=c++14 -g -Wall -Wextra -fsanitize=undefined -fno-sanitize-recover=all'
```

GitHub Actions builds the application and runs these regressions on Linux and
macOS. There is no external test framework to install.

## Maintenance scope and limitations

The maintenance fixes initialize improvement levels, reject unaffordable
construction without accidentally selling an improvement, accept exact cash,
update each building's owner when a trade changes inventory, and safely reject
unmortgaging an unowned building. Tests include saving and reloading a traded
property because inventory-only checks miss the original ownership defect.

This remains a legacy coursework codebase, not a fully audited game engine.
The regression suite is deliberately scoped: it does not establish complete
rule compliance, exhaustive malformed-input handling, or leak-free lifetime
management. Some legacy compiler warnings remain. Only load trusted save files.

## Design documents

- [Original design](design.pdf)
- [Final UML](uml-final.pdf)
