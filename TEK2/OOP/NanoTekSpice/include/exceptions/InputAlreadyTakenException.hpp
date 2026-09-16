/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** InputAlreadyTakenException
*/

#pragma once

#include "NanoTekException.hpp"

class InputAlreadyTakenException : public NanoTekException {
    public:
        InputAlreadyTakenException(const std::string& filename) : NanoTekException("Input already taken: " + filename) {}
};
