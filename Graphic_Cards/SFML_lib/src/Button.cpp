/*
** EPITECH PROJECT, 2024
** Button
** File description:
** Button
*/

#include "../lib/Button.hpp"
#include <iostream>

namespace Arcade
{   
    Button::Button()
    {
        _rectangle.setSize(_size);
        _rectangle.setFillColor(_idleColor);
        _rectangle.setOutlineThickness(1);
        _rectangle.setOutlineColor(sf::Color::Black);
        _rectangle.setPosition(_position);
    }

    Button::Button(const sf::Vector2f &position, const std::string &text, const sf::Font &font) {
        _text.setCharacterSize(25);
        _text.setFillColor(sf::Color::Black);
        _text.setFont(font);
        _text.setString(text);

        sf::FloatRect textBounds = _text.getLocalBounds();
        float width = textBounds.width + 40.0f;
        float height = textBounds.height + 30.0f;
        _rectangle.setSize(sf::Vector2f(width, height));
        _rectangle.setFillColor(_idleColor);
        _rectangle.setOutlineThickness(1);
        _rectangle.setOutlineColor(sf::Color::Black);
        _rectangle.setPosition(position);
        _text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                        textBounds.top + textBounds.height / 2.0f);
        _text.setPosition(_rectangle.getPosition() +
                          sf::Vector2f(_rectangle.getSize().x / 2.0f,
                                       _rectangle.getSize().y / 2.0f));
    }

    void Button::setPosition(sf::Vector2f position) {
        _rectangle.setPosition(position);
        sf::FloatRect textBounds = _text.getLocalBounds();
        _text.setPosition(_rectangle.getPosition() +
                          sf::Vector2f(_rectangle.getSize().x / 2.0f,
                                       _rectangle.getSize().y / 2.0f));
    }

    void Button::draw(sf::RenderWindow &window) {
            update(window);
            window.draw(_rectangle);
            window.draw(_text);
    }

    bool Button::isPressed() const { return _isPressed; };

    void Button::update(sf::RenderWindow &window) {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos(localPosition.x, localPosition.y);
        _rectangle.setFillColor(_idleColor);
        if (_rectangle.getGlobalBounds().contains(mousePos)) {
            _rectangle.setFillColor(_hoverColor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                _rectangle.setFillColor(_pressedColor);
                _isPressed = true;
            }
            else {
                _isPressed = false;
            }
        }
    }

    Button::~Button() {}
}