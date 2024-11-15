/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DlLoader.cpp
*/

#include "../lib/DlLoader.hpp"
#include <iostream>

template <typename T>
Arcade::DlLoader<T>::DlLoader()
{
    std::cout << "Booting Dynamic Library Loader..." << std::endl;
    _dl_handle = NULL;
}

template <typename T>
Arcade::DlLoader<T>::~DlLoader()
{
    std::cout << "Shutting Down Dynamic Library Loader..." << std::endl;
    remove();
    std::cout << "DL Removed" << std::endl;
}

template <typename T>
void Arcade::DlLoader<T>::load(std::string lib_filepath)
{
    _dl_handle = dlopen(lib_filepath.c_str(), RTLD_LAZY);
    if (_dl_handle == NULL) {
        throw (Arcade::Error(dlerror()));
    }
}

template <typename T>
std::unique_ptr<T> Arcade::DlLoader<T>::getInstance(std::string sym_name)
{
    T *(*_getClass)() = nullptr;

    if (_dl_handle == nullptr) {
        return nullptr;
    }
    _getClass = (T * (*) ())dlsym(_dl_handle, sym_name.c_str());
    if (_getClass == nullptr) {
        throw Arcade::Error(dlerror());
    }
    return std::unique_ptr<T>(_getClass());
}

template <typename T>
std::string Arcade::DlLoader<T>::getType()
{
    if (_dl_handle == nullptr) {
        return "";
    }
    std::string (*getTypeFunc)() = (std::string(*)())dlsym(_dl_handle, "getType");
    if (getTypeFunc == nullptr) {
        throw Arcade::Error(dlerror());
    }
    std::string instanceType = getTypeFunc();
    return instanceType;
}

template <typename T>
void Arcade::DlLoader<T>::remove()
{
    if (_dl_handle != nullptr)
        dlclose(_dl_handle);
}
