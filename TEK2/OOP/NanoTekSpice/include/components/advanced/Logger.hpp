/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** Logger.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class Logger : public AComponent {
        private:
            Tristate _previousClock;
            bool buildByte(unsigned char &out);
        public:
            Logger();
            ~Logger() = default;
            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;
    };
}