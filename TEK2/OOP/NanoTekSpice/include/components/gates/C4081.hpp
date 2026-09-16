/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4081
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4081 : public AComponent {
        public:
            C4081();
            nts::Tristate compute(std::size_t pin) override;
    };
}