/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_Logger.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fstream>
#include <cstdio>
#include "components/advanced/Logger.hpp"
#include "components/special/InputComponent.hpp"

struct LoggerFixture {
    nts::Logger         chip;
    nts::InputComponent data[8];
    nts::InputComponent clock;
    nts::InputComponent inhibit;

    LoggerFixture()
    {
        for (int i = 0; i < 8; i++) {
            chip.setLink(i + 1, data[i], 1);
            data[i].setLink(1, chip, i + 1);
            data[i].setValue(nts::Tristate::False);
        }
        chip.setLink(9,  clock,   1); clock.setLink(1,   chip, 9);
        chip.setLink(10, inhibit, 1); inhibit.setLink(1, chip, 10);

        clock.setValue(nts::Tristate::False);
        inhibit.setValue(nts::Tristate::False);
    }

    void clockRise()
    {
        clock.setValue(nts::Tristate::False);
        chip.simulate(0);
        clock.setValue(nts::Tristate::True);
        chip.simulate(0);
    }

    void setByte(int value)
    {
        for (int i = 0; i < 8; i++)
            data[i].setValue(((value >> i) & 1) ? nts::Tristate::True : nts::Tristate::False);
    }

    std::string readLog()
    {
        std::ifstream f("./log.bin", std::ios::binary);
        return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    }

    int logSize()
    {
        return (int)readLog().size();
    }
};

static void remove_log()
{
    std::remove("./log.bin");
}

Test(logger_compute, compute_always_returns_undefined)
{
    remove_log();
    LoggerFixture f;
    for (int i = 1; i <= 10; i++)
        cr_assert_eq(f.chip.compute(i), nts::Tristate::Undefined);
}

Test(logger_write, writes_one_byte_on_rising_clock)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0xA5);
    f.clockRise();
    cr_assert_eq(f.logSize(), 1);
}

Test(logger_write, written_byte_value_is_correct)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0xA5);
    f.clockRise();
    std::string log = f.readLog();
    cr_assert_eq((unsigned char)log[0], 0xA5);
}

Test(logger_write, writes_zero_byte)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0x00);
    f.clockRise();
    std::string log = f.readLog();
    cr_assert_eq((unsigned char)log[0], 0x00);
}

Test(logger_write, writes_ff_byte)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0xFF);
    f.clockRise();
    std::string log = f.readLog();
    cr_assert_eq((unsigned char)log[0], 0xFF);
}

Test(logger_write, no_write_without_rising_edge)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0xAA);
    f.clock.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    f.chip.simulate(0);
    cr_assert_eq(f.logSize(), 0);
}

Test(logger_write, no_write_when_clock_stays_low)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0xAA);
    f.chip.simulate(0);
    f.chip.simulate(0);
    cr_assert_eq(f.logSize(), 0);
}

Test(logger_write, appends_multiple_bytes)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0x01);
    f.clockRise();
    f.setByte(0x02);
    f.clockRise();
    f.setByte(0x03);
    f.clockRise();
    cr_assert_eq(f.logSize(), 3);
    std::string log = f.readLog();
    cr_assert_eq((unsigned char)log[0], 0x01);
    cr_assert_eq((unsigned char)log[1], 0x02);
    cr_assert_eq((unsigned char)log[2], 0x03);
}

Test(logger_inhibit, no_write_when_inhibit_true)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0xFF);
    f.inhibit.setValue(nts::Tristate::True);
    f.clockRise();
    cr_assert_eq(f.logSize(), 0);
}

Test(logger_inhibit, writes_when_inhibit_false)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0xFF);
    f.inhibit.setValue(nts::Tristate::False);
    f.clockRise();
    cr_assert_eq(f.logSize(), 1);
}

Test(logger_inhibit, inhibit_blocks_only_while_active)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0xAA);
    f.inhibit.setValue(nts::Tristate::True);
    f.clockRise();
    f.inhibit.setValue(nts::Tristate::False);
    f.setByte(0xBB);
    f.clockRise();
    cr_assert_eq(f.logSize(), 1);
    std::string log = f.readLog();
    cr_assert_eq((unsigned char)log[0], 0xBB);
}

Test(logger_inhibit, undefined_inhibit_does_not_write)
{
    remove_log();
    LoggerFixture f;
    f.setByte(0xFF);
    f.inhibit.setValue(nts::Tristate::Undefined);
    f.clockRise();
    cr_assert_eq(f.logSize(), 0);
}