/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4514.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4514 : public AComponent {
        private:
            Tristate _latchedA;
            Tristate _latchedB;
            Tristate _latchedC;
            Tristate _latchedD;
        public:
            C4514();
            ~C4514() = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;
    };
}
