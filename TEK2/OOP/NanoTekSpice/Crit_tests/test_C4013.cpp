/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4013.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/advanced/C4013.hpp"
#include "components/special/InputComponent.hpp"

struct C4013Fixture {
    nts::C4013          chip;
    nts::InputComponent clk1, data1, reset1, set1;
    nts::InputComponent clk2, data2, reset2, set2;

    C4013Fixture()
    {
        chip.setLink(3,  clk1,   1); clk1.setLink(1,   chip, 3);
        chip.setLink(5,  data1,  1); data1.setLink(1,  chip, 5);
        chip.setLink(4,  reset1, 1); reset1.setLink(1, chip, 4);
        chip.setLink(6,  set1,   1); set1.setLink(1,   chip, 6);
        chip.setLink(11, clk2,   1); clk2.setLink(1,   chip, 11);
        chip.setLink(9,  data2,  1); data2.setLink(1,  chip, 9);
        chip.setLink(10, reset2, 1); reset2.setLink(1, chip, 10);
        chip.setLink(8,  set2,   1); set2.setLink(1,   chip, 8);

        clk1.setValue(nts::Tristate::False);
        data1.setValue(nts::Tristate::False);
        reset1.setValue(nts::Tristate::False);
        set1.setValue(nts::Tristate::False);
        clk2.setValue(nts::Tristate::False);
        data2.setValue(nts::Tristate::False);
        reset2.setValue(nts::Tristate::False);
        set2.setValue(nts::Tristate::False);
    }

    void clockRise1()
    {
        clk1.setValue(nts::Tristate::False);
        chip.simulate(0);
        clk1.setValue(nts::Tristate::True);
        chip.simulate(0);
    }

    void clockRise2()
    {
        clk2.setValue(nts::Tristate::False);
        chip.simulate(0);
        clk2.setValue(nts::Tristate::True);
        chip.simulate(0);
    }
};

Test(c4013_init, q1_undefined_before_simulate)
{
    C4013Fixture f;
    cr_assert_eq(f.chip.compute(1), nts::Tristate::Undefined);
}

Test(c4013_init, q1_not_undefined_before_simulate)
{
    C4013Fixture f;
    cr_assert_eq(f.chip.compute(2), nts::Tristate::Undefined);
}

Test(c4013_init, q2_undefined_before_simulate)
{
    C4013Fixture f;
    cr_assert_eq(f.chip.compute(13), nts::Tristate::Undefined);
}

Test(c4013_init, q2_not_undefined_before_simulate)
{
    C4013Fixture f;
    cr_assert_eq(f.chip.compute(12), nts::Tristate::Undefined);
}

Test(c4013_ff1, captures_true_on_rising_clock)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::True);
    f.clockRise1();
    cr_assert_eq(f.chip.compute(1), nts::Tristate::True);
    cr_assert_eq(f.chip.compute(2), nts::Tristate::False);
}

Test(c4013_ff1, captures_false_on_rising_clock)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::False);
    f.clockRise1();
    cr_assert_eq(f.chip.compute(1), nts::Tristate::False);
    cr_assert_eq(f.chip.compute(2), nts::Tristate::True);
}

Test(c4013_ff1, no_capture_without_rising_edge)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::True);
    f.clk1.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(1), nts::Tristate::Undefined);
}

Test(c4013_ff1, holds_value_after_data_changes)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::True);
    f.clockRise1();
    f.data1.setValue(nts::Tristate::False);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(1), nts::Tristate::True);
}

Test(c4013_ff1, reset_forces_q_to_false)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::True);
    f.clockRise1();
    f.reset1.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(1), nts::Tristate::False);
}

Test(c4013_ff1, set_forces_q_to_true)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::False);
    f.clockRise1();
    f.set1.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(1), nts::Tristate::True);
}

Test(c4013_ff1, set_overrides_reset)
{
    C4013Fixture f;
    f.reset1.setValue(nts::Tristate::True);
    f.set1.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(1), nts::Tristate::True);
}

Test(c4013_ff1, q_and_qnot_are_complementary_true)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::True);
    f.clockRise1();
    cr_assert_eq(f.chip.compute(1), nts::Tristate::True);
    cr_assert_eq(f.chip.compute(2), nts::Tristate::False);
}

Test(c4013_ff1, q_and_qnot_are_complementary_false)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::False);
    f.clockRise1();
    cr_assert_eq(f.chip.compute(1), nts::Tristate::False);
    cr_assert_eq(f.chip.compute(2), nts::Tristate::True);
}

Test(c4013_ff2, captures_true_on_rising_clock)
{
    C4013Fixture f;
    f.data2.setValue(nts::Tristate::True);
    f.clockRise2();
    cr_assert_eq(f.chip.compute(13), nts::Tristate::True);
    cr_assert_eq(f.chip.compute(12), nts::Tristate::False);
}

Test(c4013_ff2, captures_false_on_rising_clock)
{
    C4013Fixture f;
    f.data2.setValue(nts::Tristate::False);
    f.clockRise2();
    cr_assert_eq(f.chip.compute(13), nts::Tristate::False);
    cr_assert_eq(f.chip.compute(12), nts::Tristate::True);
}

Test(c4013_ff2, reset_forces_q_to_false)
{
    C4013Fixture f;
    f.data2.setValue(nts::Tristate::True);
    f.clockRise2();
    f.reset2.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(13), nts::Tristate::False);
}

Test(c4013_ff2, set_forces_q_to_true)
{
    C4013Fixture f;
    f.data2.setValue(nts::Tristate::False);
    f.clockRise2();
    f.set2.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    cr_assert_eq(f.chip.compute(13), nts::Tristate::True);
}

Test(c4013_independence, ff1_and_ff2_independent)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::True);
    f.clockRise1();
    f.data2.setValue(nts::Tristate::False);
    f.clockRise2();
    cr_assert_eq(f.chip.compute(1),  nts::Tristate::True);
    cr_assert_eq(f.chip.compute(13), nts::Tristate::False);
}

Test(c4013_independence, clk1_does_not_affect_ff2)
{
    C4013Fixture f;
    f.data2.setValue(nts::Tristate::True);
    f.clockRise1();
    cr_assert_eq(f.chip.compute(13), nts::Tristate::Undefined);
}

Test(c4013_independence, clk2_does_not_affect_ff1)
{
    C4013Fixture f;
    f.data1.setValue(nts::Tristate::True);
    f.clockRise2();
    cr_assert_eq(f.chip.compute(1), nts::Tristate::Undefined);
}

Test(c4013_pin, unknown_pin_returns_undefined)
{
    C4013Fixture f;
    cr_assert_eq(f.chip.compute(7), nts::Tristate::Undefined);
}