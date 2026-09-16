/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** NanoTekException.hpp
*/

#pragma once

#include <exception>
#include <string>

class NanoTekException : public std::exception {
    protected:
        std::string _message;
    public:
        explicit NanoTekException(const std::string& message) : _message(message) {}

        const char* what() const noexcept override {
            return _message.c_str();
        }
};
