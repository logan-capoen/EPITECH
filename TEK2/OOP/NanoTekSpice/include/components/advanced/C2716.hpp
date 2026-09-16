/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C2716.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C2716 : public AComponent {
        private:
            Tristate _memory[2048][8];
            int getAddress();
        public:
            C2716();
            ~C2716() = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;
    };
}
