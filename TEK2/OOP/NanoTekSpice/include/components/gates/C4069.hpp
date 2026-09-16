/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4069
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4069 : public AComponent {
        public:
            C4069();
            nts::Tristate compute(std::size_t pin) override;
    };
}