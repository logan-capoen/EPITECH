/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** Circuit.hpp
*/

#pragma once

#include <memory>
#include <map>
#include <string>
#include "IComponent.hpp"
#include <stdexcept>
#include "ComponentFactory.hpp"

namespace nts
{
    class Circuit {
        private:
            std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
            ComponentFactory _factory;
            std::size_t _tick = 0;
        public:
            Circuit() = default;
            ~Circuit() = default;
            
            void addComponent(const std::string& type, const std::string& name);
            void linkComponents(const std::string& comp1, std::size_t pin1, const std::string& comp2, std::size_t pin2);
            void simulate();
            void display() const;
            void setValue(const std::string& name, nts::Tristate value);
            nts::IComponent& getComponent(const std::string& name);
    };
}
