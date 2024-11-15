/*
** EPITECH PROJECT, 2024
** Error
** File description:
** Error
*/

#pragma once

#include <iostream>

namespace Arcade
{
    class Error : public std::exception {
        public:
            Error(std::string str) { msg = str.c_str(); };
            ~Error() {};
            const char *what() const noexcept override { return msg; };

        protected:
        private:
            const char *msg;
    };
}

