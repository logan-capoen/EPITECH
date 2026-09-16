/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** Input
*/

#include "components/special/InputComponent.hpp"
#include <iostream>

/**
 * @file InputComponent.cpp
 * @brief Implementation of a user-controlled input component.
 *
 * The InputComponent allows the user or simulation to set a
 * specific logic level for a circuit input.
 *
 * Inputs:
 * - Control input to set the value (Tristate)
 *
 * Outputs:
 * - Provides the set value as output
 *
 * Behavior:
 * - setValue() stores the desired input value.
 * - simulate() updates the next output to match the stored value.
 * - displayValue() returns '1', '0', or 'U' depending on current value.
 *
 * @see nts::IComponent
 */

namespace nts {
    InputComponent::InputComponent(): _value(Undefined), _nextValue(Undefined)
    {
        _inputs[1] = false;
    }

    InputComponent::~InputComponent() {}

    void InputComponent::setValue(Tristate value)
    {
        _value = value;
    }

    void InputComponent::simulate([[maybe_unused]] std::size_t tick)
    {
        _nextValue = _value;
    }

    char InputComponent::displayValue()
    {
        switch (_nextValue)
        {
        case True:
            return '1';
        case False:
            return '0';
        default:
            return 'U';
        }
    }

    Tristate InputComponent::compute([[maybe_unused]] std::size_t pin)
    {
        _inputs[pin] = true;
        return _nextValue;
    }
}
