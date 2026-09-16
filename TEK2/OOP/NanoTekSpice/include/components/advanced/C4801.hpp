/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4801.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4801 : public AComponent {
        private:
            Tristate _memory[1024][8];
            
            int getAddress();
        public:
            C4801();
            ~C4801() = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;
    };
}
