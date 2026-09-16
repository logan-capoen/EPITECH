/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** ILib
*/

#ifndef ILIB_HPP_
#define ILIB_HPP_
#include "Common.hpp"
#include <string>

class ILib {
    public:
        virtual ~ILib() = default;
        virtual const std::string get_name() const = 0;
        virtual LibType get_type() const = 0;
};

#endif