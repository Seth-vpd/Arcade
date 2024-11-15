/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ncurses_lib.cpp
*/

#include "../lib/ncurses_lib.hpp"
#include "../../../Games/Snake/lib/Snake.hpp"

ncurses_lib::ncurses_lib()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    std::cout << "Loading ncurses_lib" << std::endl;
}

ncurses_lib::~ncurses_lib()
{
    endwin();
}

void ncurses_lib::renderElement(Arcade::mapElement Element, std::vector<std::vector<Arcade::mapElement>> _scene)
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    int centerX = (xMax / 2) - (_scene[0].size() / 2);
    int centerY = (yMax / 2) - (_scene.size() / 2);

    int posX = Element.posX + centerX;
    int posY = Element.posY + centerY;
    mvprintw(posY, posX, "%c", Element.element);
    move(0, 0);
}

void ncurses_lib::render(std::vector<std::vector<Arcade::mapElement>> _scene)
{
    for (int i = 0; i < _scene.size(); i++) {
        for (int j = 0; j < _scene[i].size(); j++) {
            renderElement(_scene[i][j], _scene);
        }
    }
}

void changeLib(Arcade::Core_Data &data)
{
    data._currentGfxIndex += 1;
    if (data._currentGfxIndex >= data._gfxLibrariesPath.size() - 1)
            data._currentGfxIndex = 0;
    data._prevFocus = data._focus;
    data._focus = Arcade::loadingLib;
}

void ncurses_lib::getInput(Arcade::Core_Data &_data)
{
    int ch = getch();
    switch (ch) {
        case KEY_UP:
            _data._input = Arcade::UP;
            break;
        case KEY_DOWN:
            _data._input = Arcade::DOWN;
            break;
        case KEY_LEFT:
            _data._input = Arcade::LEFT;
            break;
        case KEY_RIGHT:
            _data._input = Arcade::RIGHT;
            break;
        case 27:
            _data._focus = Arcade::inCore;
            _data._input = Arcade::ESCAPE;
            break;
        case 's':
            changeLib(_data);
            break;
        case 'l':
            _data._focus = Arcade::quit;
            break;
    }
}


