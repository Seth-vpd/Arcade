/*
** EPITECH PROJECT, 2024
** Button.hpp
** File description:
** Button
*/

#pragma once

#include "SFML/Graphics.hpp"

namespace Arcade
{
    class Button
    {
        public:
            Button();
            Button(const sf::Vector2f &position, const std::string &text, const sf::Font &font);
            void setPosition(sf::Vector2f position);
            void draw(sf::RenderWindow &window);
            bool isPressed() const;
            void update(sf::RenderWindow &window);
            ~Button();

        private:
        sf::Vector2f _size = sf::Vector2f(50, 50);
        sf::Vector2f _position = sf::Vector2f(0, 0);
        sf::Color _idleColor = sf::Color(177, 175, 175);
        //sf::Color _idleColor = sf::Color(61, 61, 61);
        sf::Color _pressedColor = sf::Color(51, 51, 51);
        sf::Color _hoverColor = sf::Color(96, 96, 96);
        sf::Text _text;
        sf::RectangleShape _rectangle;
        bool _isPressed = false;
    }; 
}
