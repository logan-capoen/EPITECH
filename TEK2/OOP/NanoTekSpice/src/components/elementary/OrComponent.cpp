/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** OrComponent.cpp
*/

#include "components/elementary/OrComponent.hpp"

/**
 * @file OrComponent.cpp
 * @brief Implementation of a 2-input OR logic gate.
 *
 * The OrComponent simulates a basic digital OR gate.
 *
 * Inputs:
 * - A
 * - B
 *
 * Output:
 * - Q = A OR B
 *
 * The output is True if at least one input is True.
 * Tristate logic rules apply when inputs are Undefined.
 *
 * @see nts::IComponent
 */

namespace nts {
    OrComponent::OrComponent()
    {
        _inputs[1] = false;
        _inputs[2] = false;
        _outputs[3] = {1, 2};
    }

    Tristate OrComponent::compute(std::size_t pin) {
        _inputs[pin] = true;
        return getLink(_outputs[pin].first) || getLink(_outputs[pin].second);
    }
}