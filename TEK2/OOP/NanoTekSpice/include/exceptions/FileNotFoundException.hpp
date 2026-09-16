/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** NoChipsetsException.hpp
*/

#pragma once

#include "NanoTekException.hpp"

class FileNotFoundException : public NanoTekException {
    public:
        FileNotFoundException(const std::string& filename) : NanoTekException("File not found: " + filename) {}
};
