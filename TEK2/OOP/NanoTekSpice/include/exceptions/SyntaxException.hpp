/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** SyntaxError.hpp
*/

#pragma once

#include "NanoTekException.hpp"

class SyntaxException : public NanoTekException {
    public:
        SyntaxException(const std::string& message) : NanoTekException("Syntax or lexical error in circuit file: " + message) {}
};
