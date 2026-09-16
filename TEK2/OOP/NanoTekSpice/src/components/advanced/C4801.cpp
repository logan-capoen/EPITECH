/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** C4801.cpp
*/

#include "components/advanced/C4801.hpp"

/**
 * @file C4801.cpp
 * @brief Implementation of the 4801 1K × 8-bit static RAM component.
 *
 * The C4801 component simulates a 1024-address memory device where
 * each address stores one byte (8 bits).
 *
 * Inputs:
 * - A0–A9 : 10-bit address bus
 * - D0–D7 : 8-bit data bus
 * - CE    : Chip enable
 * - OE    : Output enable
 * - WE    : Write enable
 *
 * Outputs:
 * - D0–D7 : Data outputs when reading
 *
 * Behavior:
 * - When WE is active and the chip is enabled, the component writes
 *   the value from the data bus into the selected memory address.
 * - When OE is active and the chip is enabled, the stored byte at the
 *   selected address is output on the data bus.
 *
 * Undefined address bits or control signals propagate Undefined
 * values to the outputs.
 *
 * @see nts::IComponent
 */

namespace nts {
    C4801::C4801()
    {
        const int addressPins[10] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
        const int controlPins[3] = {18, 20, 21};
        const int dataPins[8] = {9, 10, 11, 13, 14, 15, 16, 17};

        for (int pin : addressPins)
            _inputs[pin] = false;
        for (int pin : controlPins)
            _inputs[pin] = false;
        for (int pin : dataPins) {
            _inputs[pin] = false;
            _outputs[pin] = {0, 0};
        }
        for (int i = 0; i < 1024; i++)
            for (int j = 0; j < 8; j++)
                _memory[i][j] = Undefined;
    }

    void C4801::simulate([[maybe_unused]] std::size_t tick)
    {
        const int dataPins[8] = {9, 10, 11, 13, 14, 15, 16, 17};
        Tristate chipEnable = getLink(18);
        Tristate writeEnable = getLink(21);
        int address = 0;

        if (chipEnable == True || chipEnable == Undefined)
            return;
        address = getAddress();
        if (address == -1)
            return;
        if (writeEnable == False) {
            for (int i = 0; i < 8; i++)
                _memory[address][i] = getLink(dataPins[i]);
        }
    }

    Tristate C4801::compute(std::size_t pin)
    {
        const int dataPins[8] = {9, 10, 11, 13, 14, 15, 16, 17};
        Tristate chipEnable = getLink(18);
        Tristate outputEnable = getLink(20);
        Tristate writeEnable = getLink(21);
        int dataIndex = -1;
        int address = 0;
        _inputs[pin] = true;

        for (int i = 0; i < 8; i++) {
            if (dataPins[i] == static_cast<int>(pin)) {
                dataIndex = i;
                break;
            }
        }
        if (dataIndex == -1)
            return Undefined;
        if (chipEnable == True || chipEnable == Undefined)
            return Undefined;
        if (writeEnable == False)
            return Undefined;
        if (outputEnable == False) {
            address = getAddress();
            if (address == -1)
                return Undefined;
            return _memory[address][dataIndex];
        }
        return Undefined;
    }

    int C4801::getAddress()
    {
        const int addressPins[10] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
        int address = 0;

        for (int i = 0; i < 10; i++) {
            Tristate bit = getLink(addressPins[i]);
            if (bit == Undefined)
                return -1;
            if (bit == True)
                address |= (1 << i);
        }
        return address;
    }
}