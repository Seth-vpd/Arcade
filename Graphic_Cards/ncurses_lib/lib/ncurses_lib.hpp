/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ncurses_lib.hpp
*/

#ifndef NCURSES_LIB_H
    #define NCURSES_LIB_H
    #include <ncurses.h>
    #include <curses.h>
    #include "../../../Console/Drivers/GFX_D/IGfx.hpp"
    #include "../../../Console/Core_OS/lib/mapElement.hpp"
    #include "../../../Console/Core_OS/lib/Color.hpp"
    #include "../../../Console/Core_OS/lib/Input.hpp"

class ncurses_lib : public Drivers::IGfx {
    public:
        ncurses_lib();
        ~ncurses_lib();
        void renderElement(Arcade::mapElement Element, std::vector<std::vector<Arcade::mapElement>> _scene);
        void render(std::vector<std::vector<Arcade::mapElement>> _scene);
        void getInput(Arcade::Core_Data &_data);
        void ncurses_menu(Arcade::Core_Data &_data);
        std::vector<std::string> read_Ascii_art(const std::string filename);
        void update(std::vector<std::vector<Arcade::mapElement>> _layout, Arcade::Core_Data &_data);
        void exitLib();
        void render_Ascii_art(std::vector<std::string> n_map);

    
    protected:
    private:
};

extern "C" Drivers::IGfx *getGraphics();
extern "C" std::string getType();

#endif /* !NCURSES_LIB_H */