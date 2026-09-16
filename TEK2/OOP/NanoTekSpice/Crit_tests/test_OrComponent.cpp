/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** test_or.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/elementary/OrComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"

static void linkComponents(nts::IComponent &src, std::size_t srcPin,
                           nts::IComponent &dst, std::size_t dstPin)
{
    src.setLink(srcPin, dst, dstPin);
    dst.setLink(dstPin, src, srcPin);
}

static void setupOr(nts::InputComponent &a, nts::InputComponent &b,
                    nts::OrComponent &gate, nts::OutputComponent &out)
{
    linkComponents(a, 1, gate, 1);
    linkComponents(b, 1, gate, 2);
    linkComponents(gate, 3, out, 1);
}

Test(or_component, constructor_no_throw)
{
    cr_assert_no_throw(nts::OrComponent gate, std::exception);
}

Test(or_component, true_or_true_returns_true)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(or_component, true_or_false_returns_true)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(or_component, false_or_true_returns_true)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(or_component, false_or_false_returns_false)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(or_component, undefined_or_false_returns_undefined)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(or_component, false_or_undefined_returns_undefined)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(or_component, undefined_or_undefined_returns_undefined)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(or_component, true_or_undefined_returns_true)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    a.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(or_component, undefined_or_true_returns_true)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    b.setValue(nts::Tristate::True);
    a.simulate(1);
    b.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(or_component, compute_no_link_returns_undefined)
{
    nts::OrComponent gate;
    cr_assert_eq(gate.compute(3), nts::Tristate::Undefined);
}

Test(or_component, result_updates_after_new_simulate)
{
    nts::InputComponent a, b;
    nts::OrComponent gate;
    nts::OutputComponent out;
    setupOr(a, b, gate, out);

    a.setValue(nts::Tristate::False);
    b.setValue(nts::Tristate::False);
    a.simulate(1);
    b.simulate(1);
    cr_assert_eq(out.compute(1), nts::Tristate::False);

    a.setValue(nts::Tristate::True);
    a.simulate(2);
    b.simulate(2);
    cr_assert_eq(out.compute(1), nts::Tristate::True);
}