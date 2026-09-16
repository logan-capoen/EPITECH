/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** UnknownComponentName.hpp
*/

#pragma once

#include "NanoTekException.hpp"

class UnknownComponentNameException : public NanoTekException {
    public:
        explicit UnknownComponentNameException(const std::string& name) : NanoTekException("Unknown component name: " + name) {}
};
