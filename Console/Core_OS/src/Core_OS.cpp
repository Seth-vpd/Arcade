/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core_OS.cpp
*/

#include "../lib/Core_OS.hpp"
#include <iostream>

Arcade::Core_OS::Core_OS()
{

}

Arcade::Core_OS::Core_OS(char *gfx_path)
{
    _data._focus = inCore;
    _data._prevFocus = _data._focus;
    _data._input = _none;
    _data._currentGameIndex = 0;
    _data._currentGfxIndex = 0;
    _data._username = "Anonymous";

    std::cout << "Booting Console OS..." << std::endl;
    setIGfx(gfx_path);
    for (const auto& entry : std::filesystem::directory_iterator("lib/")) {
        std::string filename = entry.path().string();
        if (filename != gfx_path && filename.compare("lib/lib")) {
            _gfxDriverLoader.load(filename);
            _gameDriverLoader.load(filename);
            if (_gfxDriverLoader.getType() == "graphical") {
                _data._gfxLibrariesPath.push_back(filename);
            }
            else if (_gameDriverLoader.getType() == "game") {
                _data._gamesLibraryPath.push_back(filename);
            }
        }
    }
}

Arcade::Core_OS::~Core_OS()
{
    std::cout << "Shutting Down Console..." << std::endl;
}

void Arcade::Core_OS::run()
{
    while (1) {
        if (_data._focus == Arcade::quit) {
            return;
        }
        if (_currentGame != nullptr) {
            _currentGame->update(_data);
        }
        if (_currentGfx != nullptr) {
            if (_currentGame == nullptr) {
                std::vector<std::vector<Arcade::mapElement>> empty;
                _currentGfx->update(empty, _data);    
            }
            else {
                _currentGfx->update(_currentGame->getLayout(), _data);
            }
        }
        if (_data._focus == Arcade::Focused_prog::loadingGame) {
            setIGame(_data._gamesLibraryPath[_data._currentGameIndex]);
        }
        if (_data._focus == Arcade::Focused_prog::loadingLib) {
            setIGfx(_data._gfxLibrariesPath[_data._currentGfxIndex]);
        }
    }
}

void Arcade::Core_OS::setIGfx(std::string _dl_filepath)
{
    try {
        if (_currentGfx != nullptr) {
            _currentGfx->exitLib();
        }
        _gfxDriverLoader.load(_dl_filepath);
        if (_data._gfxLibrariesPath.empty())
            _data._gfxLibrariesPath.push_back(_dl_filepath);
        _currentGfx = _gfxDriverLoader.getInstance(std::string("getGraphics"));
        _data._focus = _data._prevFocus;
    } catch (const Arcade::Error &e) {
        std::cerr << e.what() << std::endl;
        exit (84);
    }
}

void Arcade::Core_OS::setIGame(std::string _dl_filepath)
{
    try {
        _gameDriverLoader.load(_dl_filepath);
        _currentGame = _gameDriverLoader.getInstance(std::string("getGame"));
        _data._focus = Arcade::Focused_prog::inGame;
    } catch (const Arcade::Error &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}
