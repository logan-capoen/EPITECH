/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4071.cpp
*/

#include "components/gates/C4071.hpp"

/**
 * @file C4071.cpp
 * @brief Implementation of the 4071 quad 2-input OR gate component.
 *
 * The C4071 component simulates a CMOS 4071 integrated circuit,
 * which contains four independent 2-input OR gates.
 *
 * Each gate computes:
 *   Q = A OR B
 *
 * Inputs:
 * - A, B : Gate inputs
 *
 * Outputs:
 * - Q : Result of the OR operation
 *
 * The output is True if at least one input is True.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4071::C4071()
    {
        _inputs[1] = false;
        _inputs[2] = false;
        _outputs[3] = {1, 2};
        _inputs[5] = false;
        _inputs[6] = false;
        _outputs[4] = {5, 6};
        _inputs[8] = false;
        _inputs[9] = false;
        _outputs[10] = {8, 9};
        _inputs[12] = false;
        _inputs[13] = false;
        _outputs[11] = {12, 13};
    }

    Tristate C4071::compute(std::size_t pin) {
        _inputs[pin] = true;
        return getLink(_outputs[pin].first) || getLink(_outputs[pin].second);
    }
}