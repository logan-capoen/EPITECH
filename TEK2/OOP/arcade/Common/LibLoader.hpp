/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** LibLoader
*/

#ifndef LIBLOADER_HPP_
#define LIBLOADER_HPP_

#include <string>
#include <vector>
#include <unordered_map>

class LibLoader {
    public:
        LibLoader();
        ~LibLoader();

        LibLoader(const LibLoader &) = delete;
        LibLoader &operator=(const LibLoader &) = delete;

        bool loadLib(const std::string &path);
        void closeLib();
        void *searchFunction(const std::string &name);
        
        template <typename T>
        T getFunction(const std::string &name) {
            return reinterpret_cast<T>(searchFunction(name));
        }
    private:
        void *_handle;
};

#endif /* !LIBLOADER_HPP_ */
