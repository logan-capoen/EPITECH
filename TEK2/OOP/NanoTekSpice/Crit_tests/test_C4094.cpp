/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4094.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/gates/C4094.hpp"
#include "components/special/InputComponent.hpp"

struct C4094Fixture {
    nts::C4094          chip;
    nts::InputComponent strobe;
    nts::InputComponent data;
    nts::InputComponent clock;
    nts::InputComponent oe;

    C4094Fixture()
    {
        chip.setLink(1,  strobe, 1); strobe.setLink(1, chip, 1);
        chip.setLink(2,  data,   1); data.setLink(1,   chip, 2);
        chip.setLink(3,  clock,  1); clock.setLink(1,  chip, 3);
        chip.setLink(15, oe,     1); oe.setLink(1,     chip, 15);

        strobe.setValue(nts::Tristate::False);
        data.setValue(nts::Tristate::False);
        clock.setValue(nts::Tristate::False);
        oe.setValue(nts::Tristate::True);
    }

    void clockRise()
    {
        clock.setValue(nts::Tristate::False);
        chip.simulate(0);
        clock.setValue(nts::Tristate::True);
        chip.simulate(0);
    }

    void clockFall()
    {
        clock.setValue(nts::Tristate::True);
        chip.simulate(0);
        clock.setValue(nts::Tristate::False);
        chip.simulate(0);
    }

    void clockPulse()
    {
        clockRise();
        clockFall();
    }

    void strobePulse()
    {
        strobe.setValue(nts::Tristate::True);
        chip.simulate(0);
        strobe.setValue(nts::Tristate::False);
        chip.simulate(0);
    }
};

Test(c4094_init, outputs_undefined_before_any_clock)
{
    C4094Fixture f;
    cr_assert_eq(f.chip.compute(4),  nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(5),  nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(6),  nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(7),  nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(13), nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(12), nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(11), nts::Tristate::Undefined);
}

Test(c4094_init, qs_undefined_before_any_clock)
{
    C4094Fixture f;
    cr_assert_eq(f.chip.compute(9),  nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(10), nts::Tristate::Undefined);
}

Test(c4094_shift, data_true_shifts_into_pin4_after_one_clock)
{
    C4094Fixture f;
    f.strobe.setValue(nts::Tristate::True);
    f.data.setValue(nts::Tristate::True);
    f.clockRise();
    cr_assert_eq(f.chip.compute(4), nts::Tristate::True);
}

Test(c4094_shift, data_false_shifts_into_pin4_after_one_clock)
{
    C4094Fixture f;
    f.strobe.setValue(nts::Tristate::True);
    f.data.setValue(nts::Tristate::False);
    f.clockRise();
    cr_assert_eq(f.chip.compute(4), nts::Tristate::False);
}

Test(c4094_shift, data_propagates_across_all_8_stages)
{
    C4094Fixture f;
    f.strobe.setValue(nts::Tristate::True);

    f.data.setValue(nts::Tristate::True);
    f.clockRise();
    for (int i = 0; i < 7; i++) {
        f.data.setValue(nts::Tristate::False);
        f.clockRise();
    }
    cr_assert_eq(f.chip.compute(11), nts::Tristate::True);
}

Test(c4094_shift, no_shift_without_rising_edge)
{
    C4094Fixture f;
    f.strobe.setValue(nts::Tristate::True);
    f.data.setValue(nts::Tristate::True);

    f.chip.simulate(0);
    f.chip.simulate(0);

    cr_assert_eq(f.chip.compute(4), nts::Tristate::Undefined);
}

Test(c4094_shift, sequence_true_false_true_in_shift_register)
{
    C4094Fixture f;
    f.strobe.setValue(nts::Tristate::True);

    f.data.setValue(nts::Tristate::True);  f.clockRise();
    f.data.setValue(nts::Tristate::False); f.clockRise();
    f.data.setValue(nts::Tristate::True);  f.clockRise();

    cr_assert_eq(f.chip.compute(4), nts::Tristate::True);
    cr_assert_eq(f.chip.compute(5), nts::Tristate::False);
    cr_assert_eq(f.chip.compute(6), nts::Tristate::True);
}

