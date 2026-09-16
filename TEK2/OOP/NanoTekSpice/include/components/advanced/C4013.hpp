/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4013
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4013 : public AComponent {
        private:
            Tristate _value1;
            Tristate _value2;
            Tristate _prevC1;
            Tristate _prevC2;
        public:
            C4013();
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;
    };
}