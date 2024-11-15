/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGame.hpp
*/

#ifndef IGAME_H
    #define IGAME_H
    #include "../../Core_OS/lib/mapElement.hpp"
    #include "../../Core_OS/lib/Input.hpp"
    #include <vector>

namespace Drivers {
    class IGame {
        public:
            virtual ~IGame() {};
            virtual std::vector<std::vector<Arcade::mapElement>> getLayout() const = 0;
            virtual int getScore() const = 0;
            virtual void update(Arcade::Core_Data &_data) = 0;

        protected:
        private:
    };
}

#endif /* !IGAME_H */
