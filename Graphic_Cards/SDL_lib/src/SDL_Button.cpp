/*
** EPITECH PROJECT, 2024
** SDL_Button
** File description:
** SDL_Button
*/

#include "../lib/SDL_Button.hpp"

namespace Arcade {
    SDL_Button::SDL_Button() {
        _rectangle = { _position.x, _position.y, _size.x, _size.y };
    }

    SDL_Button::SDL_Button(const SDL_Point& position, const std::string& text, TTF_Font* font, SDL_Renderer *renderer) {
        _position = position;
        _rectangle = { _position.x, _position.y, _size.x, _size.y };

        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {0, 0, 0});
        if (surface == nullptr) {
            return;
        }
        _textTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (_textTexture == nullptr) {
            return;
        }
        SDL_QueryTexture(_textTexture, nullptr, nullptr, &_textSize.x, &_textSize.y);
        _rectangle = {position.x, position.y, _textSize.x + 25, _textSize.y + 20};
    }

    void SDL_Button::setPosition(const SDL_Point& position) {
        _position = position;
        _rectangle.x = _position.x;
        _rectangle.y = _position.y;
    }

    void SDL_Button::draw(SDL_Renderer* renderer, SDL_Event &event) {
        update(renderer, event);
        SDL_RenderFillRect(renderer, &_rectangle);
        if (_textTexture != nullptr) {
            SDL_SetTextureColorMod(_textTexture, 0, 0, 0);
            int offsetX = (_rectangle.w - _textSize.x) / 2;
            int offsetY = (_rectangle.h - _textSize.y) / 2;
            SDL_Rect textRect = {_rectangle.x + offsetX, _rectangle.y + offsetY, _textSize.x, _textSize.y};
            SDL_RenderCopy(renderer, _textTexture, nullptr, &textRect);
        }
    }

    bool SDL_Button::isPressed() const {
        return _isPressed;
    }

    void SDL_Button::update(SDL_Renderer *renderer, SDL_Event& event) {
        SDL_Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);
        if (SDL_PointInRect(&mouse, &_rectangle)) {
            SDL_SetRenderDrawColor(renderer, _hoverColor.r, _hoverColor.g, _hoverColor.b, SDL_ALPHA_OPAQUE);
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                SDL_SetRenderDrawColor(renderer, _pressedColor.r, _pressedColor.g, _pressedColor.b, SDL_ALPHA_OPAQUE);
                std::cout << "Pressed" << std::endl;
                _isPressed = true;
            } else
                _isPressed = false;
        }
        else {
            SDL_SetRenderDrawColor(renderer, _idleColor.r, _idleColor.g, _idleColor.b, SDL_ALPHA_OPAQUE);
        }
    }

    SDL_Button::~SDL_Button() {
        // if (_textTexture != nullptr) {
        //     SDL_DestroyTexture(_textTexture);
        // }
    }
}