/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** FalseComponent.hpp
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class FalseComponent : public AComponent {
        public:
            FalseComponent();
            Tristate compute(std::size_t pin) override;
    };
}