/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** TrueComponent.cpp
*/

#include "components/special/TrueComponent.hpp"
#include <iostream>

/**
 * @file TrueComponent.cpp
 * @brief Implementation of a constant True (logical 1) component.
 *
 * The TrueComponent always outputs the logical True value.
 *
 * Inputs:
 * - None functional (placeholder for simulation linkage)
 *
 * Outputs:
 * - Constant True (Tristate)
 *
 * Behavior:
 * - compute() always returns True.
 *
 * @see nts::IComponent
 */

namespace nts {
    TrueComponent::TrueComponent()
    {
        _inputs[1] = false;
    }
    Tristate TrueComponent::compute([[maybe_unused]] std::size_t pin)
    {
        _inputs[pin] = true;
        return True;
    }
}