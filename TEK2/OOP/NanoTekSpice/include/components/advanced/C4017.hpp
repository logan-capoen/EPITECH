/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4017
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4017 : public AComponent {
        private:
            int _count;
            Tristate _prevCP0;
            Tristate _prevCP1;
        public:
            C4017();
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;
    };
}