/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** OutputComponent.cpp
*/

#include "components/special/OutputComponent.hpp"

/**
 * @file OutputComponent.cpp
 * @brief Implementation of a simulation output component.
 *
 * The OutputComponent captures and stores the value of a
 * connected input, allowing inspection of simulation results.
 *
 * Inputs:
 * - Connected signal to be observed
 *
 * Outputs:
 * - None directly; use compute() and displayValue() to read state
 *
 * Behavior:
 * - compute() reads the linked input and caches it.
 * - displayValue() returns '1', '0', or 'U' depending on current value.
 *
 * @see nts::IComponent
 */

namespace nts {
    OutputComponent::OutputComponent()
    {
        _outputs[1] = {0, 0};
    }
    Tristate OutputComponent::compute([[maybe_unused]] std::size_t pin)
    {
        if (_inputs[pin])
            return _results[pin];
        _inputs[pin] = true;
        _results[pin] = getLink(1);
        return _results[pin];
    }

    char OutputComponent::displayValue()
    {
        switch (compute(1))
        {
        case True:
            return '1';
        case False:
            return '0';
        default:
            return 'U';
        }
    }
}