/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4040.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/advanced/C4040.hpp"
#include "components/special/InputComponent.hpp"

static const int BIT_PINS[12] = {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1};

struct C4040Fixture {
    nts::C4040          chip;
    nts::InputComponent clock;
    nts::InputComponent reset;

    C4040Fixture()
    {
        chip.setLink(10, clock, 1); clock.setLink(1, chip, 10);
        chip.setLink(11, reset, 1); reset.setLink(1, chip, 11);

        clock.setValue(nts::Tristate::False);
        reset.setValue(nts::Tristate::False);
    }

    void clockFall()
    {
        clock.setValue(nts::Tristate::True);
        chip.simulate(0);
        clock.setValue(nts::Tristate::False);
        chip.simulate(0);
    }

    void advanceN(int n)
    {
        for (int i = 0; i < n; i++)
            clockFall();
    }

    int readCount()
    {
        int value = 0;
        for (int i = 0; i < 12; i++)
            if (chip.compute(BIT_PINS[i]) == nts::Tristate::True)
                value |= (1 << i);
        return value;
    }
};

Test(c4040_init, all_outputs_false_at_start)
{
    C4040Fixture f;
    f.chip.simulate(0);
    for (int pin : BIT_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::False);
}

Test(c4040_init, count_is_zero_at_start)
{
    C4040Fixture f;
    f.chip.simulate(0);
    cr_assert_eq(f.readCount(), 0);
}

Test(c4040_count, one_falling_edge_gives_count_1)
{
    C4040Fixture f;
    f.clockFall();
    cr_assert_eq(f.readCount(), 1);
}

Test(c4040_count, two_falling_edges_gives_count_2)
{
    C4040Fixture f;
    f.advanceN(2);
    cr_assert_eq(f.readCount(), 2);
}

Test(c4040_count, three_falling_edges_gives_count_3)
{
    C4040Fixture f;
    f.advanceN(3);
    cr_assert_eq(f.readCount(), 3);
}

Test(c4040_count, four_falling_edges_gives_count_4)
{
    C4040Fixture f;
    f.advanceN(4);
    cr_assert_eq(f.readCount(), 4);
}

Test(c4040_count, eight_falling_edges_gives_count_8)
{
    C4040Fixture f;
    f.advanceN(8);
    cr_assert_eq(f.readCount(), 8);
}

Test(c4040_count, sixteen_falling_edges_gives_count_16)
{
    C4040Fixture f;
    f.advanceN(16);
    cr_assert_eq(f.readCount(), 16);
}

Test(c4040_count, count_255)
{
    C4040Fixture f;
    f.advanceN(255);
    cr_assert_eq(f.readCount(), 255);
}

Test(c4040_count, count_1000)
{
    C4040Fixture f;
    f.advanceN(1000);
    cr_assert_eq(f.readCount(), 1000);
}

Test(c4040_count, count_max_4095)
{
    C4040Fixture f;
    f.advanceN(4095);
    cr_assert_eq(f.readCount(), 4095);
}

Test(c4040_count, no_increment_on_rising_edge)
{
    C4040Fixture f;
    f.clock.setValue(nts::Tristate::False);
    f.chip.simulate(0);
    f.clock.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.readCount(), 0);
}

Test(c4040_count, no_increment_without_clock_change)
{
    C4040Fixture f;
    f.clock.setValue(nts::Tristate::False);
    f.chip.simulate(0);
    f.chip.simulate(0);
    f.chip.simulate(0);
    cr_assert_eq(f.readCount(), 0);
}

Test(c4040_bits, bit0_toggles_every_clock)
{
    C4040Fixture f;
    f.clockFall();
    cr_assert_eq(f.chip.compute(9), nts::Tristate::True);
    f.clockFall();
    cr_assert_eq(f.chip.compute(9), nts::Tristate::False);
    f.clockFall();
    cr_assert_eq(f.chip.compute(9), nts::Tristate::True);
}

Test(c4040_bits, bit1_toggles_every_two_clocks)
{
    C4040Fixture f;
    f.advanceN(2);
    cr_assert_eq(f.chip.compute(7), nts::Tristate::True);
    f.advanceN(2);
    cr_assert_eq(f.chip.compute(7), nts::Tristate::False);
}

Test(c4040_bits, bit11_set_at_count_2048)
{
    C4040Fixture f;
    f.advanceN(2048);
    cr_assert_eq(f.chip.compute(1), nts::Tristate::True);
}

Test(c4040_reset, reset_forces_count_to_zero)
{
    C4040Fixture f;
    f.advanceN(42);
    f.reset.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.readCount(), 0);
}

Test(c4040_reset, reset_works_at_max_count)
{
    C4040Fixture f;
    f.advanceN(4095);
    f.reset.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.readCount(), 0);
}

Test(c4040_reset, count_resumes_after_reset_released)
{
    C4040Fixture f;
    f.advanceN(10);
    f.reset.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    f.reset.setValue(nts::Tristate::False);
    f.clockFall();
    cr_assert_eq(f.readCount(), 1);
}

Test(c4040_reset, reset_has_priority_over_clock)
{
    C4040Fixture f;
    f.advanceN(5);
    f.reset.setValue(nts::Tristate::True);
    f.clockFall();
    cr_assert_eq(f.readCount(), 0);
}