Test(c4094_qs, qs_updated_on_rising_edge)
{
    C4094Fixture f;

    f.data.setValue(nts::Tristate::True);
    for (int i = 0; i < 8; i++)
        f.clockRise();

    cr_assert_eq(f.chip.compute(9), nts::Tristate::True);
}

Test(c4094_qs_prime, qs_prime_updated_on_falling_edge)
{
    C4094Fixture f;

    f.data.setValue(nts::Tristate::True);
    for (int i = 0; i < 8; i++)
        f.clockRise();

    f.clockFall();
    cr_assert_eq(f.chip.compute(10), nts::Tristate::True);
}

Test(c4094_qs, qs_false_when_register_empty)
{
    C4094Fixture f;

    f.data.setValue(nts::Tristate::False);
    for (int i = 0; i < 8; i++)
        f.clockRise();

    cr_assert_eq(f.chip.compute(9), nts::Tristate::False);
}

Test(c4094_latch, latch_captures_shift_register_on_strobe_falling)
{
    C4094Fixture f;

    f.strobe.setValue(nts::Tristate::False);
    f.data.setValue(nts::Tristate::True);
    f.clockRise();

    f.strobePulse();

    cr_assert_eq(f.chip.compute(4), nts::Tristate::True);
}

Test(c4094_latch, latch_holds_value_after_new_shift)
{
    C4094Fixture f;

    f.strobe.setValue(nts::Tristate::False);
    f.data.setValue(nts::Tristate::True);
    f.clockRise();
    f.strobePulse();

    f.data.setValue(nts::Tristate::False);
    f.clockRise();

    cr_assert_eq(f.chip.compute(4), nts::Tristate::True);
}

Test(c4094_latch, strobe_true_shows_shift_register_directly)
{
    C4094Fixture f;

    f.strobe.setValue(nts::Tristate::False);
    f.data.setValue(nts::Tristate::False);
    f.clockRise();
    f.strobePulse();

    f.strobe.setValue(nts::Tristate::True);
    f.data.setValue(nts::Tristate::True);
    f.clockRise();

    cr_assert_eq(f.chip.compute(4), nts::Tristate::True);
}

Test(c4094_oe, outputs_undefined_when_oe_false)
{
    C4094Fixture f;
    f.oe.setValue(nts::Tristate::False);
    f.strobe.setValue(nts::Tristate::True);
    f.data.setValue(nts::Tristate::True);
    f.clockRise();

    cr_assert_eq(f.chip.compute(4),  nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(11), nts::Tristate::Undefined);
}

Test(c4094_oe, outputs_undefined_when_oe_undefined)
{
    C4094Fixture f;
    f.oe.setValue(nts::Tristate::Undefined);
    f.strobe.setValue(nts::Tristate::True);
    f.data.setValue(nts::Tristate::True);
    f.clockRise();

    cr_assert_eq(f.chip.compute(4), nts::Tristate::Undefined);
}

Test(c4094_oe, qs_unaffected_by_oe)
{
    C4094Fixture f;
    f.oe.setValue(nts::Tristate::False);
    f.data.setValue(nts::Tristate::True);
    for (int i = 0; i < 8; i++)
        f.clockRise();

    cr_assert_eq(f.chip.compute(9),  nts::Tristate::True);
}

Test(c4094_oe, outputs_valid_when_oe_true)
{
    C4094Fixture f;
    f.oe.setValue(nts::Tristate::True);
    f.strobe.setValue(nts::Tristate::True);
    f.data.setValue(nts::Tristate::True);
    f.clockRise();

    cr_assert_eq(f.chip.compute(4), nts::Tristate::True);
}