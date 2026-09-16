/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** ClockComponent
*/

#pragma once
#include "IComponent.hpp"
#include "AComponent.hpp"


namespace nts {
    class ClockComponent: public AComponent{
        private:
            Tristate _value;
            Tristate _nextValue;
            bool _isNext;
        public:
            ClockComponent();
            ~ClockComponent();
            void simulate(std::size_t tick) override;
            void setValue(Tristate value);
            Tristate compute(std::size_t pin) override;
            char displayValue();
    };
}
