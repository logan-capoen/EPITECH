/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C2716.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fstream>
#include <cstdio>
#include "components/advanced/C2716.hpp"
#include "components/special/InputComponent.hpp"

static const int ADDR_PINS[11] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19};
static const int DATA_PINS[8]  = {9, 10, 11, 13, 14, 15, 16, 17};

struct C2716Fixture {
    nts::C2716          chip;
    nts::InputComponent ce;
    nts::InputComponent oe;
    nts::InputComponent addr[11];

    C2716Fixture()
    {
        chip.setLink(18, ce, 1); ce.setLink(1, chip, 18);
        chip.setLink(20, oe, 1); oe.setLink(1, chip, 20);
        for (int i = 0; i < 11; i++) {
            chip.setLink(ADDR_PINS[i], addr[i], 1);
            addr[i].setLink(1, chip, ADDR_PINS[i]);
            addr[i].setValue(nts::Tristate::False);
        }
        ce.setValue(nts::Tristate::False);
        oe.setValue(nts::Tristate::False);
    }

    void setAddress(int address)
    {
        for (int i = 0; i < 11; i++) {
            addr[i].setValue(((address >> i) & 1)
                ? nts::Tristate::True
                : nts::Tristate::False);
        }
    }

    int readByte(int address)
    {
        setAddress(address);
        int value = 0;
        for (int i = 0; i < 8; i++) {
            nts::Tristate bit = chip.compute(DATA_PINS[i]);
            if (bit == nts::Tristate::True)
                value |= (1 << i);
        }
        return value;
    }
};

static void write_rom(const unsigned char *data, int size)
{
    std::ofstream f("./rom.bin", std::ios::binary);
    f.write(reinterpret_cast<const char *>(data), size);
}

static void remove_rom()
{
    std::remove("./rom.bin");
}

Test(c2716_init, all_bits_true_without_rom_file)
{
    remove_rom();
    C2716Fixture f;
    cr_assert_eq(f.readByte(0), 0xFF);
}

Test(c2716_init, all_bits_true_at_last_address)
{
    remove_rom();
    C2716Fixture f;
    cr_assert_eq(f.readByte(2047), 0xFF);
}

Test(c2716_rom, reads_first_byte_correctly)
{
    unsigned char rom[2048];
    rom[0] = 0xA5;
    write_rom(rom, 2048);
    C2716Fixture f;
    cr_assert_eq(f.readByte(0), 0xA5);
    remove_rom();
}

Test(c2716_rom, reads_second_byte_correctly)
{
    unsigned char rom[2048] = {};
    rom[1] = 0x3C;
    write_rom(rom, 2048);
    C2716Fixture f;
    cr_assert_eq(f.readByte(1), 0x3C);
    remove_rom();
}

Test(c2716_rom, reads_last_byte_correctly)
{
    unsigned char rom[2048] = {};
    rom[2047] = 0xBE;
    write_rom(rom, 2048);
    C2716Fixture f;
    cr_assert_eq(f.readByte(2047), 0xBE);
    remove_rom();
}

Test(c2716_rom, reads_zero_byte_correctly)
{
    unsigned char rom[2048] = {};
    write_rom(rom, 2048);
    C2716Fixture f;
    cr_assert_eq(f.readByte(0), 0x00);
    remove_rom();
}

Test(c2716_rom, reads_ff_byte_correctly)
{
    unsigned char rom[2048];
    for (int i = 0; i < 2048; i++) rom[i] = 0xFF;
    write_rom(rom, 2048);
    C2716Fixture f;
    cr_assert_eq(f.readByte(512), 0xFF);
    remove_rom();
}

Test(c2716_rom, address_0_and_1_differ)
{
    unsigned char rom[2048] = {};
    rom[0] = 0xAA;
    rom[1] = 0x55;
    write_rom(rom, 2048);
    C2716Fixture f;
    cr_assert_neq(f.readByte(0), f.readByte(1));
    remove_rom();
}

Test(c2716_rom, multiple_addresses_readable)
{
    unsigned char rom[2048] = {};
    rom[0]   = 0x01;
    rom[10]  = 0x0A;
    rom[100] = 0x64;
    write_rom(rom, 2048);
    C2716Fixture f;
    cr_assert_eq(f.readByte(0),   0x01);
    cr_assert_eq(f.readByte(10),  0x0A);
    cr_assert_eq(f.readByte(100), 0x64);
    remove_rom();
}

Test(c2716_ce, outputs_undefined_when_ce_high)
{
    unsigned char rom[2048] = {};
    rom[0] = 0xFF;
    write_rom(rom, 2048);
    C2716Fixture f;
    f.ce.setValue(nts::Tristate::True);
    for (int pin : DATA_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::Undefined);
    remove_rom();
}

Test(c2716_ce, outputs_undefined_when_ce_undefined)
{
    remove_rom();
    C2716Fixture f;
    f.ce.setValue(nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c2716_ce, outputs_valid_when_ce_low)
{
    unsigned char rom[2048] = {};
    rom[0] = 0xFF;
    write_rom(rom, 2048);
    C2716Fixture f;
    f.ce.setValue(nts::Tristate::False);
    cr_assert_neq(f.chip.compute(9), nts::Tristate::Undefined);
    remove_rom();
}

Test(c2716_oe, outputs_undefined_when_oe_high)
{
    unsigned char rom[2048] = {};
    rom[0] = 0xFF;
    write_rom(rom, 2048);
    C2716Fixture f;
    f.oe.setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
    remove_rom();
}

Test(c2716_oe, outputs_undefined_when_oe_undefined)
{
    remove_rom();
    C2716Fixture f;
    f.oe.setValue(nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c2716_oe, outputs_valid_when_oe_low)
{
    unsigned char rom[2048] = {};
    rom[0] = 0xFF;
    write_rom(rom, 2048);
    C2716Fixture f;
    f.oe.setValue(nts::Tristate::False);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::True);
    remove_rom();
}

Test(c2716_addr, undefined_address_bit_returns_undefined)
{
    remove_rom();
    C2716Fixture f;
    f.addr[0].setValue(nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::Undefined);
}

Test(c2716_addr, all_address_bits_false_reads_address_0)
{
    unsigned char rom[2048] = {};
    rom[0] = 0b10110010;
    write_rom(rom, 2048);
    C2716Fixture f;
    f.setAddress(0);
    cr_assert_eq(f.readByte(0), 0b10110010);
    remove_rom();
}

Test(c2716_pin, non_data_pin_returns_undefined)
{
    remove_rom();
    C2716Fixture f;
    cr_assert_eq(f.chip.compute(1), nts::Tristate::Undefined);
}

Test(c2716_pin, all_data_pins_accessible)
{
    unsigned char rom[2048];
    for (int i = 0; i < 2048; i++) rom[i] = 0xFF;
    write_rom(rom, 2048);
    C2716Fixture f;
    for (int pin : DATA_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::True);
    remove_rom();
}