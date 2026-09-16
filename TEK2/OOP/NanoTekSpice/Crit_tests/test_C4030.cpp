/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4030.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/gates/C4030.hpp"
#include "components/special/InputComponent.hpp"

static void link_inputs(nts::C4030 &chip,
                         nts::InputComponent &inA,
                         nts::InputComponent &inB,
                         std::size_t pinA,
                         std::size_t pinB)
{
    chip.setLink(pinA, inA, 1); inA.setLink(1, chip, pinA);
    chip.setLink(pinB, inB, 1); inB.setLink(1, chip, pinB);
}

Test(c4030_gate1, xor_false_false_gives_false)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    link_inputs(chip, inA, inB, 1, 2);
    cr_assert_eq(chip.compute(3), nts::Tristate::False);
}

Test(c4030_gate1, xor_true_false_gives_true)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::False);
    link_inputs(chip, inA, inB, 1, 2);
    cr_assert_eq(chip.compute(3), nts::Tristate::True);
}

Test(c4030_gate1, xor_false_true_gives_true)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::True);
    link_inputs(chip, inA, inB, 1, 2);
    cr_assert_eq(chip.compute(3), nts::Tristate::True);
}

Test(c4030_gate1, xor_true_true_gives_false)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::True);
    link_inputs(chip, inA, inB, 1, 2);
    cr_assert_eq(chip.compute(3), nts::Tristate::False);
}

Test(c4030_gate2, xor_false_false_gives_false)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    link_inputs(chip, inA, inB, 5, 6);
    cr_assert_eq(chip.compute(4), nts::Tristate::False);
}

Test(c4030_gate2, xor_true_false_gives_true)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::False);
    link_inputs(chip, inA, inB, 5, 6);
    cr_assert_eq(chip.compute(4), nts::Tristate::True);
}

Test(c4030_gate2, xor_true_true_gives_false)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::True);
    link_inputs(chip, inA, inB, 5, 6);
    cr_assert_eq(chip.compute(4), nts::Tristate::False);
}

Test(c4030_gate3, xor_false_false_gives_false)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    link_inputs(chip, inA, inB, 8, 9);
    cr_assert_eq(chip.compute(10), nts::Tristate::False);
}

Test(c4030_gate3, xor_true_false_gives_true)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::False);
    link_inputs(chip, inA, inB, 8, 9);
    cr_assert_eq(chip.compute(10), nts::Tristate::True);
}

Test(c4030_gate3, xor_true_true_gives_false)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::True);
    link_inputs(chip, inA, inB, 8, 9);
    cr_assert_eq(chip.compute(10), nts::Tristate::False);
}

Test(c4030_gate4, xor_false_false_gives_false)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    link_inputs(chip, inA, inB, 12, 13);
    cr_assert_eq(chip.compute(11), nts::Tristate::False);
}

Test(c4030_gate4, xor_true_false_gives_true)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::False);
    link_inputs(chip, inA, inB, 12, 13);
    cr_assert_eq(chip.compute(11), nts::Tristate::True);
}

Test(c4030_gate4, xor_true_true_gives_false)
{
    nts::C4030 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::True);
    link_inputs(chip, inA, inB, 12, 13);
    cr_assert_eq(chip.compute(11), nts::Tristate::False);
}

Test(c4030_independence, gate1_and_gate2_independent)
{
    nts::C4030 chip;
    nts::InputComponent i1, i2, i3, i4;

    i1.setValue(nts::Tristate::True);
    i2.setValue(nts::Tristate::False);
    chip.setLink(1, i1, 1); i1.setLink(1, chip, 1);
    chip.setLink(2, i2, 1); i2.setLink(1, chip, 2);

    i3.setValue(nts::Tristate::True);
    i4.setValue(nts::Tristate::True);
    chip.setLink(5, i3, 1); i3.setLink(1, chip, 5);
    chip.setLink(6, i4, 1); i4.setLink(1, chip, 6);

    cr_assert_eq(chip.compute(3), nts::Tristate::True);
    cr_assert_eq(chip.compute(4), nts::Tristate::False);
}

Test(c4030_independence, all_four_gates_simultaneously)
{
    nts::C4030 chip;
    nts::InputComponent i1, i2, i3, i4, i5, i6, i7, i8;

    i1.setValue(nts::Tristate::False); chip.setLink(1,  i1, 1); i1.setLink(1, chip, 1);
    i2.setValue(nts::Tristate::False); chip.setLink(2,  i2, 1); i2.setLink(1, chip, 2);
    i3.setValue(nts::Tristate::True);  chip.setLink(5,  i3, 1); i3.setLink(1, chip, 5);
    i4.setValue(nts::Tristate::False); chip.setLink(6,  i4, 1); i4.setLink(1, chip, 6);
    i5.setValue(nts::Tristate::True);  chip.setLink(8,  i5, 1); i5.setLink(1, chip, 8);
    i6.setValue(nts::Tristate::True);  chip.setLink(9,  i6, 1); i6.setLink(1, chip, 9);
    i7.setValue(nts::Tristate::False); chip.setLink(12, i7, 1); i7.setLink(1, chip, 12);
    i8.setValue(nts::Tristate::True);  chip.setLink(13, i8, 1); i8.setLink(1, chip, 13);

    cr_assert_eq(chip.compute(3),  nts::Tristate::False);
    cr_assert_eq(chip.compute(4),  nts::Tristate::True);
    cr_assert_eq(chip.compute(10), nts::Tristate::False);
    cr_assert_eq(chip.compute(11), nts::Tristate::True);
}