/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** InvalidPinException
*/

#pragma once

#include "NanoTekException.hpp"

class InvalidPinException : public NanoTekException {
    public:
        InvalidPinException(const std::string& filename) : NanoTekException("Invalid pin: " + filename) {}
};
