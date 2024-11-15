/*
** EPITECH PROJECT, 2024
** SFML_lib
** File description:
** SFML display
*/

#pragma once

#include "../../../Console/Core_OS/lib/Input.hpp"
#include "../../../Console/Core_OS/lib/mapElement.hpp"
#include "../../../Console/Drivers/GFX_D/IGfx.hpp"
#include "../../../Console/Core_OS/lib/Error.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <map>

class TextureData {
    public:
        TextureData() {};
        ~TextureData() {
            clear();
        }
        sf::Texture& loadTexture(const std::string& filename) {
            auto it = textures.find(filename);
            if (it != textures.end())
                return it->second;
            else {
                sf::Texture texture;
                if (texture.loadFromFile(filename)) {
                    textures.insert({filename, texture});
                    return textures[filename];
                } else {
                    throw Arcade::Error("Failed to load image");
                }
            }
        };
        void clear() {
            textures.clear();
        };

    private:
        std::map<std::string, sf::Texture> textures;
};

class SFML_lib : public Drivers::IGfx {
    public:
        SFML_lib();
        ~SFML_lib();
        void createWindow();
        void destroyWindow();
        bool isOpen();
        void getInput(Arcade::Core_Data &data);
        void render(std::vector<std::vector<Arcade::mapElement>> _layout);
        void renderElement(Arcade::mapElement element, int posX, int posY);
        void clearScreen();
        void initButtons(const Arcade::Core_Data _data);
        void checkGamesButtons(Arcade::Core_Data &data);
        void checkGfxButtons(Arcade::Core_Data &data);
        void updateUserText();
        void changeLib(Arcade::Core_Data &data);
        void displayGame(std::vector<std::vector<Arcade::mapElement>> _scene, Arcade::Core_Data _data);
        void update(std::vector<std::vector<Arcade::mapElement>> _scene, Arcade::Core_Data &_data);
        void exitLib();

    protected:
    private:
        sf::RenderWindow _window;
        TextureData _textures;
        sf::Sprite backgroundSprite;
        bool _isOpen;
        sf::Font font;
        std::map<int, Arcade::Button> _gfxButtons;
        std::map<int, Arcade::Button> _gamesButtons;
        std::string inputText = "Enter your username: ";
        sf::Text username;
        bool canEnterName = false;
        sf::Vector2f menuUserPosition;
        sf::Vector2f inGameUserPosition = sf::Vector2f(100, 100);
};

extern "C" Drivers::IGfx *getGraphics();
extern "C" std::string getType();