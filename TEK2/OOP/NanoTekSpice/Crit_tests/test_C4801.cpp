/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4801.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/advanced/C4801.hpp"
#include "components/special/InputComponent.hpp"

static const int ADDR_PINS[10] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
static const int DATA_PINS[8]  = {9, 10, 11, 13, 14, 15, 16, 17};

struct C4801Fixture {
    nts::C4801          chip;
    nts::InputComponent ce;
    nts::InputComponent oe;
    nts::InputComponent we;
    nts::InputComponent addr[10];
    nts::InputComponent data[8];

    C4801Fixture()
    {
        chip.setLink(18, ce, 1); ce.setLink(1, chip, 18);
        chip.setLink(20, oe, 1); oe.setLink(1, chip, 20);
        chip.setLink(21, we, 1); we.setLink(1, chip, 21);

        for (int i = 0; i < 10; i++) {
            chip.setLink(ADDR_PINS[i], addr[i], 1);
            addr[i].setLink(1, chip, ADDR_PINS[i]);
            addr[i].setValue(nts::Tristate::False);
        }
        for (int i = 0; i < 8; i++) {
            chip.setLink(DATA_PINS[i], data[i], 1);
            data[i].setLink(1, chip, DATA_PINS[i]);
            data[i].setValue(nts::Tristate::False);
        }

        ce.setValue(nts::Tristate::False);
        oe.setValue(nts::Tristate::False);
        we.setValue(nts::Tristate::True);
    }

    void setAddress(int address)
    {
        for (int i = 0; i < 10; i++)
            addr[i].setValue(((address >> i) & 1) ? nts::Tristate::True : nts::Tristate::False);
    }

    void writeByte(int address, int value)
    {
        setAddress(address);
        for (int i = 0; i < 8; i++)
            data[i].setValue(((value >> i) & 1) ? nts::Tristate::True : nts::Tristate::False);
        we.setValue(nts::Tristate::False);
        chip.simulate(0);
        we.setValue(nts::Tristate::True);
        chip.simulate(0);
    }

    int readByte(int address)
    {
        setAddress(address);
        int value = 0;
        for (int i = 0; i < 8; i++)
            if (chip.compute(DATA_PINS[i]) == nts::Tristate::True)
                value |= (1 << i);
        return value;
    }
};

Test(c4801_init, all_data_undefined_before_write)
{
    C4801Fixture f;
    for (int pin : DATA_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::Undefined);
}

Test(c4801_write_read, write_and_read_byte_at_address_0)
{
    C4801Fixture f;
    f.writeByte(0, 0xA5);
    cr_assert_eq(f.readByte(0), 0xA5);
}

Test(c4801_write_read, write_and_read_byte_at_address_1)
{
    C4801Fixture f;
    f.writeByte(1, 0x3C);
    cr_assert_eq(f.readByte(1), 0x3C);
}

Test(c4801_write_read, write_and_read_byte_at_last_address)
{
    C4801Fixture f;
    f.writeByte(1023, 0xFF);
    cr_assert_eq(f.readByte(1023), 0xFF);
}

Test(c4801_write_read, write_zero_byte)
{
    C4801Fixture f;
    f.writeByte(0, 0xFF);
    f.writeByte(0, 0x00);
    cr_assert_eq(f.readByte(0), 0x00);
}

Test(c4801_write_read, write_ff_byte)
{
    C4801Fixture f;
    f.writeByte(0, 0xFF);
    cr_assert_eq(f.readByte(0), 0xFF);
}

Test(c4801_write_read, multiple_addresses_independent)
{
    C4801Fixture f;
    f.writeByte(0,   0x01);
    f.writeByte(10,  0x0A);
    f.writeByte(100, 0x64);
    cr_assert_eq(f.readByte(0),   0x01);
    cr_assert_eq(f.readByte(10),  0x0A);
    cr_assert_eq(f.readByte(100), 0x64);
}

Test(c4801_write_read, overwrite_updates_value)
{
    C4801Fixture f;
    f.writeByte(0, 0xAA);
    f.writeByte(0, 0x55);
    cr_assert_eq(f.readByte(0), 0x55);
}

Test(c4801_ce, outputs_undefined_when_ce_high)
{
    C4801Fixture f;
    f.writeByte(0, 0xFF);
    f.ce.setValue(nts::Tristate::True);
    for (int pin : DATA_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::Undefined);
}

Test(c4801_ce, outputs_undefined_when_ce_undefined)
{
    C4801Fixture f;
    f.writeByte(0, 0xFF);
    f.ce.setValue(nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c4801_ce, no_write_when_ce_high)
{
    C4801Fixture f;
    f.ce.setValue(nts::Tristate::True);
    f.setAddress(0);
    f.we.setValue(nts::Tristate::False);
    f.chip.simulate(0);
    f.we.setValue(nts::Tristate::True);
    f.ce.setValue(nts::Tristate::False);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c4801_oe, outputs_undefined_when_oe_high)
{
    C4801Fixture f;
    f.writeByte(0, 0xFF);
    f.oe.setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c4801_oe, outputs_valid_when_oe_low)
{
    C4801Fixture f;
    f.writeByte(0, 0xFF);
    f.oe.setValue(nts::Tristate::False);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::True);
}

Test(c4801_we, outputs_undefined_during_write)
{
    C4801Fixture f;
    f.setAddress(0);
    f.we.setValue(nts::Tristate::False);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c4801_we, outputs_valid_after_write_released)
{
    C4801Fixture f;
    f.writeByte(0, 0xFF);
    cr_assert_neq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c4801_addr, undefined_address_bit_blocks_write)
{
    C4801Fixture f;
    f.addr[0].setValue(nts::Tristate::Undefined);
    f.we.setValue(nts::Tristate::False);
    f.chip.simulate(0);
    f.we.setValue(nts::Tristate::True);
    f.addr[0].setValue(nts::Tristate::False);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c4801_addr, undefined_address_bit_blocks_read)
{
    C4801Fixture f;
    f.writeByte(0, 0xFF);
    f.addr[0].setValue(nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c4801_pin, non_data_pin_returns_undefined)
{
    C4801Fixture f;
    cr_assert_eq(f.chip.compute(1), nts::Tristate::Undefined);
}

Test(c4801_pin, all_data_pins_readable_after_write)
{
    C4801Fixture f;
    f.writeByte(0, 0xFF);
    for (int pin : DATA_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::True);
}