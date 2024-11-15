##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

SFML_FLAGS	=	-lsfml-graphics -lsfml-system -lsfml-window

SFML_PATH	=	./Graphic_Cards/SFML_lib/src/SFML_lib.cpp	\
				./Graphic_Cards/SFML_lib/src/Button.cpp

SDL_FLAGS	=	-lSDL2 -lSDL2_ttf -lSDL2_image

SDL_PATH	=	./Graphic_Cards/SDL_lib/src/SDL_lib.cpp	\
				./Graphic_Cards/SDL_lib/src/SDL_Button.cpp

SRC	=	Console/DlLoader/src/DlLoader.cpp	\
		Console/arcade.cpp	\
		Console/Core_OS/src/Core_OS.cpp	\
		Console/main.cpp

OBJ	=	$(SRC:.cpp=.o)

BIN	=	arcade

all: core games graphicals
	@echo "Done compiling."

core:	$(OBJ)
	g++ -std=c++20 -Wall -Wextra -Werror $(OBJ) -g3 -o $(BIN)

games:
	g++ -shared ./Games/Pacman/src/Pacman.cpp -o ./lib/arcade_pacman.so -fPIC
	g++ -shared ./Games/Snake/src/*.cpp -o ./lib/arcade_snake.so -fPIC

graphicals:
	g++ -shared ./Graphic_Cards/ncurses_lib/src/ncurses_lib.cpp -o ./lib/arcade_ncurses.so -lncurses -fPIC
	g++ -shared $(SDL_PATH) -o ./lib/arcade_sdl2.so $(SDL_FLAGS) -fPIC
	g++ -shared $(SFML_PATH) -o ./lib/arcade_sfml.so $(SFML_FLAGS) -fPIC

clean:
	rm -f $(OBJ)
	rm -f lib/*
	rm -f *~
	rm -f *#

fclean:	clean
	rm -f $(BIN)

re:	fclean all
