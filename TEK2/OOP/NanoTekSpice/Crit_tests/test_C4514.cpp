/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4514.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/advanced/C4514.hpp"
#include "components/special/InputComponent.hpp"

static const int OUTPUT_PINS[16] = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 15, 16};

struct C4514Fixture {
    nts::C4514          chip;
    nts::InputComponent strobe;
    nts::InputComponent a, b, c, d;
    nts::InputComponent inh;

    C4514Fixture()
    {
        chip.setLink(1,  strobe, 1); strobe.setLink(1, chip, 1);
        chip.setLink(2,  a,      1); a.setLink(1,      chip, 2);
        chip.setLink(3,  b,      1); b.setLink(1,      chip, 3);
        chip.setLink(21, c,      1); c.setLink(1,      chip, 21);
        chip.setLink(22, d,      1); d.setLink(1,      chip, 22);
        chip.setLink(23, inh,    1); inh.setLink(1,    chip, 23);

        strobe.setValue(nts::Tristate::False);
        a.setValue(nts::Tristate::False);
        b.setValue(nts::Tristate::False);
        c.setValue(nts::Tristate::False);
        d.setValue(nts::Tristate::False);
        inh.setValue(nts::Tristate::False);
    }

    void setAddress(int val)
    {
        a.setValue((val & 1) ? nts::Tristate::True : nts::Tristate::False);
        b.setValue((val & 2) ? nts::Tristate::True : nts::Tristate::False);
        c.setValue((val & 4) ? nts::Tristate::True : nts::Tristate::False);
        d.setValue((val & 8) ? nts::Tristate::True : nts::Tristate::False);
    }

    void strobePulse()
    {
        strobe.setValue(nts::Tristate::True);
        chip.simulate(0);
        strobe.setValue(nts::Tristate::False);
        chip.simulate(0);
        strobe.setValue(nts::Tristate::True);
        chip.simulate(0);
    }

    int activeOutput()
    {
        for (int i = 0; i < 16; i++)
            if (chip.compute(OUTPUT_PINS[i]) == nts::Tristate::True)
                return i;
        return -1;
    }
};

Test(c4514_init, all_outputs_undefined_before_strobe)
{
    C4514Fixture f;
    f.strobe.setValue(nts::Tristate::True);
    f.chip.simulate(0);
    for (int pin : OUTPUT_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::Undefined);
}

Test(c4514_decode, address_0_activates_pin11)
{
    C4514Fixture f;
    f.setAddress(0);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(11), nts::Tristate::True);
}

Test(c4514_decode, address_1_activates_pin9)
{
    C4514Fixture f;
    f.setAddress(1);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(9), nts::Tristate::True);
}

Test(c4514_decode, address_2_activates_pin10)
{
    C4514Fixture f;
    f.setAddress(2);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(10), nts::Tristate::True);
}

Test(c4514_decode, address_3_activates_pin8)
{
    C4514Fixture f;
    f.setAddress(3);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(8), nts::Tristate::True);
}

Test(c4514_decode, address_4_activates_pin7)
{
    C4514Fixture f;
    f.setAddress(4);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(7), nts::Tristate::True);
}

Test(c4514_decode, address_5_activates_pin6)
{
    C4514Fixture f;
    f.setAddress(5);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(6), nts::Tristate::True);
}

Test(c4514_decode, address_6_activates_pin5)
{
    C4514Fixture f;
    f.setAddress(6);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(5), nts::Tristate::True);
}

Test(c4514_decode, address_8_activates_pin18)
{
    C4514Fixture f;
    f.setAddress(8);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(18), nts::Tristate::True);
}

Test(c4514_decode, address_15_activates_pin16)
{
    C4514Fixture f;
    f.setAddress(15);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(16), nts::Tristate::True);
}

Test(c4514_decode, address_10_activates_pin20)
{
    C4514Fixture f;
    f.setAddress(10);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(20), nts::Tristate::True);
}

Test(c4514_decode, address_11_activates_pin19)
{
    C4514Fixture f;
    f.setAddress(11);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(19), nts::Tristate::True);
}

Test(c4514_decode, address_12_activates_pin14)
{
    C4514Fixture f;
    f.setAddress(12);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4514_decode, address_13_activates_pin13)
{
    C4514Fixture f;
    f.setAddress(13);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(13), nts::Tristate::True);
}

Test(c4514_decode, address_14_activates_pin15)
{
    C4514Fixture f;
    f.setAddress(14);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(15), nts::Tristate::True);
}

Test(c4514_decode, only_one_output_active_at_a_time)
{
    C4514Fixture f;
    f.setAddress(5);
    f.strobePulse();
    int active = 0;
    for (int pin : OUTPUT_PINS)
        if (f.chip.compute(pin) == nts::Tristate::True)
            active++;
    cr_assert_eq(active, 1);
}

Test(c4514_latch, captures_address_on_strobe_falling_edge)
{
    C4514Fixture f;
    f.setAddress(3);
    f.strobePulse();
    cr_assert_eq(f.activeOutput(), 3);
}

Test(c4514_latch, holds_value_after_address_changes)
{
    C4514Fixture f;
    f.setAddress(5);
    f.strobePulse();
    f.setAddress(0);
    f.chip.simulate(0);
    cr_assert_eq(f.activeOutput(), 5);
}

Test(c4514_latch, updates_on_new_strobe_pulse)
{
    C4514Fixture f;
    f.setAddress(3);
    f.strobePulse();
    f.setAddress(7);
    f.strobePulse();
    cr_assert_eq(f.activeOutput(), 7);
}

Test(c4514_strobe, outputs_false_when_strobe_false)
{
    C4514Fixture f;
    f.setAddress(0);
    f.strobePulse();
    f.strobe.setValue(nts::Tristate::False);
    f.chip.simulate(0);
    for (int pin : OUTPUT_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::False);
}

Test(c4514_inh, inhibit_true_forces_all_outputs_false)
{
    C4514Fixture f;
    f.setAddress(0);
    f.strobePulse();
    f.inh.setValue(nts::Tristate::True);
    for (int pin : OUTPUT_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::False);
}

Test(c4514_inh, inhibit_undefined_returns_undefined)
{
    C4514Fixture f;
    f.setAddress(0);
    f.strobePulse();
    f.inh.setValue(nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(11), nts::Tristate::Undefined);
}

Test(c4514_inh, inhibit_false_allows_output)
{
    C4514Fixture f;
    f.setAddress(0);
    f.strobePulse();
    f.inh.setValue(nts::Tristate::False);
    cr_assert_eq(f.chip.compute(11), nts::Tristate::True);
}

Test(c4514_undefined, undefined_inputs_return_undefined)
{
    C4514Fixture f;
    f.a.setValue(nts::Tristate::Undefined);
    f.strobePulse();
    cr_assert_eq(f.chip.compute(11), nts::Tristate::Undefined);
}

Test(c4514_strobe, strobe_false_returns_false)
{
    C4514Fixture f;
    f.setAddress(0);
    f.strobePulse();
    f.strobe.setValue(nts::Tristate::False);
    f.chip.simulate(0);
    for (int pin : OUTPUT_PINS)
        cr_assert_eq(f.chip.compute(pin), nts::Tristate::False);
}