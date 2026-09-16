/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4011
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4011 : public AComponent {
        public:
            C4011();
            nts::Tristate compute(std::size_t pin) override;
    };
}