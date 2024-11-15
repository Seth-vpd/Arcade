/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** arcade.cpp
*/

#include "./Core_OS/lib/arcade.hpp"
#include "Core_OS/lib/loadMap.hpp"
#include <ncurses.h>
#include <curses.h>

void onLaunch()
{
    srand(time(NULL));
    std::vector<std::string> files{"Resources/Graphics/3d_diagonal.txt", "Resources/Graphics/doh.txt",
        "Resources/Graphics/starwars.txt", "Resources/Graphics/varsity.txt", "Resources/Graphics/swampland.txt",
        "Resources/Graphics/chiseled.txt", "Resources/Graphics/block.txt"};
    std::vector<std::string> ascii = Arcade::loadMap(files[rand() % (files.size() - 1)]);
    for (const auto &i : ascii)
        std::cout << i << std::endl;
    files.clear();
    ascii.clear();
}

void arcade(char **av)
{
    onLaunch();
    Arcade::Core_OS console(av[1]);
    console.run();
    return;
}
