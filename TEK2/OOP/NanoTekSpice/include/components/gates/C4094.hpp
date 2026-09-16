/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4094.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4094 : public AComponent {
        private:
            Tristate _shiftRegister[8];
            Tristate _latch[8];
            Tristate _previousClock = False;
            Tristate _previousStrobe = False;
            Tristate _qs = Undefined;
            Tristate _qsPrime = Undefined;
        public:
            C4094();
            ~C4094() = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;
    };
}

