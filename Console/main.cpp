/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** main.cpp
*/

#include <iostream>

void arcade(char **av);

int main(int ac, char **av)
{
    if (false/*usage()*/) {
        return 0;
    }
    if (ac != 2/*invalid_arg(ac, av)*/) {
        return 84;
    } else {
        arcade(av);
        return 0;
    }
}
