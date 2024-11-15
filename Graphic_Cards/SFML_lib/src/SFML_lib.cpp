/*
** EPITECH PROJECT, 2024
** SFML_lib
** File description:
** SFML Class implementation
*/

#include "../lib/SFML_lib.hpp"

SFML_lib::SFML_lib()
{
    createWindow();
    backgroundSprite.setTexture(_textures.loadTexture("Resources/Graphics/background.jpg"));
    font.loadFromFile("Resources/Graphics/visitor.ttf");
    username.setCharacterSize(40);
    username.setFillColor(sf::Color::White);
    username.setFont(font);
    username.setString(inputText);
    sf::Vector2u windowSize = _window.getSize();
    sf::FloatRect size = username.getLocalBounds();
    menuUserPosition = sf::Vector2f((windowSize.x - size.width) / 2, windowSize.y / 2);
    //username.setPosition((windowSize.x - size.width) / 2, windowSize.y / 2);
    username.setPosition(menuUserPosition);
}

SFML_lib::~SFML_lib()
{
    // _textures.clear();
    // _gfxButtons.clear();
    // _gamesButtons.clear();
    destroyWindow();
}

void SFML_lib::getInput(Arcade::Core_Data &data)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        data._input = Arcade::LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        data._input = Arcade::RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        data._input = Arcade::UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        data._input = Arcade::DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        data._input = Arcade::SPACE;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        data._input = Arcade::Input::ESCAPE;
        data._focus = Arcade::Focused_prog::inCore;
    }
}

void SFML_lib::renderElement(Arcade::mapElement element, int posX, int posY)
{
    sf::RectangleShape rect;
    sf::Sprite sprite;
    if (element.assetPath == "default") {
        sf::RectangleShape rect(sf::Vector2f(element.width, element.height));
        rect.setPosition(element.posX * element.width + posX, element.posY * element.height + posY);
        rect.setFillColor(sf::Color(element.color.r, element.color.g, element.color.b, element.color.a));
        _window.draw(rect);
    }
    else {
        sf::Texture text = _textures.loadTexture(element.assetPath);
        sf::Sprite sprite(text);
        sprite.setPosition(sf::Vector2f(element.posX * element.width + posX, element.posY * element.height + posY));
        _window.draw(sprite);
    }
}

void SFML_lib::render(std::vector<std::vector<Arcade::mapElement>> _layout)
{
    sf::Vector2u windowSize = _window.getSize();
    int posX = windowSize.x / 2 - ((_layout[0].size() * _layout[0][0].width) / 2);
    int posY = windowSize.y / 2 - ((_layout.size() * _layout[0][0].width) / 2);
    for (size_t i = 0; i < _layout.size(); i++) {
        for (size_t j = 0; j < _layout[i].size(); j++) {
            renderElement(_layout[i][j], posX, posY);
        }
    }
}

void SFML_lib::createWindow()
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade (SFML)", sf::Style::Resize | sf::Style::Close);
    _isOpen = true;
}

bool SFML_lib::isOpen()
{
    return _isOpen;
}

void SFML_lib::destroyWindow()
{
    _window.close();
}

void SFML_lib::initButtons(const Arcade::Core_Data _data)
{
    if (_gfxButtons.empty() && _gamesButtons.empty()) {
        float y = 100.0f;
        for (int i = 0; i < _data._gfxLibrariesPath.size(); i++) {
            _gfxButtons.insert(std::make_pair(i, Arcade::Button(sf::Vector2f(125.0f, y), _data._gfxLibrariesPath[i], font)));
            y += 75.0f;
        }
        y = 100.0f;
        for (int i = 0; i < _data._gamesLibraryPath.size(); i++) {
            _gamesButtons.insert(std::make_pair(i, Arcade::Button(sf::Vector2f(1600.0f, y), _data._gamesLibraryPath[i], font)));
            y += 75.0f;
        }
    }
}

void SFML_lib::checkGamesButtons(Arcade::Core_Data &data)
{
    for (const auto it : _gamesButtons) {
        if (it.second.isPressed()) {
            data._prevFocus = data._focus;
            data._focus = Arcade::Focused_prog::loadingGame;
            data._currentGameIndex = it.first;
        }
    }
}

void SFML_lib::checkGfxButtons(Arcade::Core_Data &data)
{
    for (const auto it : _gfxButtons) {
        if (it.second.isPressed()) {
            data._prevFocus = data._focus;
            data._focus = Arcade::Focused_prog::loadingLib;
            data._currentGfxIndex = it.first;
        }
    }
}

void SFML_lib::updateUserText()
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(_window);
    sf::Vector2f mousePos(localPosition.x, localPosition.y);
    if (username.getGlobalBounds().contains(mousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            canEnterName = true;
        username.setStyle(sf::Text::Underlined);
    }
    else
        username.setStyle(sf::Text::Regular);
}

void SFML_lib::changeLib(Arcade::Core_Data &data)
{
    if (data._focus == Arcade::inGame) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            data._currentGfxIndex += 1;
            if (data._currentGfxIndex >= data._gfxLibrariesPath.size() - 1)
                data._currentGfxIndex = 0;
            data._prevFocus = data._focus;
            data._focus = Arcade::loadingLib;
        }
    }
}

void SFML_lib::update(std::vector<std::vector<Arcade::mapElement>> _scene, Arcade::Core_Data &_data)
{
    sf::Event event;
    initButtons(_data);
    sf::Vector2i localPosition = sf::Mouse::getPosition(_window);
    sf::Vector2f mousePos(localPosition.x, localPosition.y);
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            _data._focus = Arcade::Focused_prog::quit;
            exitLib();
            return;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (_data._focus == Arcade::inGame) {
                _data._focus = Arcade::inCore;
            } else {
                _data._focus = Arcade::inGame;
            }
        }
        else if (canEnterName == true && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b' && !_data._username.empty()) {
                _data._username.pop_back();
            }
            else if (event.text.unicode < 128) {
                _data._username.push_back(static_cast<char>(event.text.unicode));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                canEnterName = false;
            }
        }
    }
    _window.clear();
    getInput(_data);
    checkGamesButtons(_data);
    checkGfxButtons(_data);
    username.setString(_data._username);
    if (_data._focus == Arcade::inGame) {
        // if (_data._username == "Anonymous")
        //     username.setString("Anonymous");
        username.setPosition(inGameUserPosition);
        _window.draw(username);
        changeLib(_data);
        render(_scene);
    } else {
        _window.draw(backgroundSprite);
        username.setPosition(menuUserPosition);
        _window.draw(username);
        updateUserText();
        for (int i = 0; i < _gamesButtons.size(); i++) {
            _gamesButtons[i].draw(_window);
        }
        for (int i = 0; i < _gfxButtons.size(); i++) {
            _gfxButtons[i].draw(_window);
        }
    }
    _window.display();
}

void SFML_lib::clearScreen()
{
    _window.clear();
}

void SFML_lib::exitLib()
{
    _textures.clear();
    _gfxButtons.clear();
    _gamesButtons.clear();
    destroyWindow();
}

extern "C" Drivers::IGfx *getGraphics()
{
    return new SFML_lib();
}

extern "C" std::string getType()
{
    return "graphical";
}