/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4071
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4071 : public AComponent {
        public:
            C4071();
            nts::Tristate compute(std::size_t pin) override;
    };
}