void ncurses_lib::ncurses_menu(Arcade::Core_Data &_data)
{
    std::vector<std::string> ascii_art = read_Ascii_art("Resources/Graphics/doh.txt");
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *bigBox = newwin(yMax - 2, xMax - 2, 1, 1);
    box(bigBox, ACS_VLINE, ACS_HLINE);
    refresh();
    wrefresh(bigBox);

    
    int libMenu_Height = 4;
    int libMenu_Width = 38;
    int libMenu_Y = 5;
    int libMenu_X = 12;
    WINDOW *libMenu_Win = subwin(bigBox, libMenu_Height, libMenu_Width, libMenu_Y, libMenu_X);
    box(libMenu_Win, 6, ACS_HLINE);

    int gameWin_Height = 4;
    int gameWin_Width = 38;
    int gameWin_Y = 5;
    int gameWin_X = xMax - gameWin_Width - 12;
    WINDOW *gameWin = subwin(bigBox, gameWin_Height, gameWin_Width, gameWin_Y, gameWin_X);
    box(gameWin, 6, ACS_HLINE);

    int ascii_art_Height = ascii_art.size() + 2;
    int ascii_art_Width = ascii_art[0].size() + 4;
    int ascii_art_Y = (yMax - ascii_art_Height) / 2;
    int ascii_art_X = (xMax - ascii_art_Width) / 2;
    WINDOW *ascii_art_menu = subwin(bigBox, ascii_art_Height, ascii_art_Width, ascii_art_Y, ascii_art_X);

    std::vector<std::string> lib_choices;
    std::vector<std::string> game_choices;
    int choice1;
    int choice2;
    int lib_highlight = 0;
    int game_highlight = 0;
    bool currentWindow = true;
    for (int i = 0; i < _data._gfxLibrariesPath.size(); i++) {
        lib_choices.push_back(_data._gfxLibrariesPath[i]);
    }

    for (int i = 0; i < _data._gamesLibraryPath.size(); i++) {
        game_choices.push_back(_data._gamesLibraryPath[i]);
    }

    wrefresh(libMenu_Win);
    wrefresh(gameWin);

    int centerX = (xMax / 2) - (ascii_art_Width / 2);
    int centerY = (yMax / 2) - (ascii_art_Height / 2);

    while(1) {
        
        keypad(libMenu_Win, true);
        choice1 = 0;
        choice2 = 0;
        for (int i = 0; i < lib_choices.size(); i++) {
            if (i == lib_highlight && currentWindow)
                wattron(libMenu_Win, A_REVERSE);
            int start_x = (libMenu_Width - lib_choices[i].length()) / 2;
            mvwprintw(libMenu_Win, i+1, start_x, "%s", lib_choices[i].c_str());
            wattroff(libMenu_Win, A_REVERSE);
        }
        keypad(gameWin, true);
        for (int i = 0; i < game_choices.size(); i++) {
            if (i == game_highlight && !currentWindow)
                    wattron(gameWin, A_REVERSE);
                int start_x = (gameWin_Width - game_choices[i].length()) / 2;
                mvwprintw(gameWin, i+1, start_x, "%s", game_choices[i].c_str());
                wattroff(gameWin, A_REVERSE);
        }
        for (int i = 0; i < ascii_art.size(); i++) {
            mvwprintw(ascii_art_menu, i+centerY, centerX, "%s", ascii_art[i].c_str());
        }
        wrefresh(ascii_art_menu);
        wrefresh(libMenu_Win);
        wrefresh(gameWin);
        if (currentWindow)
            choice1 = wgetch(libMenu_Win);
        if (!currentWindow)
            choice2 = wgetch(gameWin);
        switch(choice1) {
            case KEY_UP:
            if (currentWindow == true) {
                lib_highlight--;
                if (lib_highlight < 0)
                    lib_highlight = lib_choices.size() - 1;
            }
                break;
            case KEY_DOWN:
            if (currentWindow == true) {
                lib_highlight++;
                if (lib_highlight >= lib_choices.size())
                    lib_highlight = 0;
            }
                break;
            case '\t':
            currentWindow = false;
            break;
            default:
                break;
        }

        switch (choice2) {
            case KEY_UP:
                if (currentWindow == false) {
                    game_highlight--;
                    if (game_highlight < 0)
                        game_highlight = game_choices.size() - 1;
                }
                break;
            case KEY_DOWN:
                if (currentWindow == false) {
                    game_highlight++;
                    if (game_highlight >= game_choices.size())
                        game_highlight = 0;
                }
                break;
            case '\t':
                currentWindow = true;
                break;
            default:
                break;
        }

        if (choice1 == 10 && currentWindow == true) {
            _data._focus = Arcade::loadingLib;
            _data._currentGfxIndex = lib_highlight;
            break;
        } else if (choice2 == 10 && currentWindow == false) {
            _data._focus = Arcade::loadingGame;
            _data._currentGameIndex = game_highlight;
            break;
        }
    }

    if (_data._focus == Arcade::quit)
        return;
    
}

std::vector<std::string> ncurses_lib::read_Ascii_art(const std::string filename)
{
    std::vector<std::string> ascii_art;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            ascii_art.push_back(line);
        }
        file.close();
    } else {
        std::cout << "Failed to open file: " << filename << std::endl;
    }

    return ascii_art;
}

void ncurses_lib::update(std::vector<std::vector<Arcade::mapElement>> _scene, Arcade::Core_Data &_data)
{
    getInput(_data);
    clear();
    if (_data._focus == Arcade::quit)
        return;
    if (_data._focus != Arcade::inGame) {
        ncurses_menu(_data);
    } else {
        render(_scene);
    }
    refresh();
}

void ncurses_lib::exitLib()
{
    endwin();
}

extern "C" Drivers::IGfx *getGraphics() {
    return new ncurses_lib();
}

extern "C" std::string getType()
{
    return "graphical";
}