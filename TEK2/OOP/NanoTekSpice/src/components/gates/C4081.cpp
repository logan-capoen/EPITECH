/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4081.cpp
*/

#include "components/gates/C4081.hpp"

/**
 * @file C4081.cpp
 * @brief Implementation of the 4081 quad 2-input AND gate component.
 *
 * The C4081 component simulates a CMOS 4081 integrated circuit,
 * which contains four independent 2-input AND gates.
 *
 * Each gate computes:
 *   Q = A AND B
 *
 * Inputs:
 * - A, B : Gate inputs
 *
 * Outputs:
 * - Q : Result of the AND operation
 *
 * The output is True only when both inputs are True.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4081::C4081()
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

    Tristate C4081::compute(std::size_t pin) {
        _inputs[pin] = true;
        return getLink(_outputs[pin].first) && getLink(_outputs[pin].second);
    }
}