/*
** EPITECH PROJECT, 2024
** SDL_Button
** File description:
** SDL_Button
*/

#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace Arcade {
    class SDL_Button {
    public:
        SDL_Button();
        SDL_Button(const SDL_Point& position, const std::string& text, TTF_Font* font, SDL_Renderer *renderer);
        void setPosition(const SDL_Point& position);
        void draw(SDL_Renderer* renderer, SDL_Event &event);
        bool isPressed() const;
        void update(SDL_Renderer *renderer, SDL_Event& event);
        ~SDL_Button();

    private:
        SDL_Point _size = {50, 50};
        SDL_Point _position = {0, 0};
        SDL_Point _textSize;
        SDL_Color _idleColor = {177, 175, 175};
        SDL_Color _pressedColor = {91, 51, 51};
        SDL_Color _hoverColor = {96, 96, 96};
        SDL_Texture* _textTexture = nullptr;
        SDL_Rect _rectangle;
        bool _isPressed = false;
        bool _isHovered = false;
    };
}
