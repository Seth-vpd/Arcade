/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake.cpp
*/

#include "../lib/Snake.hpp"
#include <thread>
#include <chrono>

Snake::Snake()
{
    srand(time(NULL));
    _map = Arcade::loadMap("Resources/Snake/map.txt");
    initGame();
    generateFruit();
}

Snake::~Snake()
{
}

void Snake::setUpMap()
{
    for (int i = 0; i < _map.size(); i++) {
        std::vector<Arcade::mapElement> line;
        for (int j = 0; j < _map[i].size(); j++) {
            Arcade::mapElement data;
            double width = 20;
            double height = 20;
            if (_map[i][j] == '#')
                data = {width, height, j, i, {0, 0, 255, 255}, "Resources/Snake/deadblock.png", _map[i][j]};
            if (_map[i][j] == ' ')
                data = {width, height, j, i, {0, 0, 0, 255}, "default", _map[i][j]};
            line.push_back(data);
        }
        _layout.push_back(line);
    }
}

void  Snake::initGame()
{
    _snake.clear();
    _layout.clear();
    _score = 0;
    setUpMap();
    int InitialX = 17;
    int InitialY = 17;
    Arcade::Color snakeColor = {0, 255, 0, 255};
    for (int i = 0; i <= initialLength; i++) {
        Arcade::mapElement segment = {20, 20, InitialX, InitialY - i, snakeColor, "Resources/Snake/snake_body.png", 'o'};
        _snake.push_back(segment);
    }
    hasEaten = false;
    feeding();
}

void Snake::clearLayout()
{
    for (const auto& segment : _snake) {
        if (segment.posX > 0 && segment.posX < (_layout[0].size() - 1) &&
            segment.posY > 0 && segment.posY < (_layout.size() - 1)) {
                _layout[segment.posY][segment.posX] =  {20, 20, segment.posX, segment.posY, {0, 0, 0, 255}, "default", ' '};
        }
    }
}

void Snake::update(Arcade::Core_Data &_data)
{
    head = _snake.front();
    clearLayout();
    snakeMotion();
    changeDirection(_data._input);
    _data.currentScore = _score;
    if (checkCollision()) {
        initGame();
        generateFruit();
    }
    for (const auto& segment : _snake) {
        if (segment.posX > 0 && segment.posX < (_layout[0].size() - 1) &&
            segment.posY > 0 && segment.posY < (_layout.size() - 1)) {
                _layout[segment.posY][segment.posX] = segment;
        }
    }
}

std::vector<std::vector<Arcade::mapElement>> Snake::getLayout() const
{
    return _layout;
}

int Snake::getScore() const
{
    return _score;
}

void Snake::changeDirection(Arcade::Input newDirection)
{
    if ((newDirection == Arcade::Input::UP && _currentDirection != Arcade::Input::DOWN) ||
        (newDirection == Arcade::Input::DOWN && _currentDirection != Arcade::Input::UP) ||
        (newDirection == Arcade::Input::RIGHT && _currentDirection != Arcade::Input::LEFT) ||
        (newDirection == Arcade::Input::LEFT && _currentDirection != Arcade::Input::RIGHT)) {
            _currentDirection = newDirection;

    }
}

void Snake::snakeMotion()
{
    Snake::head = _snake.front();

    switch (_currentDirection)
    {
    case Arcade::Input::UP:
        head.posY -= 1; break;
    case Arcade::Input::DOWN:
        head.posY += 1; break;
    case Arcade::Input::RIGHT:
        head.posX += 1; break;
    case Arcade::Input::LEFT:
        head.posX -= 1; break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    _snake.insert(_snake.begin(), head);
    feeding();
}

bool Snake::checkCollision()
{
    if (head.posX < 0 || head.posX >= _layout[0].size() ||
        head.posY < 0 || head.posY >= _layout.size()) {
        return true;
    }

    for (int i = 1; i < _snake.size(); i++) {
        if (_snake[i].posX == head.posX && _snake[i].posY == head.posY) {
            return true;
        }
    }

    if (_layout[head.posY][head.posX].element == '#') {
        return true;
    }

    return false;
}

bool Snake::checkOccupied(int x, int y)
{
    for (const auto& segment : _snake) {
        if (segment.posX == x && segment.posY == y)
            return true;
    }
    return false;
}

void Snake::feeding()
{
    if (head.posX == fruitX && head.posY == fruitY) {
        hasEaten = true;
        _score += 10;
        generateFruit();
    } else {
        hasEaten = false;
    }

    if (!hasEaten) {
    _snake.pop_back();
    }
}

void Snake::generateFruit()
{
    do {
        fruitX = rand() % (_layout[0].size() - 1);
        fruitY = rand() % (_layout.size() - 1);
    } while (_layout[fruitY][fruitX].element != ' ');
    fruit = {20, 20, fruitX, fruitY, {255, 0, 0, 255}, "Resources/Snake/snake_head.png", 'F'};
    _layout[fruitY][fruitX] = fruit;
}


extern "C" Drivers::IGame *getGame()
{
    return new Snake();
}

extern "C" std::string getType()
{
    return "game";
}