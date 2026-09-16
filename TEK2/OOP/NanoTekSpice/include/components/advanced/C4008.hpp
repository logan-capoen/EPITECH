/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4008
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4008 : public AComponent {
        private:
            int _result;
        public:
            C4008();
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;
    };
}