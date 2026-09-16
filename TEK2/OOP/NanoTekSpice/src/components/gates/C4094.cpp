/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4094.cpp
*/

#include "components/gates/C4094.hpp"

/**
 * @file C4094.cpp
 * @brief Implementation of the 4094 8-bit shift and storage register.
 *
 * The C4094 component simulates a CMOS 4094 integrated circuit,
 * which is an 8-bit serial-in/parallel-out shift register with
 * a storage latch.
 *
 * Inputs:
 * - DATA   : Serial data input
 * - CLOCK  : Shift register clock
 * - STROBE : Latch control signal
 * - OE     : Output enable
 *
 * Outputs:
 * - Q0–Q7  : Parallel outputs from the latch or shift register
 * - QS     : Serial output
 * - QS'    : Complementary serial output
 *
 * Behavior:
 * - On the rising edge of the clock, the shift register shifts
 *   and inserts the serial data input.
 * - The strobe signal transfers the shift register contents
 *   into the output latch.
 * - Outputs are enabled or disabled depending on the OE signal.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4094::C4094() : _shiftRegister{Undefined, Undefined, Undefined, Undefined, Undefined, Undefined, Undefined, Undefined},
        _latch{Undefined, Undefined, Undefined, Undefined, Undefined, Undefined, Undefined, Undefined}
    {
        _inputs[1] = false;
        _inputs[2] = false;
        _inputs[3] = false;
        _inputs[15] = false;
        _outputs[4] = {0, 0};
        _outputs[5] = {0, 0};
        _outputs[6] = {0, 0};
        _outputs[7] = {0, 0};
        _outputs[14] = {0, 0};
        _outputs[13] = {0, 0};
        _outputs[12] = {0, 0};
        _outputs[11] = {0, 0};
        _outputs[9] = {0, 0};
        _outputs[10] = {0, 0};
    }

    void C4094::simulate([[maybe_unused]] std::size_t tick)
    {
        Tristate clock = getLink(3);
        Tristate strobe = getLink(1);
        Tristate data = getLink(2);
        
        if (_previousClock == False && clock == True) {
            for (int i = 7; i > 0; i--) {
                _shiftRegister[i] = _shiftRegister[i - 1];
            }
            _shiftRegister[0] = data;
            _qs = _shiftRegister[7];
        }
        if (_previousClock == True && clock == False) {
            _qsPrime = _shiftRegister[7];
        }
        if (_previousStrobe == True && strobe == False) {
            for (int i = 0; i < 8; i++) {
                _latch[i] = _shiftRegister[i];
            }
        }
        _previousClock = clock;
        _previousStrobe = strobe;
    }

    Tristate C4094::compute(std::size_t pin)
    {
        Tristate outputEnable = getLink(15);
        Tristate strobe = getLink(1);
        int index = -1;
        _inputs[pin] = true;

        if (pin == 9)
            return _qs;
        if (pin == 10)
            return _qsPrime;
        if (outputEnable == False)
            return Undefined;
        if (outputEnable == Undefined)
            return Undefined;
        switch (pin) {
            case 4: index = 0; break;
            case 5: index = 1; break;
            case 6: index = 2; break;
            case 7: index = 3; break;
            case 14: index = 4; break;
            case 13: index = 5; break;
            case 12: index = 6; break;
            case 11: index = 7; break;
        }
        if (index != -1) {
            if (strobe == True)
                return _shiftRegister[index];
            return _latch[index];
        }
        return Undefined;
    }
}