/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** FalseComponent.cpp
*/

#include "components/special/FalseComponent.hpp"
#include <iostream>

/**
 * @file FalseComponent.cpp
 * @brief Implementation of a constant False (logical 0) component.
 *
 * The FalseComponent always outputs the logical False value.
 *
 * Inputs:
 * - None functional (placeholder for simulation linkage)
 *
 * Outputs:
 * - Constant False (Tristate)
 *
 * Behavior:
 * - compute() always returns False.
 *
 * @see nts::IComponent
 */

namespace nts {
    FalseComponent::FalseComponent()
    {
        _inputs[1] = false;
    }
    
    Tristate FalseComponent::compute([[maybe_unused]] std::size_t pin)
    {
        _inputs[pin] = true;
        return False;
    }
}