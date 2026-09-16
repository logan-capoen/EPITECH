/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4017.cpp
*/

#include "components/advanced/C4017.hpp"
#include <iostream>

/**
 * @file C4017.cpp
 * @brief Implementation of the 4017 decade Johnson counter component.
 *
 * The C4017 component simulates a CMOS 4017 integrated circuit,
 * which is a decade counter with 10 decoded outputs.
 *
 * The counter advances its active output on clock pulses and
 * cycles through 10 states (0–9). Only one output is active at
 * any given time.
 *
 * Inputs:
 * - CP0 : Clock input
 * - CP1 : Clock inhibit
 * - MR  : Master reset
 *
 * Outputs:
 * - Q0–Q9 : Decoded counter outputs
 * - Carry output
 *
 * The counter increments on clock transitions depending on the
 * state of the clock inhibit input. When the reset input is
 * activated, the counter immediately returns to state 0.
 *
 * The internal counter value determines which output pin returns
 * True during compute().
 *
 * @see nts::IComponent
 */

namespace nts {
    C4017::C4017(): _count(0), _prevCP0(Undefined), _prevCP1(Undefined)
    {
        _inputs[13] = false;
        _inputs[14] = false;
        _inputs[15] = false;
        _outputs[3] = {0, 0};
        _outputs[2] = {1, 0};
        _outputs[4] = {2, 0};
        _outputs[7] = {3, 0};
        _outputs[10] = {4, 0};
        _outputs[1] = {5, 0};
        _outputs[5] = {6, 0};
        _outputs[6] = {7, 0};
        _outputs[9] = {8, 0};
        _outputs[11] = {9, 0};
        _outputs[12] = {0, 0};
    }

    void C4017::simulate([[maybe_unused]] std::size_t tick) {
        Tristate CP0 = getLink(14);
        Tristate CP1 = getLink(13);
        Tristate MR  = getLink(15);

        if (MR == True) {
            _count = 0;
            _prevCP0 = CP0;
            _prevCP1 = CP1;
            return;
        }
        if (!CP1 && !_prevCP0 && CP0)
            _count = (_count + 1) % 10;
        else if (CP0 && _prevCP1 && !CP1)
            _count = (_count + 1) % 10;;
        _prevCP0 = CP0;
        _prevCP1 = CP1;
    }

    Tristate C4017::compute(std::size_t pin) {
        _inputs[pin] = true;
        if (pin == 12)
            return (_count >= 5) ? False : True;
        return (_outputs[pin].first == (size_t)_count) ? True : False;
    }
}