/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGFX_D
*/

#ifndef IGFX_D_H
    #define IGFX_D_H
    #include <iostream>
    #include "../../Core_OS/lib/mapElement.hpp"
    #include "../../Core_OS/lib/Input.hpp"
    #include <vector>

namespace Drivers {
    class IGfx {
        public:
            virtual ~IGfx() {};
            virtual void update(std::vector<std::vector<Arcade::mapElement>> _scene, Arcade::Core_Data &_data) = 0;
            virtual void exitLib() = 0;
    
        protected:
        private:
    };
}

#endif /* !IGFX_D_H */
