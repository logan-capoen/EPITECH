/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** OrComponent
*/


#pragma once
#include "AComponent.hpp"

namespace nts {
    class OrComponent : public AComponent {
        public:
            OrComponent();
            nts::Tristate compute(std::size_t pin) override;
    };
}

