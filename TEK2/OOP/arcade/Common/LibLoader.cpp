/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** LibLoader
*/

#include "LibLoader.hpp"

#include "LibLoader.hpp"
#include <iostream>
#include <dlfcn.h>

LibLoader::LibLoader(): _handle(nullptr)
{
}

LibLoader::~LibLoader()
{
    closeLib();
}

bool LibLoader::loadLib(const std::string &path)
{
    _handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!_handle) {
        std::cerr << "dlopen error: " << dlerror() << std::endl;
        return false;
    }
    return true;
}

void LibLoader::closeLib()
{
    if (_handle) {
        dlclose(_handle);
        _handle = nullptr;
    }
}

void *LibLoader::searchFunction(const std::string &name)
{
    if (!_handle)
        return nullptr;
    dlerror();
    void *func = dlsym(_handle, name.c_str());
    const char *err = dlerror();
    if (err) {
        std::cerr << "dlsym error (" << name << "): " << err << std::endl;
        return nullptr;
    }
    return func;
}
