/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** XorComponent
*/


#pragma once
#include "AComponent.hpp"

namespace nts {
    class XorComponent : public AComponent {
        public:
            XorComponent();
            nts::Tristate compute(std::size_t pin) override;
    };
}