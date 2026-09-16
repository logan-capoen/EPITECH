/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4001.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/gates/C4001.hpp"
#include "components/special/InputComponent.hpp"

static void setup_gate(nts::C4001 &chip,
                        nts::InputComponent &inA,
                        nts::InputComponent &inB,
                        std::size_t pinA,
                        std::size_t pinB,
                        std::size_t pinOut)
{
    inA.setLink(1, chip, pinA);
    chip.setLink(pinA, inA, 1);
    inB.setLink(1, chip, pinB);
    chip.setLink(pinB, inB, 1);
    (void)pinOut;
}

Test(c4001_gate1, nor_false_false_gives_true)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    setup_gate(chip, inA, inB, 1, 2, 3);
    cr_assert_eq(chip.compute(3), nts::Tristate::True);
}

Test(c4001_gate1, nor_true_false_gives_false)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::False);
    setup_gate(chip, inA, inB, 1, 2, 3);
    cr_assert_eq(chip.compute(3), nts::Tristate::False);
}

Test(c4001_gate1, nor_false_true_gives_false)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::True);
    setup_gate(chip, inA, inB, 1, 2, 3);
    cr_assert_eq(chip.compute(3), nts::Tristate::False);
}

Test(c4001_gate1, nor_true_true_gives_false)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::True);
    setup_gate(chip, inA, inB, 1, 2, 3);
    cr_assert_eq(chip.compute(3), nts::Tristate::False);
}

Test(c4001_gate2, nor_false_false_gives_true)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    setup_gate(chip, inA, inB, 5, 6, 4);
    cr_assert_eq(chip.compute(4), nts::Tristate::True);
}

Test(c4001_gate2, nor_true_false_gives_false)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::False);
    setup_gate(chip, inA, inB, 5, 6, 4);
    cr_assert_eq(chip.compute(4), nts::Tristate::False);
}

Test(c4001_gate2, nor_true_true_gives_false)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::True);
    setup_gate(chip, inA, inB, 5, 6, 4);
    cr_assert_eq(chip.compute(4), nts::Tristate::False);
}

Test(c4001_gate3, nor_false_false_gives_true)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    setup_gate(chip, inA, inB, 8, 9, 10);
    cr_assert_eq(chip.compute(10), nts::Tristate::True);
}

Test(c4001_gate3, nor_true_false_gives_false)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::False);
    setup_gate(chip, inA, inB, 8, 9, 10);
    cr_assert_eq(chip.compute(10), nts::Tristate::False);
}

Test(c4001_gate3, nor_true_true_gives_false)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::True);
    setup_gate(chip, inA, inB, 8, 9, 10);
    cr_assert_eq(chip.compute(10), nts::Tristate::False);
}

Test(c4001_gate4, nor_false_false_gives_true)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    setup_gate(chip, inA, inB, 12, 13, 11);
    cr_assert_eq(chip.compute(11), nts::Tristate::True);
}

Test(c4001_gate4, nor_true_false_gives_false)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::False);
    setup_gate(chip, inA, inB, 12, 13, 11);
    cr_assert_eq(chip.compute(11), nts::Tristate::False);
}

Test(c4001_gate4, nor_true_true_gives_false)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::True);
    inB.setValue(nts::Tristate::True);
    setup_gate(chip, inA, inB, 12, 13, 11);
    cr_assert_eq(chip.compute(11), nts::Tristate::False);
}

Test(c4001_cache, compute_twice_same_result)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    setup_gate(chip, inA, inB, 1, 2, 3);
    nts::Tristate first  = chip.compute(3);
    nts::Tristate second = chip.compute(3);
    cr_assert_eq(first, second);
}

Test(c4001_independence, gate1_and_gate2_independent)
{
    nts::C4001 chip;
    nts::InputComponent inA, inB, inC, inD;
    inA.setValue(nts::Tristate::False);
    inB.setValue(nts::Tristate::False);
    inC.setValue(nts::Tristate::True);
    inD.setValue(nts::Tristate::True);

    chip.setLink(1, inA, 1); inA.setLink(1, chip, 1);
    chip.setLink(2, inB, 1); inB.setLink(1, chip, 2);
    chip.setLink(5, inC, 1); inC.setLink(1, chip, 5);
    chip.setLink(6, inD, 1); inD.setLink(1, chip, 6);

    cr_assert_eq(chip.compute(3), nts::Tristate::True);
    cr_assert_eq(chip.compute(4), nts::Tristate::False);
}

Test(c4001_independence, all_four_gates_simultaneously)
{
    nts::C4001 chip;
    nts::InputComponent i1, i2, i3, i4, i5, i6, i7, i8;

    i1.setValue(nts::Tristate::False); chip.setLink(1,  i1, 1); i1.setLink(1, chip, 1);
    i2.setValue(nts::Tristate::False); chip.setLink(2,  i2, 1); i2.setLink(1, chip, 2);
    i3.setValue(nts::Tristate::True);  chip.setLink(5,  i3, 1); i3.setLink(1, chip, 5);
    i4.setValue(nts::Tristate::False); chip.setLink(6,  i4, 1); i4.setLink(1, chip, 6);
    i5.setValue(nts::Tristate::False); chip.setLink(8,  i5, 1); i5.setLink(1, chip, 8);
    i6.setValue(nts::Tristate::False); chip.setLink(9,  i6, 1); i6.setLink(1, chip, 9);
    i7.setValue(nts::Tristate::True);  chip.setLink(12, i7, 1); i7.setLink(1, chip, 12);
    i8.setValue(nts::Tristate::True);  chip.setLink(13, i8, 1); i8.setLink(1, chip, 13);

    cr_assert_eq(chip.compute(3),  nts::Tristate::True);
    cr_assert_eq(chip.compute(4),  nts::Tristate::False);
    cr_assert_eq(chip.compute(10), nts::Tristate::True);
    cr_assert_eq(chip.compute(11), nts::Tristate::False);
}