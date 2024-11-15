/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core_OS.hpp
*/

#ifndef CONSOLE_OS_H
    #define CONSOLE_OS_H
    //#include "./arcade.hpp"
    #include "../../DlLoader/lib/DlLoader.hpp"
    #include "../../Drivers/Drivers.hpp"

namespace Arcade {
    class Core_OS {
        public:
            Core_OS();
            Core_OS(char *gfx_path);
            ~Core_OS();
            void run();
            void menu(std::vector<std::vector<Arcade::mapElement>> _scene, Arcade::Core_Data _data);
            void setIGfx(std::string _dl_filepath);
            void setIGame(std::string _dl_filepath);

        protected:
        private:
            Arcade::DlLoader<Drivers::IGfx> _gfxDriverLoader = Arcade::DlLoader<Drivers::IGfx>();;
            Arcade::DlLoader<Drivers::IGame> _gameDriverLoader = Arcade::DlLoader<Drivers::IGame>();;
            std::unique_ptr<Drivers::IGfx> _currentGfx;
            std::unique_ptr<Drivers::IGame> _currentGame;
            
            std::vector<std::vector<Arcade::mapElement>> _scene;
            Arcade::Core_Data _data;
    };
}


#endif /* !CONSOLE_OS_H */
