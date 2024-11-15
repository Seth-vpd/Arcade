/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman.hpp
*/

#ifndef PACMAN_H
    #define PACMAN_H
    #include "../../../Console/Drivers/GAME_DISK_D/IGame.hpp"
    #include "../../../Console/Core_OS/lib/mapElement.hpp"
    #include "../../../Console/Core_OS/lib/Input.hpp"
    #include "../../../Console/Core_OS/lib/loadMap.hpp"
    #include <map>
    #include <utility>
    #include <sstream>
    #include <string>
    #include <random>
    #include <vector>

class Pacman : public Drivers::IGame {
    public:
        Pacman();
        ~Pacman();
        //void loadMap(const std::string filename);
        void init();
        int getScore() const;
        void updateDirection(const Arcade::Input input);
        void movePlayer();
        std::vector<std::vector<Arcade::mapElement>> getLayout() const;
        void update(Arcade::Core_Data &_data);
        std::pair<size_t, size_t> getElementPos(char elem);

    protected:
    private:
        std::vector<std::vector<Arcade::mapElement>> _layout;
        Arcade::mapElement _player;
        std::vector<std::string> _map;
        std::map<char, std::string> _dictionnary;
        std::map<std::pair<int, int>, std::string> _playerAnimation;
        std::pair<int, int> _direction; // First int:-> X <---> Second int:-> Y
        int _score;
};

extern "C" Drivers::IGame *getGame();
extern "C" std::string getType();

#endif /* !PACMAN_H */
