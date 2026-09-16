/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** NotComponent.cpp
*/

#include "components/elementary/NotComponent.hpp"

/**
 * @file NotComponent.cpp
 * @brief Implementation of a NOT (inverter) logic gate.
 *
 * The NotComponent simulates a digital inverter.
 *
 * Input:
 * - A
 *
 * Output:
 * - Q = NOT A
 *
 * The output returns the logical inverse of the input.
 *
 * @see nts::IComponent
 */

namespace nts {
    NotComponent::NotComponent()
    {
        _inputs[1] = false;
        _outputs[2] = {1, 0};
    }

    Tristate NotComponent::compute(std::size_t pin) {
        _inputs[pin] = true;
        return !getLink(_outputs[pin].first);
    }
}