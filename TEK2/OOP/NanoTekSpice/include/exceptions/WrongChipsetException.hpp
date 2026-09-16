/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** WrongChipsetException
*/

#pragma once

#include "NanoTekException.hpp"

class WrongChipsetException: public NanoTekException {
    public:
        explicit WrongChipsetException(const std::string& type) : NanoTekException("Wrong chipset to set value: " + type) {}
};

