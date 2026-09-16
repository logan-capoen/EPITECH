/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** test_not.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/elementary/NotComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"

static void linkComponents(nts::IComponent &src, std::size_t srcPin,
                           nts::IComponent &dst, std::size_t dstPin)
{
    src.setLink(srcPin, dst, dstPin);
    dst.setLink(dstPin, src, srcPin);
}

static void setupNot(nts::InputComponent &in, nts::NotComponent &gate,
                     nts::OutputComponent &out)
{
    linkComponents(in, 1, gate, 1);
    linkComponents(gate, 2, out, 1);
}

Test(not_component, constructor_no_throw)
{
    cr_assert_no_throw(nts::NotComponent gate, std::exception);
}

Test(not_component, not_true_returns_false)
{
    nts::InputComponent in;
    nts::NotComponent gate;
    nts::OutputComponent out;
    setupNot(in, gate, out);

    in.setValue(nts::Tristate::True);
    in.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(not_component, not_false_returns_true)
{
    nts::InputComponent in;
    nts::NotComponent gate;
    nts::OutputComponent out;
    setupNot(in, gate, out);

    in.setValue(nts::Tristate::False);
    in.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(not_component, not_undefined_returns_undefined)
{
    nts::InputComponent in;
    nts::NotComponent gate;
    nts::OutputComponent out;
    setupNot(in, gate, out);

    in.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(not_component, double_not_true_returns_true)
{
    nts::InputComponent in;
    nts::NotComponent gate1;
    nts::NotComponent gate2;
    nts::OutputComponent out;

    linkComponents(in, 1, gate1, 1);
    linkComponents(gate1, 2, gate2, 1);
    linkComponents(gate2, 2, out, 1);

    in.setValue(nts::Tristate::True);
    in.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(not_component, double_not_false_returns_false)
{
    nts::InputComponent in;
    nts::NotComponent gate1;
    nts::NotComponent gate2;
    nts::OutputComponent out;

    linkComponents(in, 1, gate1, 1);
    linkComponents(gate1, 2, gate2, 1);
    linkComponents(gate2, 2, out, 1);

    in.setValue(nts::Tristate::False);
    in.simulate(1);

    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(not_component, result_updates_after_new_simulate)
{
    nts::InputComponent in;
    nts::NotComponent gate;
    nts::OutputComponent out;
    setupNot(in, gate, out);

    in.setValue(nts::Tristate::True);
    in.simulate(1);
    cr_assert_eq(out.compute(1), nts::Tristate::False);

    in.setValue(nts::Tristate::False);
    in.simulate(2);
    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(not_component, compute_no_link_returns_undefined)
{
    nts::NotComponent gate;
    cr_assert_eq(gate.compute(2), nts::Tristate::Undefined);
}