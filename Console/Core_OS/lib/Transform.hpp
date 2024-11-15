/*
** EPITECH PROJECT, 2024
** Transform
** File description:
** Transform
*/

#pragma once

namespace Arcade
{
    class Transform {
        public:
            Transform() {};
            Transform(int x, int y, double width, double height) {
                _x = x;
                _y = y;
                _width = width;
                _height = height;
            };
            int x() const { return _x; };
            int y() const { return _y; };
            double width() const { return _width; };
            double height() const { return _height; };
            ~Transform() {};

        protected:
        private:
            int _x = 0;
            int _y = 0;
            double _width = 0.0f;
            double _height = 0.0f;
    };
} // namespace Arcade

