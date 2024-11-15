/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman.cpp
*/

#include "../lib/Pacman.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

Pacman::Pacman()
{
    std::cout << "Hey From Pacman :)" << std::endl;
    _map = Arcade::loadMap("Resources/Pacman/map.txt");
    _direction = std::make_pair(0, 0);
    _dictionnary['#'] = "default 0,0,255,255";
    _dictionnary['.'] = "Resources/Pacman/pacgum.png default";
    _dictionnary['-'] = "default 255,255,255,255";
    _dictionnary[' '] = "default 0,0,0,0";
    _dictionnary['F'] = "Resources/Pacman/Fruit_Cherry.png default";
    _dictionnary['P'] = "Resources/Pacman/right.png default";
    _dictionnary['G'] = "Resources/Pacman/orangeghost.png default";
    _playerAnimation[std::make_pair(1, 0)] = "Resources/Pacman/right.png";
    _playerAnimation[std::make_pair(-1, 0)] = "Resources/Pacman/left.png";
    _playerAnimation[std::make_pair(0, -1)] = "Resources/Pacman/up.png";
    _playerAnimation[std::make_pair(0, 1)] = "Resources/Pacman/down.png";
    init();
}

Pacman::~Pacman()
{
    _map.clear();
}

std::vector<std::vector<Arcade::mapElement>> Pacman::getLayout() const
{
    return _layout;
}

int Pacman::getScore() const { return _score; }

Arcade::Color getColor(std::string data)
{
    std::vector<double> rgba;
    if (data != "default") {
        std::stringstream ss(data);
        std::string value;
        while (getline(ss, value, ',')) {
            size_t a = stof(value);
            rgba.push_back(a);
        }
    }
    Arcade::Color color;
    if (!rgba.empty()) {
        Arcade::Color color = {rgba[0], rgba[1], rgba[2], rgba[3]}; 
        return color;
    }
    return color;
}

void Pacman::init()
{
    for (size_t i = 0; i < _map.size(); i++) {
        std::vector<Arcade::mapElement> line;
        for (size_t j = 0; j < _map[i].size(); j++) {
            double width = 21.0f;
            double height = 21.0f;
            std::stringstream ss(_dictionnary[_map[i][j]]);
            std::string data;
            ss >> data;
            std::string path(data);
            ss >> data;
            Arcade::Color color = getColor(data);
            Arcade::mapElement element = {width, height, (int)j, (int)i, color, path, _map[i][j]};
            line.push_back(element);
        }
        _layout.push_back(line);
    }
}

void Pacman::updateDirection(const Arcade::Input input)
{
    std::pair<size_t, size_t> pos = getElementPos('P');
    std::pair<int, int> newDirection;
    if (input == Arcade::LEFT) {
        newDirection = std::make_pair(-1, 0);
    }
    else if (input == Arcade::RIGHT) {
        newDirection = std::make_pair(1, 0);
    }
    else if (input == Arcade::UP) {
        newDirection = std::make_pair(0, -1);
    }
    else if (input == Arcade::DOWN) {
        newDirection = std::make_pair(0, 1);
    } else {
        newDirection = std::make_pair(0, 0);
    }
    size_t newX = pos.first + newDirection.first;
    size_t newY = pos.second + newDirection.second;
    if (_layout[newY][newX].element != '#')
        _direction = newDirection;
}

std::pair<size_t, size_t> Pacman::getElementPos(char elem) {
    for (size_t i = 0; i < _layout.size(); i++) {
        for (size_t j = 0; j < _layout[i].size(); j++) {
            if (_layout[i][j].element == elem) {
                return std::make_pair(j, i);
            }
        }
    }
    return std::make_pair(-1, -1);
}

void Pacman::movePlayer()
{
    std::pair<size_t, size_t> pos = getElementPos('P');
    std::string path;
    size_t newX = (pos.first + _direction.first + _layout[pos.second].size()) % _layout[pos.second].size();
    size_t newY = pos.second + _direction.second;
    if (_layout[newY][newX].element == 'G') {
        _direction = std::make_pair(0, 0);
        _layout.clear();
        init();
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
        _score = 0;
        return;
    }
    if (_layout[newY][newX].element == '.') {
        _score += 10;
    }
    if (_layout[newY][newX].element != '#') {
        Arcade::mapElement newSpace = {21.0f, 21.0f, (int)pos.first, (int)pos.second, {0, 0, 0, 0}, "default", ' '};
        Arcade::mapElement Player = {21.0f, 21.0f, (int)newX, (int)newY, {0, 0, 0, 0}, _playerAnimation[_direction], 'P'};
        _layout[newY][newX] = Player;
        _layout[pos.second][pos.first] = newSpace;
    }
}

void Pacman::update(Arcade::Core_Data &_data)
{
    updateDirection(_data._input);
    _data.currentScore = _score;
    if (_direction != std::make_pair(0, 0))
        movePlayer();
    std::this_thread::sleep_for(std::chrono::milliseconds(90));
}

extern "C" Drivers::IGame *getGame()
{
    return new Pacman();
}

extern "C" std::string getType()
{
    return "game";
}