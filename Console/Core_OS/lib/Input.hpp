/*
** EPITECH PROJECT, 2024
** Input
** File description:
** Input
*/

#pragma once

#include <iostream>
#include <vector>

namespace Arcade
{
    enum Input {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE,
        ESCAPE,
        _none
    };
}

namespace Arcade {
    enum Focused_prog {
        inCore,
        inGame,
        loadingLib,
        loadingGame,
        quit
    };

    struct Core_Data {
        Input _input;
        Focused_prog _focus;
        Focused_prog _prevFocus;
        std::vector<std::string> _gfxLibrariesPath;
        std::vector<std::string> _gamesLibraryPath;
        int _currentGfxIndex;
        int _currentGameIndex;
        int currentScore;
        std::string _username;
    };
}