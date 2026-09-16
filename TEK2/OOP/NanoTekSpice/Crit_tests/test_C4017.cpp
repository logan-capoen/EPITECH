/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4017.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/advanced/C4017.hpp"
#include "components/special/InputComponent.hpp"

static const int COUNT_PINS[10] = {3, 2, 4, 7, 10, 1, 5, 6, 9, 11};

struct C4017Fixture {
    nts::C4017          chip;
    nts::InputComponent cp0;
    nts::InputComponent cp1;
    nts::InputComponent mr;

    C4017Fixture()
    {
        chip.setLink(14, cp0, 1); cp0.setLink(1, chip, 14);
        chip.setLink(13, cp1, 1); cp1.setLink(1, chip, 13);
        chip.setLink(15, mr,  1); mr.setLink(1,  chip, 15);

        cp0.setValue(nts::Tristate::False);
        cp1.setValue(nts::Tristate::False);
        mr.setValue(nts::Tristate::False);
    }

    void clockRise()
    {
        cp0.setValue(nts::Tristate::False);
        chip.simulate(0);
        cp0.setValue(nts::Tristate::True);
        chip.simulate(0);
    }

    void advanceN(int n)
    {
        for (int i = 0; i < n; i++)
            clockRise();
    }

    int activeCount()
    {
        for (int i = 0; i < 10; i++) {
            if (chip.compute(COUNT_PINS[i]) == nts::Tristate::True)
                return i;
        }
        return -1;
    }
};

Test(c4017_init, starts_at_count_zero)
{
    C4017Fixture f;
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(3), nts::Tristate::True);
}

Test(c4017_init, only_pin3_active_at_start)
{
    C4017Fixture f;
    f.chip.simulate(0);
    for (int i = 1; i < 10; i++)
        cr_assert_eq(f.chip.compute(COUNT_PINS[i]), nts::Tristate::False);
}

Test(c4017_count, one_clock_advances_to_count_1)
{
    C4017Fixture f;
    f.clockRise();
    cr_assert_eq(f.chip.compute(2), nts::Tristate::True);
    cr_assert_eq(f.chip.compute(3), nts::Tristate::False);
}

Test(c4017_count, two_clocks_advances_to_count_2)
{
    C4017Fixture f;
    f.advanceN(2);
    cr_assert_eq(f.chip.compute(4), nts::Tristate::True);
}

Test(c4017_count, three_clocks_advances_to_count_3)
{
    C4017Fixture f;
    f.advanceN(3);
    cr_assert_eq(f.chip.compute(7), nts::Tristate::True);
}

Test(c4017_count, four_clocks_advances_to_count_4)
{
    C4017Fixture f;
    f.advanceN(4);
    cr_assert_eq(f.chip.compute(10), nts::Tristate::True);
}

Test(c4017_count, five_clocks_advances_to_count_5)
{
    C4017Fixture f;
    f.advanceN(5);
    cr_assert_eq(f.chip.compute(1), nts::Tristate::True);
}

Test(c4017_count, six_clocks_advances_to_count_6)
{
    C4017Fixture f;
    f.advanceN(6);
    cr_assert_eq(f.chip.compute(5), nts::Tristate::True);
}

Test(c4017_count, seven_clocks_advances_to_count_7)
{
    C4017Fixture f;
    f.advanceN(7);
    cr_assert_eq(f.chip.compute(6), nts::Tristate::True);
}

Test(c4017_count, eight_clocks_advances_to_count_8)
{
    C4017Fixture f;
    f.advanceN(8);
    cr_assert_eq(f.chip.compute(9), nts::Tristate::True);
}

Test(c4017_count, nine_clocks_advances_to_count_9)
{
    C4017Fixture f;
    f.advanceN(9);
    cr_assert_eq(f.chip.compute(11), nts::Tristate::True);
}

Test(c4017_count, ten_clocks_wraps_back_to_count_0)
{
    C4017Fixture f;
    f.advanceN(10);
    cr_assert_eq(f.chip.compute(3), nts::Tristate::True);
}

Test(c4017_count, only_one_output_active_at_a_time)
{
    C4017Fixture f;
    f.advanceN(3);
    int active = 0;
    for (int pin : COUNT_PINS)
        if (f.chip.compute(pin) == nts::Tristate::True)
            active++;
    cr_assert_eq(active, 1);
}

Test(c4017_carry, carry_true_for_counts_0_to_4)
{
    C4017Fixture f;
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(12), nts::Tristate::True);
    f.advanceN(4);
    cr_assert_eq(f.chip.compute(12), nts::Tristate::True);
}

Test(c4017_carry, carry_false_for_counts_5_to_9)
{
    C4017Fixture f;
    f.advanceN(5);
    cr_assert_eq(f.chip.compute(12), nts::Tristate::False);
    f.advanceN(4);
    cr_assert_eq(f.chip.compute(12), nts::Tristate::False);
}

Test(c4017_carry, carry_true_again_after_wrap)
{
    C4017Fixture f;
    f.advanceN(10);
    cr_assert_eq(f.chip.compute(12), nts::Tristate::True);
}

Test(c4017_mr, reset_forces_count_to_zero)
{
    C4017Fixture f;
    f.advanceN(5);
    f.mr.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(3), nts::Tristate::True);
}

Test(c4017_mr, reset_works_at_any_count)
{
    C4017Fixture f;
    f.advanceN(8);
    f.mr.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.activeCount(), 0);
}

Test(c4017_mr, count_resumes_after_reset_released)
{
    C4017Fixture f;
    f.advanceN(3);
    f.mr.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    f.mr.setValue(nts::Tristate::False);
    f.clockRise();
    cr_assert_eq(f.chip.compute(2), nts::Tristate::True);
}

Test(c4017_no_clock, count_unchanged_without_rising_edge)
{
    C4017Fixture f;
    f.chip.simulate(0);
    f.cp0.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(2), nts::Tristate::True);
}