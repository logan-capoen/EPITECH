/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** NoChipsetsException.hpp
*/

#pragma once

#include "NanoTekException.hpp"

class NoChipsetsException : public NanoTekException {
    public:
        NoChipsetsException() : NanoTekException("No chipsets found in circuit.") {}
};
