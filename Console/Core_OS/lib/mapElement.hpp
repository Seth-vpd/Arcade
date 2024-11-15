/*
** EPITECH PROJECT, 2024
** mapData
** File description:
** Structure relative to each map data
*/

#pragma once
#include <iostream>
#include "Color.hpp"

namespace Arcade {
    struct mapElement
    {
        double width;
        double height;
        int posX;
        int posY;
        Arcade::Color color;
        std::string assetPath;
        char element;
    };
}  