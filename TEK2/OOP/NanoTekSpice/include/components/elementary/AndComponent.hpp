/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** AndComponent.hpp
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class AndComponent : public AComponent {
        public:
            AndComponent();
            nts::Tristate compute(std::size_t pin) override;
    };
}