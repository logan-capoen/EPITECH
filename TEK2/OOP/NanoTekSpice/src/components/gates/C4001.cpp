/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4001.cpp
*/

#include "components/gates/C4001.hpp"

/**
 * @file C4001.cpp
 * @brief Implementation of the 4001 quad 2-input NOR gate component.
 *
 * The C4001 component simulates a CMOS 4001 integrated circuit,
 * which contains four independent 2-input NOR gates.
 *
 * Each gate computes:
 *   Q = NOT (A OR B)
 *
 * Inputs:
 * - A, B : Gate inputs
 *
 * Outputs:
 * - Q : Result of the NOR operation
 *
 * Each gate operates independently and the output is computed
 * from its associated pair of inputs.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4001::C4001()
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

    Tristate C4001::compute(std::size_t pin) {
        if (_inputs[pin])
            return _results[pin];
        _inputs[pin] = true;
        _results[pin] = !(getLink(_outputs[pin].first) || getLink(_outputs[pin].second));
        return _results[pin];
    }
}