/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4069.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/gates/C4069.hpp"
#include "components/special/InputComponent.hpp"

static void link_input(nts::C4069 &chip, nts::InputComponent &in, std::size_t pinIn)
{
    chip.setLink(pinIn, in, 1);
    in.setLink(1, chip, pinIn);
}

Test(c4069_gate1, not_false_gives_true)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::False);
    link_input(chip, in, 1);
    cr_assert_eq(chip.compute(2), nts::Tristate::True);
}

Test(c4069_gate1, not_true_gives_false)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::True);
    link_input(chip, in, 1);
    cr_assert_eq(chip.compute(2), nts::Tristate::False);
}

Test(c4069_gate1, not_undefined_gives_undefined)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::Undefined);
    link_input(chip, in, 1);
    cr_assert_eq(chip.compute(2), nts::Tristate::Undefined);
}

Test(c4069_gate2, not_false_gives_true)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::False);
    link_input(chip, in, 3);
    cr_assert_eq(chip.compute(4), nts::Tristate::True);
}

Test(c4069_gate2, not_true_gives_false)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::True);
    link_input(chip, in, 3);
    cr_assert_eq(chip.compute(4), nts::Tristate::False);
}

Test(c4069_gate2, not_undefined_gives_undefined)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::Undefined);
    link_input(chip, in, 3);
    cr_assert_eq(chip.compute(4), nts::Tristate::Undefined);
}

Test(c4069_gate3, not_false_gives_true)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::False);
    link_input(chip, in, 5);
    cr_assert_eq(chip.compute(6), nts::Tristate::True);
}

Test(c4069_gate3, not_true_gives_false)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::True);
    link_input(chip, in, 5);
    cr_assert_eq(chip.compute(6), nts::Tristate::False);
}

Test(c4069_gate3, not_undefined_gives_undefined)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::Undefined);
    link_input(chip, in, 5);
    cr_assert_eq(chip.compute(6), nts::Tristate::Undefined);
}

Test(c4069_gate4, not_false_gives_true)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::False);
    link_input(chip, in, 9);
    cr_assert_eq(chip.compute(8), nts::Tristate::True);
}

Test(c4069_gate4, not_true_gives_false)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::True);
    link_input(chip, in, 9);
    cr_assert_eq(chip.compute(8), nts::Tristate::False);
}

Test(c4069_gate4, not_undefined_gives_undefined)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::Undefined);
    link_input(chip, in, 9);
    cr_assert_eq(chip.compute(8), nts::Tristate::Undefined);
}

Test(c4069_gate5, not_false_gives_true)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::False);
    link_input(chip, in, 11);
    cr_assert_eq(chip.compute(10), nts::Tristate::True);
}

Test(c4069_gate5, not_true_gives_false)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::True);
    link_input(chip, in, 11);
    cr_assert_eq(chip.compute(10), nts::Tristate::False);
}

Test(c4069_gate5, not_undefined_gives_undefined)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::Undefined);
    link_input(chip, in, 11);
    cr_assert_eq(chip.compute(10), nts::Tristate::Undefined);
}

Test(c4069_gate6, not_false_gives_true)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::False);
    link_input(chip, in, 13);
    cr_assert_eq(chip.compute(12), nts::Tristate::True);
}

Test(c4069_gate6, not_true_gives_false)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::True);
    link_input(chip, in, 13);
    cr_assert_eq(chip.compute(12), nts::Tristate::False);
}

Test(c4069_gate6, not_undefined_gives_undefined)
{
    nts::C4069 chip; nts::InputComponent in;
    in.setValue(nts::Tristate::Undefined);
    link_input(chip, in, 13);
    cr_assert_eq(chip.compute(12), nts::Tristate::Undefined);
}

Test(c4069_independence, all_six_gates_simultaneously)
{
    nts::C4069 chip;
    nts::InputComponent i1, i2, i3, i4, i5, i6;
    i1.setValue(nts::Tristate::False); link_input(chip, i1, 1);
    i2.setValue(nts::Tristate::True);  link_input(chip, i2, 3);
    i3.setValue(nts::Tristate::False); link_input(chip, i3, 5);
    i4.setValue(nts::Tristate::True);  link_input(chip, i4, 9);
    i5.setValue(nts::Tristate::False); link_input(chip, i5, 11);
    i6.setValue(nts::Tristate::True);  link_input(chip, i6, 13);
    cr_assert_eq(chip.compute(2),  nts::Tristate::True);
    cr_assert_eq(chip.compute(4),  nts::Tristate::False);
    cr_assert_eq(chip.compute(6),  nts::Tristate::True);
    cr_assert_eq(chip.compute(8),  nts::Tristate::False);
    cr_assert_eq(chip.compute(10), nts::Tristate::True);
    cr_assert_eq(chip.compute(12), nts::Tristate::False);
}

Test(c4069_independence, gates_do_not_interfere)
{
    nts::C4069 chip;
    nts::InputComponent i1, i2;
    i1.setValue(nts::Tristate::True);  link_input(chip, i1, 1);
    i2.setValue(nts::Tristate::False); link_input(chip, i2, 3);
    cr_assert_eq(chip.compute(2), nts::Tristate::False);
    cr_assert_eq(chip.compute(4), nts::Tristate::True);
}

Test(c4069_extra, unlinked_pin_gives_undefined)
{
    nts::C4069 chip;
    cr_assert_eq(chip.compute(2), nts::Tristate::Undefined);
}