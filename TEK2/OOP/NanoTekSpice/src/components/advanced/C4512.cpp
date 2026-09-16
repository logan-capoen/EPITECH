/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4512.cpp
*/

#include "components/advanced/C4512.hpp"

/**
 * @file C4512.cpp
 * @brief Implementation of the 4512 8-channel data selector (multiplexer).
 *
 * The C4512 component simulates a CMOS 4512 integrated circuit,
 * which acts as an 8-channel data selector (multiplexer). It selects
 * one of several input signals and forwards it to the output.
 *
 * Inputs:
 * - A, B, C : Selection inputs
 * - D0–D7   : Data inputs
 * - INH     : Inhibit input (disables the output)
 * - STROBE  : Control signal affecting output behavior
 *
 * Output:
 * - Q : Selected data output
 *
 * The selection inputs determine which data input is routed to the
 * output. If the inhibit signal is active, the output is disabled.
 * Undefined control inputs propagate an Undefined result.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4512::C4512()
    {
        _inputs[1] = false;
        _inputs[2] = false;
        _inputs[3] = false;
        _inputs[4] = false;
        _inputs[5] = false;
        _inputs[6] = false;
        _inputs[7] = false;
        _inputs[9] = false;
        _inputs[10] = false;
        _inputs[15] = false;
        _inputs[11] = false;
        _inputs[12] = false;
        _inputs[13] = false;
        _outputs[14] = {0, 0};
    }


    Tristate C4512::compute([[maybe_unused]] std::size_t pin) {
        _inputs[pin] = true;
        int value = 0;
        Tristate first = getLink(11);
        Tristate second = getLink(12);
        Tristate third = getLink(13);
        
        if (first == Undefined || second == Undefined || third == Undefined || getLink(15) == True)
            return Undefined;
        if (getLink(10) == True)
            return False;
        value = first == True ? value + 1 : value;
        value = second == True ? value + 2 : value;
        value = third == True ? value + 4 : value;
        value = value == 7 ? 9 : value;
        return getLink(value + 1);
    }   
}