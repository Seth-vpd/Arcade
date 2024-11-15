/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake.hpp
*/

#ifndef SNAKE_H
#define SNAKE_H
#include "../../../Console/Drivers/GAME_DISK_D/IGame.hpp"
#include "../../../Console/Core_OS/lib/mapElement.hpp"
#include "../../../Console/Core_OS/lib/Input.hpp"
#include "../../../Console/Core_OS/lib/loadMap.hpp"
#include <fstream>
#include <stdio.h>
#include <unistd.h>

class Snake : public virtual Drivers::IGame
{
public:
    Snake();
    ~Snake();
    void setUpMap();
    std::vector<std::vector<Arcade::mapElement>> getLayout() const;
    int getScore() const;
    void update(Arcade::Core_Data &_data);
    void initGame();
    void changeDirection(Arcade::Input newDirection);
    void snakeMotion();
    bool checkCollision();
    void generateFruit();
    void feeding();
    bool checkOccupied(int x, int y);
    void clearLayout();

protected:
private:
    std::vector<std::vector<Arcade::mapElement>> _layout;
    std::vector<std::string> _map;
    std::vector<Arcade::mapElement> _snake;
    Arcade::mapElement head;
    int initialLength = 4;
    int _score;
    Arcade::Input _currentDirection = Arcade::Input::DOWN;
    Arcade::mapElement fruit;
    int fruitX;
    int fruitY;
    bool hasEaten;
};

extern "C" Drivers::IGame *getGame();

extern "C" std::string getType();

#endif /* !SNAKE_H */