/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** ArcadeException
*/

#pragma once

#include <stdexcept>
#include <string>

class ArcadeException : public std::exception {
    public:
        explicit ArcadeException(const std::string &message): _message(message) {}
        const char* what() const noexcept override {
            return _message.c_str();
        }
    private:
        std::string _message;
};
