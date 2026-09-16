/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_C4512.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/advanced/C4512.hpp"
#include "components/special/InputComponent.hpp"

struct C4512Fixture {
    nts::C4512          chip;
    nts::InputComponent in[8];
    nts::InputComponent a0, a1, a2;
    nts::InputComponent inh;
    nts::InputComponent oe;

    C4512Fixture()
    {
        int data_pins[8] = {1, 2, 3, 4, 5, 6, 7, 9};
        for (int i = 0; i < 8; i++) {
            chip.setLink(data_pins[i], in[i], 1);
            in[i].setLink(1, chip, data_pins[i]);
            in[i].setValue(nts::Tristate::False);
        }
        chip.setLink(11, a0,  1); a0.setLink(1,  chip, 11);
        chip.setLink(12, a1,  1); a1.setLink(1,  chip, 12);
        chip.setLink(13, a2,  1); a2.setLink(1,  chip, 13);
        chip.setLink(10, inh, 1); inh.setLink(1, chip, 10);
        chip.setLink(15, oe,  1); oe.setLink(1,  chip, 15);

        a0.setValue(nts::Tristate::False);
        a1.setValue(nts::Tristate::False);
        a2.setValue(nts::Tristate::False);
        inh.setValue(nts::Tristate::False);
        oe.setValue(nts::Tristate::False);
    }

    void setAddress(int addr)
    {
        a0.setValue((addr & 1) ? nts::Tristate::True : nts::Tristate::False);
        a1.setValue((addr & 2) ? nts::Tristate::True : nts::Tristate::False);
        a2.setValue((addr & 4) ? nts::Tristate::True : nts::Tristate::False);
    }
};

Test(c4512_select, address_0_reads_pin1)
{
    C4512Fixture f;
    f.setAddress(0);
    f.in[0].setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4512_select, address_0_reads_pin1_false)
{
    C4512Fixture f;
    f.setAddress(0);
    f.in[0].setValue(nts::Tristate::False);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::False);
}

Test(c4512_select, address_1_reads_pin2)
{
    C4512Fixture f;
    f.setAddress(1);
    f.in[1].setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4512_select, address_2_reads_pin3)
{
    C4512Fixture f;
    f.setAddress(2);
    f.in[2].setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4512_select, address_3_reads_pin4)
{
    C4512Fixture f;
    f.setAddress(3);
    f.in[3].setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4512_select, address_4_reads_pin5)
{
    C4512Fixture f;
    f.setAddress(4);
    f.in[4].setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4512_select, address_5_reads_pin6)
{
    C4512Fixture f;
    f.setAddress(5);
    f.in[5].setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4512_select, address_6_reads_pin7)
{
    C4512Fixture f;
    f.setAddress(6);
    f.in[6].setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4512_select, unselected_inputs_do_not_affect_output)
{
    C4512Fixture f;
    f.setAddress(0);
    f.in[0].setValue(nts::Tristate::False);
    for (int i = 1; i < 7; i++)
        f.in[i].setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::False);
}

Test(c4512_inh, inhibit_true_returns_false)
{
    C4512Fixture f;
    f.setAddress(0);
    f.in[0].setValue(nts::Tristate::True);
    f.inh.setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::False);
}

Test(c4512_inh, inhibit_false_allows_output)
{
    C4512Fixture f;
    f.setAddress(0);
    f.in[0].setValue(nts::Tristate::True);
    f.inh.setValue(nts::Tristate::False);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4512_inh, inhibit_overrides_any_address)
{
    C4512Fixture f;
    f.inh.setValue(nts::Tristate::True);
    for (int addr = 0; addr < 6; addr++) {
        f.setAddress(addr);
        f.in[addr].setValue(nts::Tristate::True);
        cr_assert_eq(f.chip.compute(14), nts::Tristate::False);
    }
}

Test(c4512_oe, oe_true_returns_undefined)
{
    C4512Fixture f;
    f.setAddress(0);
    f.in[0].setValue(nts::Tristate::True);
    f.oe.setValue(nts::Tristate::True);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::Undefined);
}

Test(c4512_oe, oe_false_allows_output)
{
    C4512Fixture f;
    f.setAddress(0);
    f.in[0].setValue(nts::Tristate::True);
    f.oe.setValue(nts::Tristate::False);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::True);
}

Test(c4512_addr, undefined_a0_returns_undefined)
{
    C4512Fixture f;
    f.a0.setValue(nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::Undefined);
}

Test(c4512_addr, undefined_a1_returns_undefined)
{
    C4512Fixture f;
    f.a1.setValue(nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::Undefined);
}

Test(c4512_addr, undefined_a2_returns_undefined)
{
    C4512Fixture f;
    f.a2.setValue(nts::Tristate::Undefined);
    cr_assert_eq(f.chip.compute(14), nts::Tristate::Undefined);
}