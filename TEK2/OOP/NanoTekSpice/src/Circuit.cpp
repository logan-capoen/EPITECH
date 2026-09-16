/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** Circuit
*/

#include "Circuit.hpp"
#include "ComponentFactory.hpp"
#include "exceptions/UnknownComponentNameException.hpp"
#include <iostream>
#include "components/special/InputComponent.hpp"
#include "components/special/ClockComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "exceptions/WrongChipsetException.hpp"

/**
 * @file Circuit.cpp
 * @brief Represents the entire NTS circuit simulation.
 *
 * Circuit manages components, links, and simulation ticks.
 *
 * Functions:
 * - addComponent(type, name) : Add a component by type.
 * - getComponent(name) : Retrieve a component by name.
 * - linkComponents(comp1, pin1, comp2, pin2) : Connect components.
 * - simulate() : Run one simulation tick for all components.
 * - display() : Print circuit state to console.
 * - setValue(name, value) : Set a value for an InputComponent or ClockComponent.
 */
 
namespace nts {
    void Circuit::addComponent(const std::string& type, const std::string& name)
    {
        _components[name] = _factory.createComponent(type);
    }

    nts::IComponent& Circuit::getComponent(const std::string& name)
    {
        auto it = _components.find(name);

        if (it == _components.end())
            throw UnknownComponentNameException(name);
        return *(it->second);
    }

    void Circuit::linkComponents(const std::string& comp1, std::size_t pin1, const std::string& comp2, std::size_t pin2)
    {
        IComponent& first = getComponent(comp1);
        IComponent& second = getComponent(comp2);

        first.setLink(pin1, second, pin2);
        second.setLink(pin2, first, pin1);
    }

    void Circuit::simulate()
    {
        for (auto& [name, comp] : _components) {
            comp->simulate(_tick);
            if (auto* ac = dynamic_cast<nts::AComponent*>(comp.get()))
                ac->resetInputs();
        }
        _tick++;
    }

    void Circuit::display() const
    {
        bool is_outputs = false;
        std::cout << "tick: " << _tick << std::endl;
        std::cout << "input(s):" << std::endl;
        for (auto it = _components.begin(); it != _components.end(); it++) {
            auto input = dynamic_cast<InputComponent *>(it->second.get());
            auto clock = dynamic_cast<ClockComponent *>(it->second.get());
            auto output = dynamic_cast<OutputComponent *>(it->second.get());
            if (input)
                std::cout << "  " << it->first << ": " << input->displayValue() << std::endl;
            else if (clock)
                std::cout << "  " << it->first << ": " << clock->displayValue() << std::endl;
            else if (output && is_outputs == false) {
                std::cout << "output(s):\n" << "  " << it->first << ": " << output->displayValue() << std::endl;
                is_outputs = true;
            }
            else if (output && is_outputs == true)
                std::cout << "  " << it->first << ": " << output->displayValue() << std::endl;
        }
    }

    void Circuit::setValue(const std::string& name, nts::Tristate value)
    {
        IComponent& component = getComponent(name);
        auto input = dynamic_cast<InputComponent *>(&component);
        auto clock = dynamic_cast<ClockComponent *>(&component);

        if (input)
            input->setValue(value);
        else if (clock)
            clock->setValue(value);
        else
            throw WrongChipsetException(name);
    }
}