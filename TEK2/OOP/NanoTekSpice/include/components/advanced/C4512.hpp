/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4040
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4512 : public AComponent {
        public:
            C4512();
            Tristate compute(std::size_t pin) override;
    };
}