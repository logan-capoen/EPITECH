/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** UnknownComponentException.hpp
*/

#pragma once

#include "NanoTekException.hpp"

class UnknownComponentTypeException : public NanoTekException {
    public:
        explicit UnknownComponentTypeException(const std::string& type) : NanoTekException("Unknown component type: " + type) {}
};
