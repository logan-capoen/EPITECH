/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** InputComponent
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class InputComponent: public AComponent {
        private:
            Tristate _value;
            Tristate _nextValue;
        public:
            InputComponent();
            ~InputComponent();
            void simulate(std::size_t tick) override;
            void setValue(Tristate value);
            char displayValue();
            Tristate compute(std::size_t pin) override;
    };
}
