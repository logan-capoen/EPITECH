/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** XorComponent.cpp
*/

#include "components/elementary/XorComponent.hpp"

/**
 * @file XorComponent.cpp
 * @brief Implementation of a 2-input XOR logic gate.
 *
 * The XorComponent simulates a digital exclusive OR gate.
 *
 * Inputs:
 * - A
 * - B
 *
 * Output:
 * - Q = A XOR B
 *
 * The output is True if the inputs differ and False
 * if they are identical.
 *
 * @see nts::IComponent
 */

namespace nts {
    XorComponent::XorComponent()
    {
        _inputs[1] = false;
        _inputs[2] = false;
        _outputs[3] = {1, 2};
    }

    Tristate XorComponent::compute(std::size_t pin) {
        _inputs[pin] = true;
        return getLink(_outputs[pin].first) ^ getLink(_outputs[pin].second);
    }
}