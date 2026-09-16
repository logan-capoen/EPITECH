/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** Logger.cpp
*/

#include "components/advanced/Logger.hpp"
#include <fstream>

/**
 * @file Logger.cpp
 * @brief Implementation of a logging component for binary output.
 *
 * The Logger component captures an 8-bit value from its inputs and
 * writes it to a binary file when a clock event occurs.
 *
 * Inputs:
 * - D0–D7 : Data inputs forming one byte
 * - CLK   : Clock input
 * - INH   : Inhibit input
 *
 * Behavior:
 * - On the rising edge of the clock signal, if the inhibit input is
 *   inactive, the component reads the 8 input bits.
 * - If all bits are defined, they are combined into a single byte.
 * - The byte is appended to the file `log.bin` in binary format.
 *
 *
 * @see nts::IComponent
 */

namespace nts {
    Logger::Logger() : _previousClock(False) {}

    bool Logger::buildByte(unsigned char &out)
    {
        out = 0;
        for (int i = 0; i < 8; i++) {
            Tristate bit = getLink(i + 1);
            if (bit != True && bit != False)
                return false;
            if (bit == True)
                out |= (1 << i);
        }
        return true;
    }

    void Logger::simulate([[maybe_unused]] std::size_t tick)
    {
        Tristate clock = getLink(9);
        Tristate inhibit = getLink(10);
        if (_previousClock == False && clock == True && inhibit == False) {
            unsigned char byte = 0;
            if (buildByte(byte)) {
                std::ofstream file("./log.bin", std::ios::binary | std::ios::app);
                if (file.is_open())
                    file.write(reinterpret_cast<char*>(&byte), 1);
            }
        }
        _previousClock = clock;
    }

    Tristate Logger::compute([[maybe_unused]] std::size_t pin)
    {
        return Undefined;
    }
}