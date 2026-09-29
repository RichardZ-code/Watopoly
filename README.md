# Watopoly

A terminal-based, University of Waterloo-themed property trading game in C++14.
Players move around a board, buy properties, trade, pay rent, mortgage buildings,
and save or load game state.

## Project background

This is an undergraduate **team project**, not a claim of sole authorship by the
owner of this repository. This repository was originally populated with uploaded
files, so its upload history is not the original team's development history.
The later correctness changes and regression tests are maintenance work on that
snapshot. Original team attribution should be retained; individual contributions
should be described only when verified by the team or original development records.

## Build and run

Requires a C++14 compiler and Make. Tests additionally require Python 3.

```sh
make -C Watopoly
./Watopoly/watopoly
```

Enter a player count from 2 to 7, then select the character IDs printed by the
game. The existing CLI supports `-testing`, `-load FILE`, and
`-testing -load FILE`. In testing mode the game asks for explicit dice values.
Use the prompts for commands such as `roll`, `next`, `trade`, `improve`,
`mortgage`, `unmortgage`, `assets`, `all`, `save`, and `quit`.

## Regression tests

```sh
make -C tests test
```

The test binary links the production game classes, excluding the interactive
`main.cc` and the unused alternate `textdisplay.cc`. Each named regression runs
in its own process with a timeout. Tests cover initial improvement state,
exact-price and unaffordable purchases, improvement limits, all three trade
forms, rent after transfer, rejected/self/malformed trades, unowned and mortgaged
properties, unmortgaging an unowned building, backward board movement, net-worth
calculation, invalid player-count headers, and a simple save/load round trip.

A local baseline run passed 3 of these 18 checks. The corrected code passed all
18, including the four baseline cases that crashed. CI reruns the checks on
Linux and macOS; a green workflow applies only to the tested revision.

## Design

`Watopoly` coordinates the board and players. `Building` and `Property` provide
polymorphic board behavior; academic buildings, residences, and gyms implement
specific rent rules. Players track their cash, properties, and outstanding debt.
A property's stored owner and its owner's property list must agree after trading.
The original design documents remain in `design.pdf` and `uml-final.pdf`.

## Scope and limitations

This is a maintained student project, not a production game engine or a complete
implementation of every Monopoly rule. These tests address specific reproduced
regressions, not every path through the large interactive command loop. The
legacy save format is not hardened against every malformed file and has known
limitations with multiword names and complete game-state preservation. Only load
trusted saves. The original shared-pointer ownership graph and broader
bankruptcy/auction edge cases remain candidates for a separate review.

No teammate-owned repository, original team history, or repository visibility
is changed by these maintenance fixes.
