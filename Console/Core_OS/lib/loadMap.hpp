/*
** EPITECH PROJECT, 2024
** loadMap
** File description:
** loadMap
*/

#include <iostream>
#include <fstream>
#include <vector>

namespace Arcade
{
    static std::vector<std::string> loadMap(const std::string filename)
    {
        std::vector<std::string> map;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                map.push_back(line);
            }
            file.close();
        } else {
        std::cout << "Failed to open file: " << filename << std::endl;
        }
        return map;
    }
}
