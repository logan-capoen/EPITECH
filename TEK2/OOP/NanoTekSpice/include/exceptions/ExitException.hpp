/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** ExitException.hpp
*/

#pragma once

#include <exception>

class ExitException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "exit";
        }
};
