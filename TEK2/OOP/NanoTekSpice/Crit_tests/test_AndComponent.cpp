/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** test_and.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/elementary/AndComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"

static void linkComponents(nts::IComponent &src, std::size_t srcPin,
                           nts::IComponent &dst, std::size_t dstPin)
{
    src.setLink(srcPin, dst, dstPin);
    dst.setLink(dstPin, src, srcPin);
}

static void setupAnd(nts::InputComponent &a, nts::InputComponent &b,
                     nts::AndComponent &gate, nts::OutputComponent &out)
{
    linkComponents(a, 1, gate, 1);
    linkComponents(b, 1, gate, 2);
    linkComponents(gate, 3, out, 1);
}

Test(and_component, constructor_no_throw)
{
    cr_assert_no_throw(nts::AndComponent gate, std::exception);
}

Test(and_component, true_and_true_returns_true)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(and_component, false_and_true_returns_false)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(and_component, true_and_false_returns_false)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(and_component, false_and_false_returns_false)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(and_component, undefined_and_true_returns_undefined)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(and_component, true_and_undefined_returns_undefined)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(and_component, undefined_and_undefined_returns_undefined)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(and_component, false_and_undefined_returns_false)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(and_component, undefined_and_false_returns_false)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(and_component, result_updates_after_new_simulate)
{
    nts::InputComponent a, b;
    nts::AndComponent gate;
    nts::OutputComponent out;
    setupAnd(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);
    cr_assert_eq(out.compute(1), nts::Tristate::False);

    a.setValue(nts::Tristate::True);
    b.setValue(nts::Tristate::True);
    a.simulate(2);
    b.simulate(2);
    cr_assert_eq(out.compute(1), nts::Tristate::True);
}