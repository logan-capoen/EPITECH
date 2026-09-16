/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4001
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4001 : public AComponent {
        public:
            C4001();
            nts::Tristate compute(std::size_t pin) override;
    };
}