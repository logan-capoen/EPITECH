/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** AndComponent.cpp
*/

#include "components/elementary/AndComponent.hpp"

/**
 * @file AndComponent.cpp
 * @brief Implementation of a 2-input AND logic gate.
 *
 * The AndComponent simulates a basic digital AND gate.
 *
 * Inputs:
 * - A
 * - B
 *
 * Output:
 * - Q = A AND B
 *
 * The output is True only when both inputs are True.
 * If any input is Undefined, the tristate logic rules
 * determine the resulting value.
 *
 * @see nts::IComponent
 */

namespace nts {
    AndComponent::AndComponent()
    {
        _inputs[1] = false;
        _inputs[2] = false;
        _outputs[3] = {1, 2};
    }

    Tristate AndComponent::compute(std::size_t pin) {
        _inputs[pin] = true;
        return getLink(_outputs[pin].first) && getLink(_outputs[pin].second);
    }
}