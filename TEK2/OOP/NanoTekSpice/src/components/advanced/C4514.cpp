/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4514.cpp
*/

#include "components/advanced/C4514.hpp"

/**
 * @file C4514.cpp
 * @brief Implementation of the 4514 4-to-16 line decoder with latch.
 *
 * The C4514 component simulates a CMOS 4514 integrated circuit,
 * which is a 4-to-16 line decoder with latched inputs.
 *
 * Inputs:
 * - A, B, C, D : 4-bit binary input
 * - STROBE     : Latch control input
 * - INHIBIT    : Output disable signal
 *
 * Outputs:
 * - Q0–Q15 : One-hot decoded outputs
 *
 * When the strobe signal is active, the input values are latched
 * internally. The latched value is decoded to activate exactly one
 * of the sixteen outputs.
 *
 * If the inhibit signal is active, all outputs are forced to False.
 * If any latched value is Undefined, the outputs return Undefined.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4514::C4514() : _latchedA(Undefined), _latchedB(Undefined),  _latchedC(Undefined), _latchedD(Undefined)
    {
        _inputs[1] = false;
        _inputs[2] = false;
        _inputs[3] = false;
        _inputs[21] = false;
        _inputs[22] = false;
        _inputs[23] = false;
        _outputs[11] = {0, 0};
        _outputs[9] = {0, 0};
        _outputs[10] = {0, 0};
        _outputs[8] = {0, 0};
        _outputs[7] = {0, 0};
        _outputs[6] = {0, 0};
        _outputs[5] = {0, 0};
        _outputs[4] = {0, 0};
        _outputs[18] = {0, 0};
        _outputs[17] = {0, 0};
        _outputs[20] = {0, 0};
        _outputs[19] = {0, 0};
        _outputs[14] = {0, 0};
        _outputs[13] = {0, 0};
        _outputs[15] = {0, 0};
        _outputs[16] = {0, 0};
    }

    void C4514::simulate([[maybe_unused]] std::size_t tick)
    {
        Tristate strobe = getLink(1);

        if (strobe == True) {
            _latchedA = getLink(2);
            _latchedB = getLink(3);
            _latchedC = getLink(21);
            _latchedD = getLink(22);
        }
    }

    Tristate C4514::compute(std::size_t pin)
    {
        int outputNum = -1;

        switch (pin) {
            case 11: outputNum = 0; break;
            case 9: outputNum = 1; break;
            case 10: outputNum = 2; break;
            case 8: outputNum = 3; break;
            case 7: outputNum = 4; break;
            case 6: outputNum = 5; break;
            case 5: outputNum = 6; break;
            case 4: outputNum = 7; break;
            case 18: outputNum = 8; break;
            case 17: outputNum = 9; break;
            case 20: outputNum = 10; break;
            case 19: outputNum = 11; break;
            case 14: outputNum = 12; break;
            case 13: outputNum = 13; break;
            case 15: outputNum = 14; break;
            case 16: outputNum = 15; break;
        }
        if (outputNum == -1)
            return getLink(pin);
        Tristate inhibit = getLink(23);
        if (inhibit == True)
            return False;
        if (inhibit == Undefined)
            return Undefined;
        if (_latchedA == Undefined || _latchedB == Undefined ||
            _latchedC == Undefined || _latchedD == Undefined)
            return Undefined;
        int selected = (_latchedD == True ? 8 : 0) + (_latchedC == True ? 4 : 0)
            + (_latchedB == True ? 2 : 0) + (_latchedA == True ? 1 : 0);
        return (outputNum == selected) ? True : False;
    }
}