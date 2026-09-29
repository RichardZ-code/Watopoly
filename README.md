# Watopoly

A University of Waterloo-themed, terminal-based Monopoly game in C++14.
Originally developed as an undergraduate **team project**. This repository is a
later source snapshot, not the original team development history; its upload
commits should not be interpreted as sole authorship.

## Build and run

Requires a C++14 compiler and Make. Tests additionally require Python 3.

```sh
make -C Watopoly
./Watopoly/watopoly
```

Select 2 to 7 players and character tokens when prompted. Enter `help` for
commands or `quit` to exit. The `-testing` flag accepts manually supplied dice;
`-load FILE` reads a saved game. These are local terminal modes, not network play.

## Implementation

`Watopoly/Watopoly.cc` coordinates the board, turns, trades, and persistence.
`Player` tracks cash, properties, and debt. Polymorphic building classes implement
academic properties, residences, gyms, and non-property board actions.
The original design notes and UML diagrams remain in the repository.

## Correctness maintenance

This maintenance pass initializes academic improvement levels, fixes buying with
exact funds and failed purchases incorrectly selling improvements, keeps traded
properties' recorded owners consistent with both players' inventories, rejects
self-trades and malformed cash amounts, and avoids collecting rent or dereferencing
owners on unowned or mortgaged properties. Zero-player and nonnumeric save headers
are rejected before player indexing.

## Tests

```sh
make -C tests test
```

The regression suite runs 18 isolated cases covering improvements, the three trade
forms, rejected/self/malformed trades, rent after transfer, unowned-property
handling, a simple trade/save/load round trip, and invalid player count.
Each case has a timeout; a crash fails the test rather than stopping the whole suite.
CI builds the game, runs these tests, and checks startup/quit on Linux and macOS.

## Limitations

This is a maintained coursework snapshot, not a claim of a fully audited game.
The regression suite is focused, not exhaustive. The legacy save parser, multiword
player-name handling, bankruptcy/auction edge cases, and shared-pointer ownership
cycles need broader review. Compiler warnings remain in legacy code. No new license,
publication permission, or historical teammate contribution is inferred here.
