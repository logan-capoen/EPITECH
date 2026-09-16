/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4013.cpp
*/

#include "components/advanced/C4013.hpp"

/**
 * @file C4013.cpp
 * @brief Implementation of the 4013 dual D-type flip-flop component.
 *
 * The C4013 component simulates a CMOS 4013 integrated circuit,
 * which contains two independent D-type flip-flops with set and
 * reset controls.
 *
 * Each flip-flop has:
 * - Data input (D)
 * - Clock input (C)
 * - Asynchronous set (S)
 * - Asynchronous reset (R)
 * - Q output
 * - !Q inverted output
 *
 * The flip-flop captures the value of the D input on the rising
 * edge of the clock signal. The set and reset inputs override
 * the stored value asynchronously.
 *
 * This implementation keeps track of the previous clock state
 * in order to detect rising edges.
 *
 * Outputs always reflect the stored internal state.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4013::C4013(): _value1(Undefined), _value2(Undefined), _prevC1(Undefined), _prevC2(Undefined)
    {
        _inputs[3] = false;
        _inputs[4] = false;
        _inputs[5] = false;
        _inputs[6] = false;
        _outputs[1] = {0, 0};
        _outputs[2] = {0, 0};
        _inputs[11] = false;
        _inputs[10] = false;
        _inputs[9] = false;
        _inputs[8] = false;
        _outputs[13] = {0, 0};
        _outputs[12] = {0, 0};
    }

    void C4013::simulate(std::size_t tick [[maybe_unused]])
    {
        if (_prevC1 == False && getLink(3) == True)
            _value1 = getLink(5);
        if (getLink(4) == True)
            _value1 = False;
        if (getLink(6) == True)
            _value1 = True;
        _prevC1 = getLink(3);
        if (_prevC2 == False && getLink(11) == True)
            _value2 = getLink(9);
        if (getLink(10) == True)
            _value2 = False;
        if (getLink(8) == True)
            _value2 = True;
        _prevC2 = getLink(11);
    }

    Tristate C4013::compute(std::size_t pin) {
        _inputs[pin] = true;
        switch (pin)
        {
        case 1:
            return _value1;
        case 2:
            return !_value1;
        case 13:
            return _value2;
        case 12:
            return !_value2;
        default:
            return Undefined;
        }
    }   
}