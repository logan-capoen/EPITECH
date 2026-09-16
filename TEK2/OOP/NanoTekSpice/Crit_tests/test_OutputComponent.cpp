/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** test_output.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/special/OutputComponent.hpp"
#include "components/special/InputComponent.hpp"

static void linkComponents(nts::IComponent &src, std::size_t srcPin,
                           nts::IComponent &dst, std::size_t dstPin)
{
    src.setLink(srcPin, dst, dstPin);
    dst.setLink(dstPin, src, srcPin);
}

Test(output_component, constructor_no_throw)
{
    cr_assert_no_throw(nts::OutputComponent out, std::exception);
}

Test(output_component, constructor_display_is_undefined)
{
    nts::OutputComponent out;
    cr_assert_eq(out.displayValue(), 'U');
}

Test(output_component, constructor_compute_returns_undefined)
{
    nts::OutputComponent out;
    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(output_component, compute_no_link_returns_undefined)
{
    nts::OutputComponent out;
    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(output_component, compute_never_returns_true_without_link)
{
    nts::OutputComponent out;
    cr_assert_neq(out.compute(1), nts::Tristate::True);
}

Test(output_component, compute_never_returns_false_without_link)
{
    nts::OutputComponent out;
    cr_assert_neq(out.compute(1), nts::Tristate::False);
}

Test(output_component, compute_linked_input_true)
{
    nts::InputComponent in;
    nts::OutputComponent out;
    linkComponents(in, 1, out, 1);
    in.setValue(nts::Tristate::True);
    in.simulate(1);
    cr_assert_eq(out.compute(1), nts::Tristate::True);
}

Test(output_component, compute_linked_input_false)
{
    nts::InputComponent in;
    nts::OutputComponent out;
    linkComponents(in, 1, out, 1);
    in.setValue(nts::Tristate::False);
    in.simulate(1);
    cr_assert_eq(out.compute(1), nts::Tristate::False);
}

Test(output_component, compute_linked_input_undefined)
{
    nts::InputComponent in;
    nts::OutputComponent out;
    linkComponents(in, 1, out, 1);
    in.simulate(1);
    cr_assert_eq(out.compute(1), nts::Tristate::Undefined);
}

Test(output_component, compute_caches_result_on_second_call)
{
    nts::InputComponent in;
    nts::OutputComponent out;
    linkComponents(in, 1, out, 1);
    in.setValue(nts::Tristate::True);
    in.simulate(1);
    nts::Tristate first = out.compute(1);
    nts::Tristate second = out.compute(1);
    cr_assert_eq(first, second);
}

Test(output_component, display_value_returns_U_without_link)
{
    nts::OutputComponent out;
    cr_assert_eq(out.displayValue(), 'U');
}

Test(output_component, display_value_returns_1_when_linked_true)
{
    nts::InputComponent in;
    nts::OutputComponent out;
    linkComponents(in, 1, out, 1);
    in.setValue(nts::Tristate::True);
    in.simulate(1);
    cr_assert_eq(out.displayValue(), '1');
}

Test(output_component, display_value_returns_0_when_linked_false)
{
    nts::InputComponent in;
    nts::OutputComponent out;
    linkComponents(in, 1, out, 1);
    in.setValue(nts::Tristate::False);
    in.simulate(1);
    cr_assert_eq(out.displayValue(), '0');
}

Test(output_component, display_value_returns_U_when_linked_undefined)
{
    nts::InputComponent in;
    nts::OutputComponent out;
    linkComponents(in, 1, out, 1);
    in.simulate(1);
    cr_assert_eq(out.displayValue(), 'U');
}

Test(output_component, display_value_consistent_with_compute)
{
    nts::InputComponent in;
    nts::OutputComponent out;
    linkComponents(in, 1, out, 1);
    in.setValue(nts::Tristate::True);
    in.simulate(1);
    nts::Tristate val = out.compute(1);
    char display = out.displayValue();
    if (val == nts::Tristate::True)
        cr_assert_eq(display, '1');
    else if (val == nts::Tristate::False)
        cr_assert_eq(display, '0');
    else
        cr_assert_eq(display, 'U');
}