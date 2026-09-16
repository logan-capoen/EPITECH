/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** OutputComponent.hpp
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class OutputComponent : public AComponent {
        public:
            OutputComponent();
            nts::Tristate compute(std::size_t pin) override;
            char displayValue();
    };
}