/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL_lib.hpp
*/

#ifndef SDL_LIB_H
    #define SDL_LIB_H
    #include <vector>
    #include "../../../Console/Core_OS/lib/Input.hpp"
    #include "../../../Console/Core_OS/lib/mapElement.hpp"
    #include "../../../Console/Drivers/GFX_D/IGfx.hpp"
    #include "../../../Console/Core_OS/lib/Error.hpp"
    #include "../lib/SDL_Button.hpp"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <map>

class SDL_TextureData {
    public:
        SDL_TextureData() {};
        ~SDL_TextureData() {
            clear();
        }
        SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string& filename) {
            auto it = textures.find(filename);
            if (it != textures.end())
                return it->second;
            else {
                //SDL_Texture *texture;
                SDL_Surface *surface = IMG_Load(filename.c_str());
                if (surface != nullptr) {
                    textures.insert({filename, SDL_CreateTextureFromSurface(renderer, surface)});
                    return textures[filename];
                } else {
                    throw Arcade::Error("Failed to load image");
                }
                SDL_FreeSurface(surface);
            }
        };
        void clear() {
            for (auto &i : textures) {
                SDL_DestroyTexture(i.second);
            }
            textures.clear();
        };

    private:
        std::map<std::string, SDL_Texture*> textures;
};

class SDL_lib : public Drivers::IGfx
{
    public:
        SDL_lib();
        ~SDL_lib();
        void getInput(Arcade::Core_Data &_data, SDL_Event &event);
        void renderElement(Arcade::mapElement element);
        void render(std::vector<std::vector<Arcade::mapElement>> _layout);
        void initButtons(const Arcade::Core_Data _data);
        void checkGamesButtons(Arcade::Core_Data &data);
        void checkGfxButtons(Arcade::Core_Data &data);
        void changeLib(Arcade::Core_Data &data);
        void update(std::vector<std::vector<Arcade::mapElement>> _scene, Arcade::Core_Data &_data);
        void exitLib();

    private:
        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;
        TTF_Font *_font;
        //SDL_Texture *_background;
        SDL_TextureData _textures;
        std::map<int, Arcade::SDL_Button> _gfxButtons;
        std::map<int, Arcade::SDL_Button> _gamesButtons;
};

extern "C" Drivers::IGfx *get_Class();
extern "C" std::string getType();

#endif /* !SDL_LIB_H */
