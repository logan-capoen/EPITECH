/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** Link.hpp
*/

#pragma once

#include "IComponent.hpp"

namespace nts
{
    class Link {
        public:
            Link(IComponent& other, std::size_t otherPin);
            size_t getOtherPin();
            IComponent& getOther();
        private:
            IComponent& _other;
            std::size_t _otherPin;
    };
}
