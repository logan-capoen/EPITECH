/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** NotComponent
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class NotComponent : public AComponent {
        public:
            NotComponent();
            nts::Tristate compute(std::size_t pin) override;
    };
}