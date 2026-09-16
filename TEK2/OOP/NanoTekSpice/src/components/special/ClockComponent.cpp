/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** ClockComponent
*/

#include "components/special/ClockComponent.hpp"

/**
 * @file ClockComponent.cpp
 * @brief Implementation of a clock generator component.
 *
 * The ClockComponent simulates a digital clock signal in the
 * NTS simulation. It toggles its output every simulation tick
 * unless a new value is explicitly set.
 *
 * Inputs:
 * - Control input (optional) to set the next value
 *
 * Outputs:
 * - Clock output (Tristate) toggling between True and False
 *
 * Behavior:
 * - If setValue() is called, the next simulation tick outputs
 *   the specified value.
 * - Otherwise, the component toggles its output automatically.
 * - displayValue() returns '1', '0', or 'U' depending on the
 *   current Tristate value.
 *
 * @see nts::IComponent
 */

namespace nts {
    ClockComponent::ClockComponent(): _value(Undefined), _nextValue(Undefined), _isNext(false)
    {
        _inputs[1] = false;
    }

    ClockComponent::~ClockComponent(){}

    void ClockComponent::setValue(Tristate value)
    {
        _isNext = true;
        _value = value;
    }

    void ClockComponent::simulate([[maybe_unused]] std::size_t tick)
    {
        if (_isNext == true) {
            _nextValue = _value;
            _isNext = False;
        } else 
            _nextValue = !_nextValue;
    }

    char ClockComponent::displayValue()
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

    Tristate ClockComponent::compute([[maybe_unused]] std::size_t pin)
    {
        _inputs[pin] = true;
        return _nextValue;
    }
}