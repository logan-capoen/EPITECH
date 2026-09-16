/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** test_xor.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/elementary/XorComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"

static void linkComponents(nts::IComponent &src, std::size_t srcPin,
                           nts::IComponent &dst, std::size_t dstPin)
{
    src.setLink(srcPin, dst, dstPin);
    dst.setLink(dstPin, src, srcPin);
}

static void setupXor(nts::InputComponent &a, nts::InputComponent &b,
                     nts::XorComponent &gate, nts::OutputComponent &out)
{
    linkComponents(a, 1, gate, 1);
    linkComponents(b, 1, gate, 2);
    linkComponents(gate, 3, out, 1);
}

Test(xor_component, constructor_no_throw)
{
    cr_assert_no_throw(nts::XorComponent gate, std::exception);
}

Test(xor_component, true_xor_true_returns_false)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(xor_component, true_xor_false_returns_true)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(xor_component, false_xor_true_returns_true)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(xor_component, false_xor_false_returns_false)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(xor_component, undefined_xor_true_returns_undefined)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(xor_component, true_xor_undefined_returns_undefined)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(xor_component, undefined_xor_false_returns_undefined)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(xor_component, false_xor_undefined_returns_undefined)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(xor_component, undefined_xor_undefined_returns_undefined)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(xor_component, compute_no_link_returns_undefined)
{
    nts::XorComponent gate;
    cr_assert_eq(gate.compute(3), nts::Tristate::Undefined);
}

Test(xor_component, result_updates_after_new_simulate)
{
    nts::InputComponent a, b;
    nts::XorComponent gate;
    nts::OutputComponent out;
    setupXor(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);
    cr_assert_eq(out.compute(1), nts::Tristate::False);

    b.setValue(nts::Tristate::False);
    a.simulate(2);
    b.simulate(2);
    cr_assert_eq(out.compute(1), nts::Tristate::True);
}