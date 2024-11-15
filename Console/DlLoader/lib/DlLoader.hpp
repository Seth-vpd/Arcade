/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DlLoader.hpp
*/

#ifndef DL_LOADER_H
    #define DL_LOADER_H
    #include <iostream>
    #include <filesystem>
    #include <dlfcn.h>
    #include "../../Drivers/Drivers.hpp"
    #include "../../Core_OS/lib/Error.hpp"
    #include <memory>

namespace Arcade {
    template <typename T>
    class DlLoader {
        public:
            DlLoader();
            ~DlLoader();
            void load(std::string lib_filepath);
            std::unique_ptr<T> getInstance(std::string sym_name);
            std::string getType();
            void remove();
    
        protected:
        private:
            void *_dl_handle;
    };

    template class Arcade::DlLoader<Drivers::IGame>;
    template class Arcade::DlLoader<Drivers::IGfx>;
}

#define DL_DIR_PATH "./lib/"

#endif /* !DL_LOADER_H */
