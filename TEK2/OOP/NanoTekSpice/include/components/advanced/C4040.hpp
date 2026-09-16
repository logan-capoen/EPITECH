/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** C4040
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class C4040 : public AComponent {
        private:
            int _count;
            bool _prevClock;
        public:
            C4040();
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;
    };
}