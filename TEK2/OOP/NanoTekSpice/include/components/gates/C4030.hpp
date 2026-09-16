/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4030
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4030 : public AComponent {
        public:
            C4030();
            nts::Tristate compute(std::size_t pin) override;
    };
}