/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4008.cpp
*/

#include "components/advanced/C4008.hpp"

/**
 * @file C4008.cpp
 * @brief Implementation of the 4008 4-bit full adder component.
 *
 * The C4008 component simulates a CMOS 4008 integrated circuit,
 * which is a 4-bit binary full adder. It performs the addition of
 * two 4-bit numbers and a carry input, producing a 4-bit result
 * and a carry output.
 *
 * Inputs:
 * - A1–A4 : First 4-bit operand
 * - B1–B4 : Second 4-bit operand
 * - Cin   : Carry input
 *
 * Outputs:
 * - S1–S4 : Sum outputs
 * - Cout  : Carry output
 *
 * The component reads all inputs during the simulation phase,
 * computes the integer sum, and exposes the corresponding bits
 * through the compute() method.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4008::C4008()
    {
        _inputs[7] = false;
        _inputs[5] = false;
        _inputs[3] = false;
        _inputs[1] = false;
        _inputs[6] = false;
        _inputs[4] = false;
        _inputs[2] = false;
        _inputs[15] = false;
        _inputs[9] = false;
        _outputs[10] = {1, 0};
        _outputs[11] = {2, 0};
        _outputs[12] = {4, 0};
        _outputs[13] = {8, 0};
        _outputs[14] = {16, 0};
    }

    void C4008::simulate(std::size_t tick [[maybe_unused]])
    {
        int a = (getLink(1)  == True ? 1 : 0) | (getLink(3)  == True ? 2 : 0) | (getLink(9)  == True ? 4 : 0) | (getLink(11) == True ? 8 : 0);
        int b = (getLink(2)  == True ? 1 : 0) | (getLink(4)  == True ? 2 : 0) | (getLink(10) == True ? 4 : 0) | (getLink(12) == True ? 8 : 0);
        int cin = (getLink(7) == True ? 1 : 0);
        _result = a + b + cin;
    }

    Tristate C4008::compute(std::size_t pin) {
        _inputs[pin] = true;
        return (_result & _outputs[pin].first) ? True : False;
    }   
}