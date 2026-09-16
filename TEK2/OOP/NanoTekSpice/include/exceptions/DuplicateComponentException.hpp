/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** DuplicateComponentException.hpp
*/

#pragma once

#include "NanoTekException.hpp"

class DuplicateComponentNameException : public NanoTekException {
    public:
        explicit DuplicateComponentNameException(const std::string& name) : NanoTekException("Duplicate component name: " + name) {}
};
