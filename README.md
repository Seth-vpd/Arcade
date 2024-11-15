# Arcade

Arcade is a retro platform arcade game developed as part of the Epitech curriculum. It's a gaming platform that allows users to choose and play various games, each implemented as a dynamic library. The program also keeps track of player scores. The graphics are rendered using different graphics libraries, which are also loaded as dynamic libraries at runtime.

## Features

- Choose from a selection of games implemented as dynamic libraries
- Multiple graphics libraries supported, loaded dynamically at runtime
- Scoreboard to track player scores
- Ability to switch between games and graphics libraries while the program is running

## Games

The following games are implemented:

- Snake
- Pacman (not entirely implemented tho :=[ )

## Graphics Libraries

The project supports the following graphics libraries:

- NCurses (`arcade_ncurses.so`)
- SDL2 (`arcade_sdl2.so`)
- SFML (`arcade_sfml.so`)

## Building

The project can be built using a Makefile.

### Makefile

The Makefile provides the following rules:

- `all`: Build the entire project
- `core`: Build only the core arcade program
- `games`: Build only the game libraries
- `graphicals`: Build only the graphics libraries
- `re`, `clean`, `fclean`: Rebuild, clean object files, clean everything

## Usage

Run the program with the initial graphics library as an argument:
`./arcade ./lib/arcade_ncurses.so`

## Documentation

Refer to the `doc/` directory for documentation on implementing new graphics libraries or games compatible with the system.
