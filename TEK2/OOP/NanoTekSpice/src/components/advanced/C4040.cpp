/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4040.cpp
*/

#include "components/advanced/C4040.hpp"
#include <iostream>

/**
 * @file C4040.cpp
 * @brief Implementation of the 4040 12-stage binary ripple counter.
 *
 * The C4040 component simulates a CMOS 4040 integrated circuit,
 * which is a 12-bit binary ripple counter.
 *
 * The counter increments on each falling edge of the clock input.
 * Each output corresponds to a binary division of the clock
 * frequency.
 *
 * Inputs:
 * - Clock : Counter clock signal
 * - Reset : Asynchronous reset
 *
 * Outputs:
 * - Q1–Q12 : Binary counter outputs
 *
 * The internal counter increases at every valid clock transition
 * and each output reflects a specific bit of the counter value.
 *
 * When reset is active, the counter is cleared to zero.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4040::C4040(): _count(0), _prevClock(false)
    {
        _inputs[10] = false;
        _inputs[11] = false;
        _outputs[9] = {1, 0};
        _outputs[7] = {2, 0};
        _outputs[6] = {4, 0};
        _outputs[5] = {8, 0};
        _outputs[3] = {16, 0};
        _outputs[2] = {32, 0};
        _outputs[4] = {64, 0};
        _outputs[13] = {128, 0};
        _outputs[12] = {256, 0};
        _outputs[14] = {512, 0};
        _outputs[15] = {1024, 0};
        _outputs[1] = {2048, 0};
    }

    void C4040::simulate([[maybe_unused]] std::size_t tick)
    {
        if (_prevClock == True && getLink(10) == False)
            _count++;
        if (getLink(11) == True)
            _count = 0;
        _prevClock = getLink(10);
    }

    Tristate C4040::compute(std::size_t pin) {
        _inputs[pin] = true;
        int weight = _outputs[pin].first;
    
        if (_count & weight) {
            return True;
        } else {
            return False;
        }
    }   
}