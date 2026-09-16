/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4008.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/advanced/C4008.hpp"
#include "components/special/InputComponent.hpp"

struct C4008Fixture {
    nts::C4008          chip;
    nts::InputComponent a0, a1, a2, a3;
    nts::InputComponent b0, b1, b2, b3;
    nts::InputComponent cin;

    C4008Fixture()
    {
        chip.setLink(1,  a0,  1); a0.setLink(1,  chip, 1);
        chip.setLink(3,  a1,  1); a1.setLink(1,  chip, 3);
        chip.setLink(9,  a2,  1); a2.setLink(1,  chip, 9);
        chip.setLink(11, a3,  1); a3.setLink(1,  chip, 11);
        chip.setLink(2,  b0,  1); b0.setLink(1,  chip, 2);
        chip.setLink(4,  b1,  1); b1.setLink(1,  chip, 4);
        chip.setLink(10, b2,  1); b2.setLink(1,  chip, 10);
        chip.setLink(12, b3,  1); b3.setLink(1,  chip, 12);
        chip.setLink(7,  cin, 1); cin.setLink(1, chip, 7);

        a0.setValue(nts::Tristate::False);
        a1.setValue(nts::Tristate::False);
        a2.setValue(nts::Tristate::False);
        a3.setValue(nts::Tristate::False);
        b0.setValue(nts::Tristate::False);
        b1.setValue(nts::Tristate::False);
        b2.setValue(nts::Tristate::False);
        b3.setValue(nts::Tristate::False);
        cin.setValue(nts::Tristate::False);
    }

    void setA(int val)
    {
        a0.setValue((val & 1) ? nts::Tristate::True : nts::Tristate::False);
        a1.setValue((val & 2) ? nts::Tristate::True : nts::Tristate::False);
        a2.setValue((val & 4) ? nts::Tristate::True : nts::Tristate::False);
        a3.setValue((val & 8) ? nts::Tristate::True : nts::Tristate::False);
    }

    void setB(int val)
    {
        b0.setValue((val & 1) ? nts::Tristate::True : nts::Tristate::False);
        b1.setValue((val & 2) ? nts::Tristate::True : nts::Tristate::False);
        b2.setValue((val & 4) ? nts::Tristate::True : nts::Tristate::False);
        b3.setValue((val & 8) ? nts::Tristate::True : nts::Tristate::False);
    }

    int readResult()
    {
        int result = 0;
        if (chip.compute(10) == nts::Tristate::True) result |= 1;
        if (chip.compute(11) == nts::Tristate::True) result |= 2;
        if (chip.compute(12) == nts::Tristate::True) result |= 4;
        if (chip.compute(13) == nts::Tristate::True) result |= 8;
        if (chip.compute(14) == nts::Tristate::True) result |= 16;
        return result;
    }
};

Test(c4008_basic, zero_plus_zero_equals_zero)
{
    C4008Fixture s;
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 0);
}

Test(c4008_basic, one_plus_zero_equals_one)
{
    C4008Fixture s;
    s.setA(1);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 1);
}

Test(c4008_basic, zero_plus_one_equals_one)
{
    C4008Fixture s;
    s.setB(1);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 1);
}

Test(c4008_basic, one_plus_one_equals_two)
{
    C4008Fixture s;
    s.setA(1);
    s.setB(1);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 2);
}

Test(c4008_basic, two_plus_two_equals_four)
{
    C4008Fixture s;
    s.setA(2);
    s.setB(2);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 4);
}

Test(c4008_basic, seven_plus_eight_equals_fifteen)
{
    C4008Fixture s;
    s.setA(7);
    s.setB(8);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 15);
}

Test(c4008_carry_in, zero_plus_zero_plus_cin_equals_one)
{
    C4008Fixture s;
    s.cin.setValue(nts::Tristate::True);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 1);
}

Test(c4008_carry_in, one_plus_one_plus_cin_equals_three)
{
    C4008Fixture s;
    s.setA(1);
    s.setB(1);
    s.cin.setValue(nts::Tristate::True);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 3);
}

Test(c4008_carry_in, seven_plus_seven_plus_cin_equals_fifteen)
{
    C4008Fixture s;
    s.setA(7);
    s.setB(7);
    s.cin.setValue(nts::Tristate::True);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 15);
}

Test(c4008_carry_out, fifteen_plus_one_produces_carry)
{
    C4008Fixture s;
    s.setA(15);
    s.setB(1);
    s.chip.simulate(0);
    cr_assert_eq(s.chip.compute(14), nts::Tristate::True);
}

Test(c4008_carry_out, fifteen_plus_fifteen_produces_carry)
{
    C4008Fixture s;
    s.setA(15);
    s.setB(15);
    s.chip.simulate(0);
    cr_assert_eq(s.chip.compute(14), nts::Tristate::True);
    cr_assert_eq(s.readResult(), 30);
}

Test(c4008_carry_out, fifteen_plus_fifteen_plus_cin)
{
    C4008Fixture s;
    s.setA(15);
    s.setB(15);
    s.cin.setValue(nts::Tristate::True);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 31);
}

Test(c4008_carry_out, no_carry_when_sum_below_16)
{
    C4008Fixture s;
    s.setA(7);
    s.setB(7);
    s.chip.simulate(0);
    cr_assert_eq(s.chip.compute(14), nts::Tristate::False);
}

Test(c4008_simulate, result_zero_before_simulate)
{
    C4008Fixture s;
    s.setA(5);
    s.setB(5);
    cr_assert_eq(s.readResult(), 0);
}

Test(c4008_simulate, result_updates_after_each_simulate)
{
    C4008Fixture s;
    s.setA(3);
    s.setB(3);
    s.chip.simulate(0);
    cr_assert_eq(s.readResult(), 6);

    s.setA(1);
    s.setB(1);
    s.chip.simulate(1);
    cr_assert_eq(s.readResult(), 2);
}