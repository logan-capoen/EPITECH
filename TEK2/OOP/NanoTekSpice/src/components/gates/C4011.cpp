/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4011.cpp
*/

#include "components/gates/C4011.hpp"

/**
 * @file C4011.cpp
 * @brief Implementation of the 4011 quad 2-input NAND gate component.
 *
 * The C4011 component simulates a CMOS 4011 integrated circuit,
 * which contains four independent 2-input NAND gates.
 *
 * Each gate computes:
 *   Q = NOT (A AND B)
 *
 * Inputs:
 * - A, B : Gate inputs
 *
 * Outputs:
 * - Q : Result of the NAND operation
 *
 * The output is False only when both inputs are True.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4011::C4011()
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

    Tristate C4011::compute(std::size_t pin) {
        _inputs[pin] = true;
        return !(getLink(_outputs[pin].first) && getLink(_outputs[pin].second));
    }
}