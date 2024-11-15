/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL_lib.cpp
*/

#include "../lib/SDL_lib.hpp"

// SDL_lib::SDL_lib()
// {
//     SDL_Init(SDL_INIT_VIDEO);
//     TTF_Init();
//     SDL_CreateWindowAndRenderer(1920, 1080, 0, &_window, &_renderer);
//     SDL_SetWindowTitle(_window, "Arcade (SDL)");
//     IMG_Init(IMG_INIT_PNG);
// 	_font = TTF_OpenFont("lib/resources/visitor.ttf", 200 );
//     // SDL_RenderCopy(_renderer, _textures.loadTexture(_renderer, "Resources/Graphics/arcade_room.png"), nullptr, nullptr);
//     // SDL_RenderPresent(_renderer);
// }

SDL_lib::SDL_lib()
{
    std::cout << "Welcome to SDL !" << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }

    if (TTF_Init() != 0) {
        std::cerr << "Failed to initialize SDL TTF: " << TTF_GetError() << std::endl;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "Failed to initialize SDL IMG: " << IMG_GetError() << std::endl;
    }

    _window = SDL_CreateWindow("Arcade (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_RESIZABLE);
    if (_window == nullptr) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr) {
        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
    }

    _font = TTF_OpenFont("Resources/Graphics/visitor.ttf", 20);
    if (_font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}


void SDL_lib::getInput(Arcade::Core_Data &_data, SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym)
        {
            case SDLK_UP:
                _data._input = Arcade::UP;
                break;
            case SDLK_DOWN:
                _data._input = Arcade::DOWN;
                break;
            case SDLK_LEFT:
                _data._input = Arcade::LEFT;
                break;
            case SDLK_RIGHT:
                _data._input = Arcade::RIGHT;
                break;
            case SDLK_SPACE:
                _data._input = Arcade::SPACE;
                break;
            case SDLK_ESCAPE:
                _data._input = Arcade::ESCAPE;
                _data._focus = Arcade::inCore;
            case SDLK_s:
                changeLib(_data);
                break;    
            default:
                break;
        };
    }
}

void SDL_lib::renderElement(Arcade::mapElement element)
{
    SDL_Rect rect = {element.posX * (int)element.width + 650, element.posY * (int)element.height + 100, (int)element.width, (int)element.height};
    if (element.assetPath == "default") {
        SDL_SetRenderDrawColor(_renderer, element.color.r, element.color.g, element.color.b, element.color.a);
        SDL_RenderFillRect(_renderer, &rect);
    }
    else {
        SDL_RenderCopy(_renderer, _textures.loadTexture(_renderer, element.assetPath), NULL, &rect);
    }
}

void SDL_lib::render(std::vector<std::vector<Arcade::mapElement>> _layout)
{
    for (size_t i = 0; i < _layout.size(); i++) {
        for (size_t j = 0; j < _layout[i].size(); j++) {
            renderElement(_layout[i][j]);
        }
    }
}

void SDL_lib::initButtons(const Arcade::Core_Data _data)
{
    if (_gfxButtons.empty() && _gamesButtons.empty()) {
        int y = 100.0f;
        for (int i = 0; i < _data._gfxLibrariesPath.size(); i++) {
            _gfxButtons.insert(std::make_pair(i, Arcade::SDL_Button(SDL_Point{125, y},
                _data._gfxLibrariesPath[i], _font, _renderer)));
            y += 75.0f;
        }
        y = 100.0f;
        for (int i = 0; i < _data._gamesLibraryPath.size(); i++) {
            _gamesButtons.insert(std::make_pair(i, Arcade::SDL_Button(SDL_Point{1600, y}, _data._gamesLibraryPath[i], _font, _renderer)));
            y += 75.0f;
        }
    }
}

void SDL_lib::checkGamesButtons(Arcade::Core_Data &data)
{
    for (const auto it : _gamesButtons) {
        if (it.second.isPressed()) {
            data._prevFocus = data._focus;
            data._focus = Arcade::loadingGame;
            data._currentGameIndex = it.first;
        }
    }
}

void SDL_lib::checkGfxButtons(Arcade::Core_Data &data)
{
    for (const auto it : _gfxButtons) {
        if (it.second.isPressed()) {
            data._prevFocus = data._focus;
            data._focus = Arcade::loadingLib;
            data._currentGfxIndex = it.first;
        }
    }
}

void SDL_lib::changeLib(Arcade::Core_Data &data)
{
    if (data._focus == Arcade::Focused_prog::inGame) {
        data._currentGfxIndex += 1;
        if (data._currentGfxIndex >= data._gfxLibrariesPath.size() - 1)
                data._currentGfxIndex = 0;
        data._prevFocus = data._focus;
        data._focus = Arcade::loadingLib;
    }
}

void SDL_lib::update(std::vector<std::vector<Arcade::mapElement>> _scene, Arcade::Core_Data &_data)
{
    SDL_Event event;
    initButtons(_data);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            _data._focus = Arcade::quit;
            exitLib();
            return;
        }
        getInput(_data, event);
        for (int i = 0; i < _gamesButtons.size(); i++) {
            _gamesButtons[i].update(_renderer, event);
        }
        for (int i = 0; i < _gfxButtons.size(); i++) {
            _gfxButtons[i].update(_renderer, event);
        }
    }
    checkGamesButtons(_data);
    checkGfxButtons(_data);
    if (_data._focus == Arcade::inGame) {
        render(_scene);
    } else {
        SDL_RenderCopy(_renderer, _textures.loadTexture(_renderer, "Resources/Graphics/arcade_room.png"), nullptr, nullptr);
        for (int i = 0; i < _gamesButtons.size(); i++) {
            _gamesButtons[i].draw(_renderer, event);
        }
        for (int i = 0; i < _gfxButtons.size(); i++) {
            _gfxButtons[i].draw(_renderer, event);
        }
    }
    SDL_RenderPresent(_renderer);
}

SDL_lib::~SDL_lib() {
    std::cout << "See u :)" << std::endl;
    exitLib();
}

void SDL_lib::exitLib() {
    _textures.clear();
    _gfxButtons.clear();
    _gamesButtons.clear();
    if (_font != nullptr) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
    if (_renderer != nullptr) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_window != nullptr) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}


extern "C" Drivers::IGfx *getGraphics()
{
    return new SDL_lib();
}

extern "C" std::string getType()
{
    return "graphical";
}