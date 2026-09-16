/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4069.cpp
*/

#include "components/gates/C4069.hpp"

/**
 * @file C4069.cpp
 * @brief Implementation of the 4069 hex inverter component.
 *
 * The C4069 component simulates a CMOS 4069 integrated circuit,
 * which contains six independent NOT gates (inverters).
 *
 * Each gate computes:
 *   Q = NOT A
 *
 * Inputs:
 * - A : Input signal
 *
 * Outputs:
 * - Q : Inverted signal
 *
 * Each inverter operates independently from the others.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4069::C4069()
    {
        _inputs[1] = false;
        _outputs[2] = {1, 0};
        _inputs[3] = false;
        _outputs[4] = {3, 0};
        _inputs[5] = false;
        _outputs[6] = {5, 0};
        _inputs[9] = false;
        _outputs[8] = {9, 0};
        _inputs[11] = false;
        _outputs[10] = {11, 0};
        _inputs[13] = false;
        _outputs[12] = {13, 0};
    }

    Tristate C4069::compute(std::size_t pin) {
        _inputs[pin] = true;
        return !getLink(_outputs[pin].first);
    }
}