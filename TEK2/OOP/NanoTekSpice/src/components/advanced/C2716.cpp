/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C2716.cpp
*/

#include "components/advanced/C2716.hpp"
#include <fstream>

/**
 * @file C2716.cpp
 * @brief Implementation of the 2716 2K × 8-bit EPROM component.
 *
 * The C2716 component simulates a CMOS 2716 EPROM (Erasable
 * Programmable Read-Only Memory) integrated circuit. It contains
 * 2048 memory addresses where each address stores one byte (8 bits).
 *
 * Inputs:
 * - A0–A10 : 11-bit address bus
 * - CE     : Chip enable
 * - OE     : Output enable
 *
 * Outputs:
 * - D0–D7 : Data outputs corresponding to the selected memory address
 *
 * Behavior:
 * - When both CE and OE are active, the component outputs the stored
 *   byte at the selected address.
 * - The ROM content is loaded at initialization from the file
 *   `rom.bin`.
 * - If the file is missing, the memory is initialized with default
 *   values.
 *
 * Undefined address lines propagate Undefined outputs.
 *
 * @see nts::IComponent
 */

namespace nts {
    C2716::C2716()
    {
        const int addressPins[11] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19};
        const int controlPins[2] = {18, 20};
        const int dataPins[8] = {9, 10, 11, 13, 14, 15, 16, 17};
        std::ifstream file("./rom.bin", std::ios::binary);
        char byte;
        int address = 0;

        for (int pin : addressPins)
            _inputs[pin] = false;
        for (int pin : controlPins)
            _inputs[pin] = false;
        for (int i = 0; i < 2048; i++)
            for (int j = 0; j < 8; j++)
                _memory[i][j] = True;
        for (int pin : dataPins)
            _outputs[pin] = {0, 0};
        if (!file)
            return;
        while (file.get(byte) && address < 2048) {
            for (int bit = 0; bit < 8; bit++)
                _memory[address][bit] = ((byte >> bit) & 1) ? True : False;
            address++;
        }
        file.close();
    }

    void C2716::simulate([[maybe_unused]] std::size_t tick) {}

    Tristate C2716::compute(std::size_t pin)
    {
        const int dataPins[8] = {9, 10, 11, 13, 14, 15, 16, 17};
        int dataIndex = -1;

        if (pin < 1 || pin > 24)
            return Undefined;
        if (pin == 12 || pin == 24)
            return Undefined;
        for (int i = 0; i < 8; i++) {
            if (dataPins[i] == static_cast<int>(pin)) {
                dataIndex = i;
                break;
            }
        }
        if (dataIndex == -1)
            return getLink(pin);
        Tristate chipEnable   = getLink(18);
        Tristate outputEnable = getLink(20);
        if (chipEnable != False || outputEnable != False)
            return Undefined;
        int address = getAddress();
        if (address == -1)
            return Undefined;
        return _memory[address][dataIndex];
    }

    int C2716::getAddress()
    {
        const int addressPins[11] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19};
        int address = 0;

        for (int i = 0; i < 11; i++) {
            Tristate bit = getLink(addressPins[i]);
            if (bit == Undefined)
                return -1;
            if (bit == True)
                address |= (1 << i);
        }
        return address;
    }
}